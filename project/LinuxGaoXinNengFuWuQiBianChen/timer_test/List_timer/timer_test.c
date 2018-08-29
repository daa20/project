#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <signal.h>


#include "sort_timer_lst.h"

#define FD_LIMIT            (65535)
#define MAX_EVENT_NUMBER    (1024)
#define TIMESLOT            (5)

static int              pipefd[2];

/* 升序链表来管理定时器 */
static sort_timer_lst   timer_lst;

static int              epollfd = 0;


static int
create_socket(const char *ip, int port) 
{
    int                     ret = -1;
    int                     sock_fd = -1;
    int                     reused = 1;
    struct sockaddr_in      server_addr = {};
    
    if (ip == NULL) {
        fprintf(stderr, "ip is %s\n", ip);
        goto out;
    }

    if (port < 0 || port >= 65536) {
        fprintf(stderr, "port is %d\n", port);
        goto out;
    }
    
    sock_fd = socket(PF_INET, SOCK_STREAM, 0);
    if (sock_fd < 0) {
        fprintf(stderr, "create socket failed[%s]!\n", strerror(errno));
        goto out;
    }
    
    ret = setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, &reused, sizeof(reused));
    if (ret != 0) {
        fprintf(stderr, "set socket address reuse failed[%s]!\n", strerror(errno));
        ret = -1;
        goto out;
    }

    bzero(&server_addr, sizeof(server_addr));
    
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    inet_pton(AF_INET, ip, &server_addr.sin_addr);

    ret = bind(sock_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (ret != 0) {
        fprintf(stderr, "bind failed[%s]!\n", strerror(errno));
        ret = -1;
        goto out;
    }

    ret = listen(sock_fd, 5);
    if (ret != 0) {
        fprintf(stderr, "listen failed[%s]\n", strerror(errno));
        ret = -1;
        goto out;
    }

out:

    return ret;

}

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
add_fd(int epollfd, int fd)
{
    struct epoll_event event = {};

    event.data.fd = fd;
    event.events = EPOLLIN | EPOLLET;

    epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &event);

    set_nonblocking(fd);
}

