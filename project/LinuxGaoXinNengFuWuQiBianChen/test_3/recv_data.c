#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdbool.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define BUF_SIZE (1024)

static bool flag = true;

void
sig_handler(int arg)
{
    flag = false;
    fprintf(stdout, "Quitting...\n");
}

static void
Usage(const char *bin)
{
    fprintf(stderr, "\n===============Usage:===============\n"
            "%s 127.0.0.1 8092 5"
            "\n====================================\n", bin);
}

int 
main(int argc, char *const argv[])
{
    int                 sock_fd = -1;
    int                 acpt_fd = -1;
    int                 reuse_addr = 1;
    int                 ret = -1;
    int                 backlog = -1;
    char                ip[] = {};
    struct sockaddr_in  server_addr = {};
    struct sockaddr_in  client_addr = {};
    socklen_t           client_len = -1;

    signal(SIGINT, sig_handler);

    if (argc <= 3) {
        Usage(argv[0]);
        return -1;
    }

    sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_fd < 0) {
        fprintf(stderr, "create socket failed![%s]\n", strerror(errno));
        return -1;
    }
    
    ret = setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, &reuse_addr, sizeof(reuse_addr));
    if (ret != 0) {
        fprintf(stderr, "setsockopt failed[%s]!\n", strerror(errno));
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
    
    backlog = atoi(argv[3]);

    ret = listen(sock_fd, backlog);
    if (ret != 0) {
        fprintf(stderr, "listen %d failed![%s]\n", sock_fd, strerror(errno));
        return -1;
    } else {

        client_len = sizeof(client_addr); 
        while (flag) {

            acpt_fd = accept(sock_fd, (struct sockaddr *)&client_addr, &client_len);
            if (acpt_fd > 0) {

                char buffer[BUF_SIZE] = {};

                memset(buffer, '\0', BUF_SIZE);
                bzero(ip, sizeof(ip));

                inet_ntop(AF_INET, &client_addr.sin_addr, ip, INET_ADDRSTRLEN);
                fprintf(stdout, "From: %s:%d\n", ip, ntohs(client_addr.sin_port));

                ret = recv(acpt_fd, buffer, BUF_SIZE - 1, 0);
                fprintf(stdout, "recv normal: %s, length: %d\n", buffer, ret);

                memset(buffer, '\0', BUF_SIZE);

                ret = recv(acpt_fd, buffer, BUF_SIZE - 1, MSG_OOB);
                fprintf(stdout, "recv oob: %s, length: %d\n", buffer, ret);

                memset(buffer, '\0', BUF_SIZE);

                ret = recv(acpt_fd, buffer, BUF_SIZE - 1, 0);
                fprintf(stdout, "recv normal: %s, length: %d\n", buffer, ret);
                close(acpt_fd);
            }
        }
    }

    close(sock_fd);
    printf("recv data!\n");
    return 0;
}
