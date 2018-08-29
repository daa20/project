#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/epoll.h>

#define MAX_EVENT_NUMBER    (1024)
#define BUFFER_SIZE         (10)

static void
Usage(const char *bin)
{
    fprintf(stdout, "\n================Usage:===============\n"
            "%s 127.0.0.1 8093 LT/ET"
            "\n=================================\n", bin);
}

static int
setnonblocking(int fd)
{
    int old_option = fcntl(fd, F_GETFL);
    int new_option = old_option | O_NONBLOCK;
    fcntl(fd, F_SETFL, new_option);
    return old_option; 
}

static void
add_fd(int epollfd, int fd, bool enable)
{
    struct epoll_event event;
    event.data.fd = fd;
    event.events = EPOLLIN;
    if (enable == true) {
        event.events |= EPOLLET;
    }

    epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &event);
    
    setnonblocking(fd);
}

static void 
lt(struct epoll_event *events, int number, int epollfd, int listen_fd)
{
    int                 ret = -1;
    int                 i = 0;
    int                 sock_fd = 0;
    int                 conn_fd = 0;
    struct sockaddr_in  client_addr = {};
    socklen_t           client_addr_len = 0;
    char                IP[INET_ADDRSTRLEN] = {};
    char                buf[BUFFER_SIZE];
    
    bzero(&client_addr, sizeof(client_addr));
    memset(IP, '\0', INET_ADDRSTRLEN);
    client_addr_len = sizeof(client_addr);

    for (i = 0; i < number; i++) {
        sock_fd = events[i].data.fd;
        if (sock_fd == listen_fd) {
            conn_fd = accept(listen_fd, (struct sockaddr *)&client_addr, &client_addr_len);
            if (conn_fd < 0) {
                fprintf(stderr, "accept %d failed![%s]\n", listen_fd, strerror(errno));
                continue;
            }

            /* Disable epoll ET mode. */
            add_fd(epollfd, conn_fd, false);
        } else if (events[i].events & EPOLLIN) {
            /* just the cache of socket has data which dont read, trigger this. */
            fprintf(stdout, "event trigger once!\n");
            memset(buf, '\0', BUFFER_SIZE);
            ret = recv(sock_fd, buf, BUFFER_SIZE - 1, 0);
            if (ret <= 0) {
                close(sock_fd);
                continue;
            }

            fprintf(stdout, "get %d bytes of content: %s\n", ret, buf);

        } else {

            fprintf(stdout, "something else happened!\n");
        }   
    }
}

static void
et(struct epoll_event *events, int number, int epollfd, int listen_fd)
{
    int                 ret = -1;
    int                 i = 0;
    int                 sock_fd = -1;
    int                 conn_fd = -1;
    char                buf[BUFFER_SIZE] = {};
    struct sockaddr_in  client_addr = {};
    socklen_t           client_addr_len = 0;

    for (i = 0; i < number; i++) {
        sock_fd = events[i].data.fd;
        if (sock_fd == listen_fd) {

            bzero(&client_addr, sizeof(client_addr));
            client_addr_len = sizeof(client_addr);
            conn_fd = accept(listen_fd, (struct sockaddr *)&client_addr,
                    &client_addr_len);
            if (conn_fd < 0) {
                fprintf(stderr, "accept %d failed![%s]\n",
                        listen_fd, strerror(errno));
                continue;
            }

            /* Enable epoll ET mode. */
            add_fd(epollfd, conn_fd, true);
        } else if (events[i].events & EPOLLIN) {

            fprintf(stdout, "event trigger once\n");
            
            while (1) {

                ret = recv(sock_fd, buf, BUFFER_SIZE - 1, 0);
                if (ret < 0) {

                    if ((errno == EAGAIN) || (errno == EWOULDBLOCK)) {
                        fprintf(stdout, "read later!\n");
                        break;
                    }

                    close(sock_fd);
                    break;
                } else if (ret == 0) {
                    close(sock_fd);
                } else {
                    fprintf(stdout, "get %d bytes of content: %s\n",
                            ret, buf);
                }
            }

        } else {
            fprintf(stdout, "something else happened\n");
        }
    }
}

int
main(int argc, char *const argv[])
{

    int                 ret = -1;
    const char          *ip = NULL;
    const char          *mode = NULL;
    unsigned short int  port = 0;
    int                 sock_fd = 0;
    struct sockaddr_in  server_addr = {};
    struct epoll_event  events[MAX_EVENT_NUMBER];
    int                 epollfd = 0;

    if (argc != 4) {
        Usage(argv[0]);
        return -1;
    }

    ip = argv[1];
    port = atoi(argv[2]);
    mode = argv[3];

    bzero(&server_addr, sizeof(server_addr));

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    inet_pton(AF_INET, ip, &server_addr.sin_addr);

    sock_fd = socket(PF_INET, SOCK_STREAM, 0);
    if (sock_fd <= 0) {
        fprintf(stderr, "create socket failed![%s]\n", strerror(errno));
        return -1;
    }

    ret = bind(sock_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (ret != 0) {
        fprintf(stderr, "bind %d failed![%s]\n", sock_fd, strerror(errno));
        close(sock_fd);
        return -1;
    }

    ret = listen(sock_fd, 5);
    if (ret != 0) {
        fprintf(stderr, "listen %d failed![%s]\n", sock_fd, strerror(errno));
        close(sock_fd);
        return -1;
    }

    epollfd = epoll_create(5);
    if (epollfd <= 0) {
        fprintf(stderr, "create epoll failed![%s]\n", strerror(errno));
        return -1;
    }

    add_fd(epollfd, sock_fd, true);

    while (1) {
        
        ret = epoll_wait(epollfd, events, MAX_EVENT_NUMBER, -1);
        if (ret < 0) {
            fprintf(stderr, "epoll failed![%s]\n", strerror(errno));
            break;
        }
        
        if (strncmp(mode, "LT", strlen("LT")) == 0) {

            fprintf(stdout, "LT mode!\n");
            
            /* use epoll LT mode. */
            lt(events, ret, epollfd, sock_fd);
        } else if (strncmp(mode, "ET", strlen("ET")) == 0) {

            fprintf(stdout, "ET mode!\n");
            
            /* use epoll ET mode. */
            et(events, ret, epollfd, sock_fd);
        } else {

            fprintf(stdout, "LT mode!\n");

            /* default: use epoll LT mode. */
            lt(events, ret, epollfd, sock_fd);
        }
    }


    close(sock_fd);

    fprintf(stdout, "hello world!\n");
    return 0;
}
