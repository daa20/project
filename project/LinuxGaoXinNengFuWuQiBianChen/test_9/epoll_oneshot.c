
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <pthread.h>
#include <sys/epoll.h>

#define MAX_EVENT_NUMBER    (1024)
#define BUFFER_SIZE         (1024)

struct fds {
    int epoll_fd;
    int conn_fd;
};

static void
Usage(const char *bin)
{
    fprintf(stdout, "\n================Usage:================\n"
            "%s 127.0.0.1 8093"
            "\n===================================\n", bin);
}

static int 
setnonblocking(int fd)
{
    int old_option = 0;
    int new_option = 0;

    old_option = fcntl(fd, F_GETFL);
    new_option = old_option | O_NONBLOCK;

    fcntl(fd, F_SETFL, new_option);
    
    return old_option; 
}

static void 
add_fd(int epollfd, int fd, bool one_shot)
{
    struct epoll_event event = {};

    event.data.fd = fd;
    event.events = EPOLLIN | EPOLLET;

    if (one_shot == true) {
        event.events |= EPOLLONESHOT;
    }

    epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &event);

    setnonblocking(fd);
}

static void
reset_oneshot(int epoll_fd, int conn_fd)
{
    struct epoll_event event = {};

    event.data.fd = conn_fd;
    event.events = EPOLLIN | EPOLLET | EPOLLONESHOT;

    epoll_ctl(epoll_fd, EPOLL_CTL_MOD, conn_fd, &event);
}

/* worker thread. */
void *
worker(void *arg)
{
    struct fds  *fds_for_new_worker = (struct fds *)arg;
    int         conn_fd = fds_for_new_worker->conn_fd;
    int         epoll_fd = fds_for_new_worker->epoll_fd;
    int         ret = -1;
    char        buf[BUFFER_SIZE] = {};

    memset(buf, '\0', BUFFER_SIZE);

    while (1) {
        ret = recv(conn_fd, buf, BUFFER_SIZE - 1, 0);
        if (ret == 0) {
            close(conn_fd);
            fprintf(stdout, "foreigner closed the connection\n");
            break;
        } else if (ret < 0) {
            if (errno == EAGAIN) {
                reset_oneshot(epoll_fd, conn_fd);
                fprintf(stdout, "read later!\n");
                break;
            }
        } else {
            fprintf(stdout, "get content: %s\n", buf);
            /* sleep 5s to simulate handling data process. */
            sleep(5);
        }
    }
    
    fprintf(stdout, "end thread receiving data on fd: %d\n", conn_fd);

    return NULL;
}

int 
main(int argc, char *const argv[])
{
    int                 ret = -1;
    int                 i = 0;
    int                 sock_fd = -1;
    int                 conn_fd = -1;
    int                 epollfd = -1;
    int                 event_fd = -1;
    unsigned short int  port = 0;
    const char          *ip = NULL;
    struct sockaddr_in  server_addr = {};
    struct sockaddr_in  client_addr = {};
    socklen_t           client_addr_len = 0;
    struct epoll_event  events[MAX_EVENT_NUMBER] = {};
    pthread_t           thread;
    struct fds          fds_for_new_worker = {};

    if (argc != 3) {
        Usage(argv[0]);
        return -1;
    }

    port = atoi(argv[2]);
    ip = argv[1];

    bzero(&server_addr, sizeof(server_addr));
    bzero(&client_addr, sizeof(client_addr));

    sock_fd = socket(PF_INET, SOCK_STREAM, 0);
    if (sock_fd < 0) {
        fprintf(stderr, "create socket failed![%s]\n", strerror(errno));
        return -1;
    }
    
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    inet_pton(AF_INET, ip, &server_addr.sin_addr);

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
    if (epollfd < 0) {
        fprintf(stderr, "create epoll failed![%s]\n", strerror(errno));
        return -1;
    }

    add_fd(epollfd, sock_fd, false);

    while (1) {
    
        ret = epoll_wait(epollfd, events, MAX_EVENT_NUMBER, -1);
        if (ret < 0) {
            fprintf(stderr, "epoll wait failed![%s]\n", strerror(errno));
            break;
        }
        
        for (i = 0; i < ret; i++) {
            event_fd = events[i].data.fd;
            if (event_fd == sock_fd) {
                client_addr_len = sizeof(client_addr_len);
                conn_fd = accept(sock_fd, (struct sockaddr *)&client_addr, &client_addr_len);
                if (conn_fd < 0) {
                    fprintf(stderr, "accept failed![%s]\n", strerror(errno));
                    continue;
                }
                
                add_fd(epollfd, conn_fd, true);

            } else if (events[i].events & EPOLLIN) {
                fds_for_new_worker.epoll_fd = epollfd;
                fds_for_new_worker.conn_fd = event_fd;
                /* start a pthread to work. */
                pthread_create(&thread, NULL,
                        worker, (void *)&fds_for_new_worker);
                //recv();
            } else {
                fprintf(stderr, "Something else happened\n");
            }
        }
    }


    close(sock_fd);

    fprintf(stdout, "hello world!\n");
    return 0;
}
