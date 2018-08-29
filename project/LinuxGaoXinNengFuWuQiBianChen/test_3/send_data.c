#include <stdio.h>
#include <arpa/inet.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <assert.h>
#include <stdlib.h>

static void
Usage(const char *bin)
{
    fprintf(stderr, "\n================Usage:================\n"
            "%s 127.0.0.1 8091\n"
            "=========================================\n", bin);
}


int
main(int argc, char *const argv[])
{
    const char          *ip = NULL;
    unsigned short int  port = 0; 
    struct sockaddr_in  server_addr = {};
    int                 sock_fd = -1;
    int                 ret = -1;

    if (argc <= 2) {
        Usage(argv[0]);
        return -1;
    }
    
    bzero(&server_addr, sizeof(server_addr));

    server_addr.sin_family = PF_INET;
    ip = argv[1];
    inet_pton(AF_INET, ip, &server_addr.sin_addr);
    port = atoi(argv[2]);
    server_addr.sin_port = htons(port);

    sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    assert(sock_fd > 0);

    ret = connect(sock_fd, (const struct sockaddr *)&server_addr, sizeof(server_addr));
    if (ret != 0) {
        fprintf(stderr, "connect %d failed![%s]\n", sock_fd, strerror(errno));
        return -1;
    } else {
    
        const char *normal_data = "hello";
        const char *oob_data = "123";
        send(sock_fd, normal_data, strlen(normal_data), 0);
        send(sock_fd, oob_data, strlen(oob_data), MSG_OOB);
        send(sock_fd, normal_data, strlen(normal_data), 0);

    }

    close(sock_fd);
  
    printf("send data!\n");
    return 0;
}
