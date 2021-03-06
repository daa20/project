#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

static void 
Usage(const char *bin)
{
    fprintf(stdout, "\n==============Usage:==============\n"
            "%s 127.0.0.1 8093"
            "\n================================\n", bin);
}

int
main(int argc, char *const argv[])
{
    int                 ret = -1;
    int                 sock_fd = -1;
    int                 conn_fd = -1;
    struct sockaddr_in  server_addr = {};
    struct sockaddr_in  client_addr = {};
    socklen_t           client_len = -1;
    char                IP[INET_ADDRSTRLEN] = {};


    if (argc != 3) {
        Usage(argv[0]);
        return -1;
    }
    
    fprintf(stdout, "IP: %s:%d\n", argv[1], atoi(argv[2]));

    bzero(&server_addr, sizeof(server_addr));
    bzero(&client_addr, sizeof(client_addr));
    fprintf(stdout, "IP strlen: %d\n", (int)strlen(IP));

    memset(IP, '\0', strlen(IP));

    sock_fd = socket(PF_INET, SOCK_STREAM, 0);
    if (sock_fd < 0) {
        fprintf(stderr, "create socket failed![%s]\n", strerror(errno));
        return -1;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = ntohs(atoi(argv[2]));
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

    client_len = sizeof(client_addr);
    conn_fd = accept(sock_fd, (struct sockaddr *)&client_addr, &client_len);
    if (conn_fd < 0) {
        fprintf(stderr, "accept failed![%s]\n", strerror(errno));
        return -1;
    } else {
        inet_ntop(AF_INET, &client_addr.sin_addr, IP, INET_ADDRSTRLEN);
        fprintf(stdout, "Welcome %s:%d\n", IP, ntohs(client_addr.sin_port)); 

        close(STDOUT_FILENO);

        dup(conn_fd);

        fprintf(stdout, "hello world!\n");

        close(conn_fd);
    }

    close(sock_fd);

    printf("hello world!\n");
    return 0;
}
