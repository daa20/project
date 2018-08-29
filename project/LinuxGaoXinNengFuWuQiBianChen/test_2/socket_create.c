#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <assert.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

static bool flag = true;

void signal_handler(int arg)
{
    flag = false;
    fprintf(stdout, "Quit...\n");
}

void
Usage(const char *bin)
{
    fprintf(stderr, "\n============Usage:============\n"
            "%s 127.0.0.1 8091 5"
            "\n====================================\n", bin);
}

int
main(int argc, char *const argv[])
{
    int                 listen_fd = -1;
    struct sockaddr_in  server_addr = {};
    struct sockaddr_in  client_addr = {};
    int                 client_fd = -1;
    socklen_t           client_len = 0;
    char                ip[INET_ADDRSTRLEN] = {};
    int                 ret = -1;
    int                 blacklog = 0;

    if (argc <= 3) {
        Usage(argv[0]);
        return -1;
    }

    signal(SIGINT, signal_handler);

    listen_fd = socket(PF_INET, SOCK_STREAM, 0);
    assert(listen_fd > 0);

    bzero(&server_addr, sizeof(server_addr));
    bzero(&client_addr, sizeof(client_addr));
    bzero(ip, sizeof(ip));

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(argv[2]));
    inet_pton(AF_INET, argv[1], &server_addr.sin_addr);
    
    ret = bind(listen_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (ret != 0) {
        fprintf(stderr, "bind %d failed![%s]\n", listen_fd, strerror(errno));
        return -1;
    }

    blacklog = atoi(argv[3]);
    
    ret = listen(listen_fd, blacklog);
    if (ret != 0) {
        fprintf(stderr, "listen %d failed![%s]\n", listen_fd, strerror(errno));
        return -1;
    }

    client_len = sizeof(client_addr);

    while(flag) {
        client_fd = accept(listen_fd, (struct sockaddr *)&client_addr, &client_len);
        if (client_fd == -1) {
            fprintf(stderr, "accept failed![%s]\n", strerror(errno));
        } else {
            inet_ntop(AF_INET, &client_addr.sin_addr, ip, INET_ADDRSTRLEN);
            fprintf(stdout, "From: %s:%d connecting!\n", ip, ntohs(client_addr.sin_port));
            close(client_fd);
        }

        sleep(20);
    }

    close(listen_fd);
    printf("hello world!\n");
    return 0;
}
