#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/epoll.h>


#define TCP_BUF_SIZE        (1024)
#define MAX_EVENT_NUMBER    (1024)
#define UDP_BUF_SIZE        (1024)


static int
set_nonblocking(int fd)
{
    int old_opt = -1;
    int new_opt = -1;

    old_opt = fcntl(fd, F_GETFL);

    new_opt = old_opt | O_NONBLOCK;
    fcntl(fd, F_SETFL, new_opt);

    return old_opt;
}

static void
add_fd(int epol_fd, int fd)
{
    struct epoll_event event = {};
    
    event.data.fd = fd;
    event.events = EPOLLIN | EPOLLET;

    epoll_ctl(epol_fd, EPOLL_CTL_ADD, fd, &event);

    set_nonblocking(fd);
}


int
main(int argc, char *const argv[])
{
    int                 ret = -1;
    int                 i = 0;
    int                 sock_fd = -1;
    int                 tcp_sock_fd = -1;
    int                 udp_sock_fd = -1;
    int                 conn_fd = -1;
    int                 epol_fd = -1;
    int                 epol_number = -1;
    int                 port = -1;
    int                 addr_reuse = 1; /* 1: enable addr-reused, 0: disable addr-reused. */
    const char          *ip = NULL;
    char                tcp_buf[TCP_BUF_SIZE] = {};
    char                udp_buf[UDP_BUF_SIZE] = {};
    struct sockaddr_in  server_addr = {};
    struct sockaddr_in  client_addr = {};
    socklen_t           client_addr_len = 0;
    struct epoll_event  events[MAX_EVENT_NUMBER] = {};
 
    if (argc != 3) {
        fprintf(stderr, "\n==========Usage:========\n"
                "%s 127.0.0.1 9080"
                "\n==================\n", argv[0]);
        return -1; 
    }


    tcp_sock_fd = socket(PF_INET, SOCK_STREAM, 0);
    if (tcp_sock_fd < 0) {
        fprintf(stderr, "create TCP socket failed[%s]!\n", strerror(errno));
        return -1;
    }

    ret = setsockopt(tcp_sock_fd, SOL_SOCKET, SO_REUSEADDR,
            &addr_reuse, sizeof(addr_reuse));
    if (ret != 0) {
        fprintf(stderr, "setsockopt failed[%s]!\n", strerror(errno));
        return -1;
    }

    ip = argv[1];
    port = atoi(argv[2]);

    /* handle TCP */
    bzero(&server_addr, sizeof(server_addr));
    bzero(&client_addr, sizeof(client_addr));
    client_addr_len = sizeof(client_addr);
    memset(tcp_buf, '\0', TCP_BUF_SIZE);
    memset(udp_buf, '\0', UDP_BUF_SIZE);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    inet_pton(AF_INET, ip, &server_addr.sin_addr);

    ret = bind(tcp_sock_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (ret != 0) {
        fprintf(stderr, "bind TCP socket failed[%s]!\n", strerror(errno));
        goto out;
    }

    ret = listen(tcp_sock_fd, 5);
    if (ret != 0) {
        fprintf(stderr, "listen failed[%s]!\n", strerror(errno));
        goto out;
    }
    
    /* handle UDP */
    bzero(&server_addr, sizeof(server_addr));

    udp_sock_fd = socket(PF_INET, SOCK_DGRAM, 0);
    if (udp_sock_fd < 0) {
        fprintf(stderr, "create UDP socket failed[%s]!\n", strerror(errno));
        goto out;
    }

    ret = setsockopt(udp_sock_fd, SOL_SOCKET, SO_REUSEADDR,
            &addr_reuse, sizeof(addr_reuse));
    if (ret != 0) {
        fprintf(stderr, "setsockopt failed[%s]!\n", strerror(errno));
        return -1;
    }


    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    inet_pton(AF_INET, ip, &server_addr.sin_addr);

    ret = bind(udp_sock_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (ret != 0) {
        fprintf(stderr, "bind UDP failed[%s]!\n", strerror(errno));
        goto out;
    }

    epol_fd = epoll_create(5);
    if (epol_fd < 0) {
        fprintf(stderr, "create epoll failed[%s]!\n", strerror(errno));
        goto out;
    }

    add_fd(epol_fd, tcp_sock_fd);
    add_fd(epol_fd, udp_sock_fd);

    while (1) {
        //epol_number = epoll_wait(epol_fd, events, MAX_EVENT_NUMBER, 1000);
        epol_number = epoll_wait(epol_fd, events, MAX_EVENT_NUMBER, -1);
        if (epol_number < 0) {
            fprintf(stderr, "epoll wait error[%s]\n", strerror(errno));
            break;
        } else if (epol_number == 0) {
            fprintf(stdout, "timeout!\n");
        } else {
            for (i = 0; i < epol_number; i++) {
                sock_fd = events[i].data.fd;
                if (sock_fd == tcp_sock_fd) {
                    
                    conn_fd = accept(tcp_sock_fd, (struct sockaddr *)&client_addr, &client_addr_len);
                    if (conn_fd < 0) {
                        fprintf(stderr, "accept failed[%s]\n", strerror(errno));
                   
                    } else {
                        add_fd(epol_fd, conn_fd);
                    }
                } else if (sock_fd == udp_sock_fd) {
                    memset(udp_buf, '\0', UDP_BUF_SIZE);
                    ret = recvfrom(udp_sock_fd, udp_buf, UDP_BUF_SIZE - 1, 0,
                            (struct sockaddr *)&client_addr, &client_addr_len);
                    if (ret > 0) {
                        sendto(udp_sock_fd, udp_buf, UDP_BUF_SIZE - 1, 0, 
                                (struct sockaddr *)&client_addr, client_addr_len);
                    }
                } else if (events[i].events & EPOLLIN) {
                    while (1) {
                        memset(tcp_buf, '\0', TCP_BUF_SIZE);
                        ret = recv(sock_fd, tcp_buf, TCP_BUF_SIZE - 1, 0);
                        if (ret < 0) {
                            if ((errno == EAGAIN) || (errno == EWOULDBLOCK)) {
                                break;
                            }

                            close(sock_fd);
                            break;
                        } else if ( ret == 0) {
                            close(sock_fd);
                        } else {
                            send(sock_fd, tcp_buf, ret, 0);
                        }
                    } 
                } else {
                    fprintf(stdout, "something else happened!\n");
                }
            }
                
        }
    }
out:

    if (tcp_sock_fd > 0) {
        close(tcp_sock_fd);
    }

    if (udp_sock_fd > 0) {
        close(udp_sock_fd);
    }

    fprintf(stdout, "hello world!\n");
    return ret;
}