static void
sig_handler(int sig)
{
    int save_errno = errno;
    int msg = sig;

    send(pipefd[1], (char *)&msg, 1, 0);

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

static void
cb_func(client_data *user_data)
{
    if (user_data != NULL) {
        epoll_ctl(epollfd, EPOLL_CTL_DEL, user_data->sockfd, 0);

        close(user_data->sockfd);

        fprintf(stdout, "close fd %d\n", user_data->sockfd);
    }
}

static void
timer_handler(void)
{
    /*定时处理任务，实际上就是调用tick函数*/
    timer_lst.tick();

    /* 
     * 因为一次alarm调用只会引起一次SIGALRM信号，所以需要重新定时，
     * 不断触发SIGALRM信号。
     * */
    alarm(TIMESLOT);
}

static int
epoll_process(int sock_fd)
{
    int                     ret = -1;
    bool                    stop_server = false;
    struct epoll_event      events[MAX_EVENT_NUMBER] = {};
    
    epollfd = epoll_create(5);
    if (epollfd < 0) {
        fprintf(stderr, "create epoll failed[%s]!\n", strerror(errno));
        ret = -1;
        return ret;
    }

    ret = socketpair(PF_UNIX, SOCK_STREAM, 0, pipefd);
    if (ret != 0) {
        fprintf(stderr, "socketpair failed[%s]!\n", strerror(errno));
        ret = -1;
        return ret;
    }

    set_nonblocking(pipefd[1]);
    add_fd(epollfd, pipefd[0]);

    /*添加信号处理函数*/
    add_sig(SIGALRM);
    add_sig(SIGTERM);
    

    client_data *users = new client_data[FD_LIMIT];
    bool        timeout = false;
    alarm(TIMESLOT); /*定时*/

    while (stop_server == false) {
        
        int number = epoll_wait(epollfd, events, MAX_EVENT_NUMBER, -1);
        
        if ((number < 0) && (errno != EINTR)) {
            fprintf(stderr, "epoll failure[%s]!\n", strerror(errno));
            break;
        } 

        for (int i = 0; i < number; i++) {
            int sockfd = events[i].data.fd;

            /*处理新到的客户连接*/
            if (sockfd == sock_fd) {
            
                struct sockaddr_in  client_addr = {};
                socklen_t           client_addr_len = 0;
                int                 connfd = -1;
                
                client_addr_len = sizeof(client_addr);
                connfd = accept(sock_fd, (struct sockaddr *)&client_addr, &client_addr_len);
                if (connfd < 0) {
                    fprintf(stderr, "accept failed[%s]!\n", strerror(errno));
                    break;
                }

                add_fd(epollfd, connfd);

                users[connfd].address = client_addr;
                users[connfd].sockfd = connfd;

                /*
                 * 创建定时器，设置其回调函数与超时时间，然后绑定定时器与用户数据，
                 * 最后将定时器添加到链表timer_lst中。
                 * */
                util_timer *timer = new util_timer;
                timer->user_data = &users[connfd];
                timer->cb_func = cb_func;

                time_t cur = time(NULL);
                timer->expire = cur + 3 * TIMESLOT;
                users[connfd].timer = timer;
                timer_lst.add_timer(timer);
            } 
            /*处理信号*/
            else if((sockfd == pipefd[0]) && (events[i].events & EPOLLIN)) {
                //int sig;
                char signals[1024] = {};

                ret = recv(pipefd[0], signals, sizeof(signals), 0);
                if (ret == -1) {
                    /*handle the error*/
                    continue;
                } else if (ret == 0) {
                    continue;
                } else {
                    for (int i = 0; i < ret; i++) {
                        switch (signals[i]) {
                            case SIGALRM:
                                {
                                    /*
                                     * 用timeout变量标记有定时任务需要处理，
                                     * 但不立即处理定时器任务。因为定时任务的优先级
                                     * 不是很高，我们优先处理其他更重要的任务。
                                     * */
                                    timeout = true;
                                    break;
                                }
                            case SIGTERM:
                                {
                                    stop_server = true;
                                }
                            default:
                                {
                                    fprintf(stderr, "Unknown signal: %d\n", signals[i]);
                                    break;
                                }
                        }
                    }
                }
            }

            /*处理客户连接上接收到的数据*/
            else if (events[i].events & EPOLLIN) {
                memset(users[sockfd].buf, '\0', BUFFER_SIZE);
                ret = recv(sockfd, users[sockfd].buf, BUFFER_SIZE, 0);
                fprintf(stdout, "get %d bytes of client data %s from %d\n",
                        ret, users[sockfd].buf, sockfd);
                util_timer *timer = users[sockfd].timer;

                if (ret < 0) {
                    /*如果发生错误，则关闭连接，并移除其对应的定时器*/
                    if (errno != EAGAIN) {
                        cb_func(&users[sockfd]);

                        if (timer != NULL) {
                            timer_lst.del_timer(timer);
                        }
                    }
                } else if (ret == 0) {
                    /*如果对方已经关闭连接，则我们也关闭连接，并移除对应的定时器*/
                    cb_func(&users[sockfd]);

                    if (timer != NULL) {
                        timer_lst.del_timer(timer);
                    }
                } else {
                    /*
                     * 如果某个客户连接上有数据可读，则我们要调整该定时器，
                     * 以延迟连接被关闭的时间。
                     * */
                    if (timer != NULL) {
                        time_t cur = time(NULL);
                        timer->expire = cur + 3 * TIMESLOT;
                        fprintf(stdout, "adjust timer once\n");
                        timer_lst.adjust_timer(timer);
                    }
                }
            } else {
                //other
            }
        }

        /*
         * 最后处理定时事件，因为I/O事件有更高的优先级。
         * 当然，这样做将导致定时任务不能精确地按照预期的时间执行。
         *
         * */
        if (timeout == true) {
            timer_handler();
            timeout = false;
        }
    
    }

    
    if (pipefd[0] > 0) {
        close(pipefd[0]);
    }
    
    if (pipefd[1] > 0) {
        close(pipefd[1]);
    }

    if (users != NULL) {
        delete [] users;
    }

    return ret;
}


static int
main_func(const char *ip, int port)
{
    int     ret = -1;
    int     sock_fd = -1;
    
    sock_fd = create_socket(ip, port);
    if (sock_fd == -1) {
        ret = -1;
        goto out;
    }

    ret = epoll_process(sock_fd);
    if (ret == -1) {
        ret = -1;
        goto out;
    }

out:

    if (sock_fd >= 0)  {
        close(sock_fd);
    }

    return ret;
}

int
main(int argc, char *const argv[])
{
    int             ret = -1;
    int             port = -1;
    const char      *ip = NULL;

    if (argc != 3) {
        fprintf(stderr, "\n=================Usage:===============\n"
                "%s 127.0.0.1 8091"
                "\n====================================\n", argv[0]);
        return -1;
    }

    ip = argv[1];
    port = atoi(argv[2]);

    ret = main_func(ip, port);
    if (ret == -1) {
        
        fprintf(stderr, "main_func quit!\n");

    } else {
        fprintf(stdout, "quiting!\n");
        ret = 0;
    }

    fprintf(stdout, "hello world!\n");
    return ret;
}
