#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdbool.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <signal.h>

#define MAX_EVENT_NUMBER    (1024)

static int pipe_fd[2] = {};


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

static void
sig_handler(int sig)
{
    /* save errno value. */
    int save_errno = errno;
    int msg = sig;
    /* will write signal value into PIPE and tell master process. */
    send(pipe_fd[1], (char *)&msg, 1, 0);
    errno = save_errno;
}


static void
add_sig(int sig)
{
    struct sigaction sa = {};
    
    memset(&sa, '\0', sizeof(sa));

    sa.sa_handler = sig_handler;
    sa.sa_flags |= SA_RESTART;
    
    sigfillset(&sa.sa_mask);

    sigaction(sig, &sa, NULL);
}

int 
main(int argc, char *const argv[])
{
    int                 ret = -1;
    int                 sock_fd = -1;
    int                 conn_fd = -1;
    int                 epol_fd = -1;
    int                 fd = -1;
    int                 epol_num = -1;
    int                 i = 0;
    int                 j = 0;
    int                 port = -1;
    bool                stop_server = false;
    /* 1: enable, 0: disable */
    int                 reuse_enable = 1;
    const char          *ip = NULL;
    struct sockaddr_in  server_addr = {};
    struct sockaddr_in  client_addr = {};
    socklen_t           client_addr_len = -1;
    struct epoll_event  events[MAX_EVENT_NUMBER] = {};

    if (argc != 3) {
        fprintf(stderr, "\n==========Usage:==========\n"
                "%s 127.0.0.1 8091"
                "\n==========================\n", argv[0]);
        return -1;
    }

    ip = argv[1];
    port = atoi(argv[2]);

    sock_fd = socket(PF_INET, SOCK_STREAM, 0);
    if (sock_fd < 0) {
        fprintf(stderr, "create tcp socket failed[%s]!\n", strerror(errno));
        return -1;
    }
    
    ret = setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, &reuse_enable, sizeof(reuse_enable));
    if (ret != 0) {
        fprintf(stderr, "setsockopt failed[%s]!\n", strerror(errno));
        goto out;
    }
    
    bzero(&server_addr, sizeof(server_addr));
    bzero(&client_addr, sizeof(client_addr));
    client_addr_len = sizeof(client_addr);

    server_addr.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &server_addr.sin_addr);
    server_addr.sin_port = htons(port);

    ret = bind(sock_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (ret != 0) {
        fprintf(stderr, "bind failed[%s]!\n", strerror(errno));
        goto out;
    }

    ret = listen(sock_fd, 5);
    if (ret != 0) {
        fprintf(stderr, "listen failed[%s]!\n", strerror(errno));
        goto out;
    }

    ret = socketpair(PF_UNIX, SOCK_STREAM, 0, pipe_fd);
    if (ret != 0) {
        fprintf(stderr, "socketpair failed[%s]!\n", strerror(errno));
        goto out;
    }

    /* pipe_fd[0] for reading and register event. */
    add_fd(epol_fd, pipe_fd[0]);

    /* pipe_fd[1] for sending, */
    set_nonblocking(pipe_fd[1]);

    epol_fd = epoll_create(5);
    if (epol_fd < 0) {
        fprintf(stderr, "epoll create failed[%s]!\n", strerror(errno));
        goto out;
    }
    
    add_fd(epol_fd, sock_fd);

    /* add signal number. */
    add_sig(SIGTERM);
    add_sig(SIGINT);
    add_sig(SIGHUP);
    add_sig(SIGCHLD);

    stop_server = false;

    while (stop_server == false) {
    
        epol_num = epoll_wait(epol_fd, events, MAX_EVENT_NUMBER, -1);
        if (epol_num < 0) {
            fprintf(stderr, "epoll wait failed[%s]!\n", strerror(errno));
            goto out;
        } 

        for (i = 0; i < epol_num; i++) {
            fd = events[i].data.fd;
            if (fd == sock_fd) {
                /* for accetp. */
                conn_fd = accept(sock_fd, (struct sockaddr *)&client_addr, &client_addr_len);
                if (conn_fd < 0) {
                    fprintf(stderr, "accept failed[%s]!\n", strerror(errno));
                    break;
                }

                add_fd(epol_fd, conn_fd);

            } else if ((fd == pipe_fd[0]) && (events[i].events & EPOLLIN)) {
                /* pipe_fd[0] is ready status and wait for receiving data. */
                char signal[1024] = {};
                memset(signal, '\0', sizeof(signal));
                ret = recv(pipe_fd[0], signal, sizeof(signal), 0);
                if (ret < 0) {
                    continue;
                } else if (ret == 0) {
                    continue;
                } else {
                    /* 每个信号占1字节，因此按字节来逐个接收信号。*/
                    for (j = 0; j < ret; j++) {

                        switch (signal[j]) {
                            case SIGCHLD:
                                printf("SIGCHLD\n");
                                continue;
                            case SIGHUP:
                                printf("SIGHUP\n");
                                continue;
                            case SIGTERM:
                            case SIGINT:
                                stop_server = true;
                            default:
                                printf("other signal\n");
                                continue;
                        }
                    }
                }

            } else if ((fd == conn_fd) && (events[i].events & EPOLLIN)){
                
                char buf[1024] = {};
                
                memset(buf, '\0', sizeof(buf));

                ret = recv(conn_fd, buf, sizeof(buf) - 1, 0);

                if (ret < 0) {
                    
                    if ((errno == EAGAIN) || (errno == EWOULDBLOCK)) {
                        continue;
                    }

                    close(fd);

                    break;
                  
                } else if (ret == 0) {
                    close(conn_fd);
                } else {
                    send(fd, buf, ret, 0);
                }
            }
        
        }
    }

out:

    if (sock_fd > 0) {
        close(sock_fd);
    }
    
    close(pipe_fd[0]);
    close(pipe_fd[1]);

    fprintf(stdout, "hello world!\n");
    return 0;
}
