#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/sendfile.h>

static void
Usage(const char *bin)
{
    fprintf(stdout, "\n=============Usage:============\n"
            "%s 127.0.0.1 8093 ./test.txt"
            "\n==============================\n", bin);
}


int
main(int argc, char *const argv[])
{
    int                 ret = -1;
    int                 sock_fd = -1;
    int                 conn_fd = -1;
    struct sockaddr_in  server_addr = {};
    struct sockaddr_in  client_addr = {};
    socklen_t           client_addr_len = -1;
    char                IP[INET_ADDRSTRLEN] = {};
    int                 fd = -1;
    struct stat         stat_buf = {};

    if (argc != 4) {
        Usage(argv[0]);
        return -1;
    }

    fd = open(argv[3], O_RDONLY);
    if (fd < 0) {
        fprintf(stderr, "open %s failed![%s]\n", argv[3], strerror(errno));
        return -1;
    }

    ret = fstat(fd, &stat_buf);
    if (ret != 0) {
        fprintf(stderr, "get file %s status failed![%s]\n", argv[3], strerror(errno));
        return -1;
    }

    sock_fd = socket(PF_INET, SOCK_STREAM, 0);
    if (sock_fd < 0) {
        fprintf(stderr, "create socket failed![%s]\n", strerror(errno));
        return -1;
    }

    bzero(&server_addr, sizeof(server_addr));
    bzero(&client_addr, sizeof(client_addr));
    server_addr.sin_family = PF_INET;
    server_addr.sin_port = htons(atoi(argv[2]));
    inet_pton(AF_INET, argv[1], &server_addr.sin_addr);

    ret = bind(sock_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (ret != 0) {
        fprintf(stderr, "bind %d failed![%s]\n", sock_fd, strerror(errno));
        return -1;
    }

    ret = listen(sock_fd, 5);
    if (ret != 0) {
        fprintf(stderr, "listen %d failed![%s]\n", sock_fd, strerror(errno));
        return -1;
    }
    
    client_addr_len = sizeof(client_addr);
    conn_fd = accept(sock_fd, (struct sockaddr *)&client_addr, &client_addr_len);
    if (conn_fd < 0) {
        fprintf(stderr, "accept failed![%s]", strerror(errno));
    } else {
        inet_ntop(AF_INET, &client_addr.sin_addr, IP, INET_ADDRSTRLEN);
        fprintf(stdout, "Welcome %s:%d\n", IP, ntohs(client_addr.sin_port));

        ret = sendfile(conn_fd, fd, NULL, stat_buf.st_size);
        fprintf(stdout, "send: %d bytes!\n", ret);

        close(conn_fd);
    }

    close(sock_fd);

    fprintf(stdout, "hello world!\n");
    return 0;
}
