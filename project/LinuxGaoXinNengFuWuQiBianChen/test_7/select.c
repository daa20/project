#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <assert.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <sys/time.h>

static void
Usage(const char *bin) 
{
    fprintf(stderr, "\n============================\n"
            "%s 127.0.0.1 8092"
            "\n==========================\n", bin);
}


int 
main(int argc, char *const argv[])
{
    int                 ret = -1;
    int                 sock_fd = -1;
    int                 conn_fd = -1;
    unsigned short int  port = 0;
    const char          *ip = NULL;
    struct sockaddr_in  server_addr = {};
    struct sockaddr_in  client_addr = {};
    socklen_t           client_addr_len = -1;
    char                IP[INET_ADDRSTRLEN] = {};

    if (argc != 3) {
        Usage(argv[0]);
        return -1;
    }

    ip = argv[1];
    port = atoi(argv[2]);

    bzero(&server_addr, sizeof(server_addr));
    bzero(&client_addr, sizeof(client_addr));
    memset(IP, '\0', INET_ADDRSTRLEN);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    inet_pton(AF_INET, ip, &server_addr.sin_addr);

    sock_fd = socket(PF_INET, SOCK_STREAM, 0);
    assert(sock_fd > 0);

    ret = bind(sock_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    //assert(ret != -1);
    if (ret != 0) {
        fprintf(stderr, "bind %d failed![%s]\n", sock_fd, strerror(errno));
        close(sock_fd);
        return -1;
    }

    ret = listen(sock_fd, 5);
    //assert(ret != -1);
    if (ret != 0) {
        fprintf(stderr, "listen %d failed![%s]\n", sock_fd, strerror(errno));
        close(sock_fd);
        return -1;
    }

    client_addr_len = sizeof(client_addr);
    conn_fd = accept(sock_fd, (struct sockaddr *)&client_addr, &client_addr_len);
    if (conn_fd < 0) {

        fprintf(stderr, "accept failed![%s]\n", strerror(errno));
    } else {
        
        char buf[1024] = {};
        int nfds = conn_fd + 1;
        fd_set readfds;
        fd_set errorfds;

        FD_ZERO(&readfds);
        FD_ZERO(&errorfds);

        inet_ntop(AF_INET, &client_addr.sin_addr, IP, INET_ADDRSTRLEN);

        while (1) {
            memset(buf, '\0', 1024);

            FD_SET(conn_fd, &readfds);
            FD_SET(conn_fd, &errorfds);

            ret = select(nfds, &readfds, NULL, &errorfds, NULL);
            if (ret < 0) {
                fprintf(stderr, "select failed![%s]\n", strerror(errno));
                continue;
            }

            /* read event handle. */
            if (FD_ISSET(conn_fd, &readfds)) {

                ret = recv(conn_fd, buf, sizeof(buf) - 1, 0);
                if (ret <= 0) {
                    break;
                }

                fprintf(stdout, "recv normal data: %s[length: %d] from %s:%d\n",
                        buf, ret, IP, ntohs(client_addr.sin_port));
            }

            /* error event handle. */
            if (FD_ISSET(conn_fd, &errorfds)) {
                ret = recv(conn_fd, buf, sizeof(buf) - 1, MSG_OOB);
                if (ret <= 0) {
                    break;
                }

                fprintf(stdout, "recv OOB data: %s[length: %d] from %s:%d\n",
                        buf, ret, IP, ntohs(client_addr.sin_port));
            }
        }

        close(conn_fd);
    }
    
    close(sock_fd);

    fprintf(stdout, "hello world~\n");
    return 0;
}
