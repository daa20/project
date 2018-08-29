#include <sys/types.h>
#include <sys/socket.h>
#include <pthread.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>



//#define SERV_PORT 8090

static void
usage(const char *bin)
{
    fprintf(stdout, "\n====================Usage:===================\n"
            "%s 8092\n"
            "====================end===================\n", bin);
}


int main(int argc, char **argv)
{


    int sock_fd;
    char rcv_buff[512];
    struct sockaddr_in client_addr;
    struct sockaddr_in server_addr;
    int client_len;
    int rcv_num = -1;
    
    if (argc != 2) {
        usage(argv[0]);
        return -1;
    }

    if ((sock_fd = socket(AF_INET, SOCK_DGRAM,0)) < 0)
    {
        perror("socket create error\n");
        exit(1);
    }

    memset(&server_addr,0,sizeof(struct sockaddr_in));

    server_addr.sin_family = AF_INET;
    //server_addr.sin_port = htons(SERV_PORT);
    server_addr.sin_port = htons(atoi(argv[1]));
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    client_len = sizeof(struct sockaddr_in);

    if (bind(sock_fd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr_in)) < 0)
    {
        perror("bind error.\n");
        exit(1);
    }

    while (1)
    {
        rcv_num= recvfrom(sock_fd, rcv_buff, sizeof(rcv_buff), 0, (struct sockaddr*)&client_addr, &client_len);
        if (rcv_num>0)
        {
            rcv_buff[rcv_num] = '\0';
            printf("%s %u says: %s\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port), rcv_buff);

        }
        else
        {
            perror("recv error\n");
            break;
        }
    }
    close(sock_fd);
    return 0;
}
