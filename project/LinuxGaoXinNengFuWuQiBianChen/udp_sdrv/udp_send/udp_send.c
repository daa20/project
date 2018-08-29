#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

static void
usage(const char *bin)
{
    fprintf(stdout, "\n========================Usage=====================\n"
            "%s 127.0.0.1 8092\n"
            "========================end=====================\n", bin);
}

int main(int argc, char *const argv[])
{
    int sock_send_fd;
    struct sockaddr_in addr;
    char buff[20];
    memset(&addr,0,sizeof(struct sockaddr_in));

    if (argc != 3) {
       usage(argv[0]);
       return -1;
    }

    if ((sock_send_fd = socket(AF_INET, SOCK_DGRAM,0)) < 0)
    {
        perror("socket create error\n");
        exit(1);
    }

    addr.sin_family = AF_INET;
    //addr.sin_port = htons(27350);
    addr.sin_port = htons(atoi(argv[2]));
    //addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_addr.s_addr = inet_addr(argv[1]);
    if (addr.sin_addr.s_addr == INADDR_NONE)
    {
        printf("Incorrect ip address!\n");
        close(sock_send_fd);
        exit(1);
    }

    sprintf(buff,"%d,%d,%d,%d,%d",1,2,3,4,5);
    while (1)
    {
        int n;
        n = sendto(sock_send_fd , buff, strlen(buff), 0, (struct sockaddr *)&addr, sizeof(addr));
        if (n < 0)
        {
            perror("sendto");
            close(sock_send_fd);
            break;
        }

        return 0;
    }
    return 0;
}
