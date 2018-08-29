#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>


static int
connect_timeout(const char *ip, const int port, const int time)
{
    int                 ret = -1;
    int                 sock_fd = -1;
    struct sockaddr_in  server_addr = {};
    struct timeval      timeout = {};

    sock_fd = socket(PF_INET, SOCK_STREAM, 0);
    if (sock_fd < 0) {
        fprintf(stderr, "create socket failed[%s]!\n", strerror(errno));
        goto out;
    }
    
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    inet_pton(AF_INET, ip, &server_addr.sin_addr);

    timeout.tv_sec = time;
    timeout.tv_usec = 0;

    ret = setsockopt(sock_fd, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof(timeout));
    if (ret != 0) {
        fprintf(stderr, "set timeout failed[%s]!\n", strerror(errno));
        goto out;
    }

    ret = connect(sock_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (ret != 0) {
        fprintf(stderr, "connect failed[%s]\n", strerror(errno));
        if (errno == EINPROGRESS) {
        
            fprintf(stderr, "connect timeout[%s]\n", strerror(errno));
        }

        goto out;
    }

    ret = sock_fd;

out:

    if (sock_fd > 0) {
        close(sock_fd);
    }

    return ret;
}

int
main(int argc, char *const argv[])
{
    const char          *ip = NULL;
    int                 port = -1;
    int                 ret = -1;

    if (argc != 3) {
        fprintf(stderr, "\n==============Usage:============\n"
                "%s 127.0.0.1 8091"
                "\n=================================\n", argv[0]);
        return -1;
    }

    ip = argv[1];
    port = atoi(argv[2]);

    ret = connect_timeout(ip, port, 10);
    if (ret < 0) {
        ret = -1;
    }

    fprintf(stdout, "hello world!\n");
    return 0;
}
