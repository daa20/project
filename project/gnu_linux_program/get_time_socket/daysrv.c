#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

#define MAX_BUFFER              (128)
#define DAYTIME_SERVER_PORT     (13)

int 
main(int argc, char *argv[])
{
    int server_fd;
    int connect_fd;
    struct sockaddr_in server_addr;
    char time_buffer[MAX_BUFFER + 1] = {};
    time_t current_time;
    
    /* 1. create a socket. */
    /*
     * AF_INET: IPV4
     * SOCK_STREAM: based on stream protocal.
     * 0: dufault vaule: TCP protocal.
     *
     * */
    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    memset(&server_addr, 0, sizeof(server_addr));

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(DAYTIME_SERVER_PORT);
    
    /* 2. bind a socket addr. */
    bind(server_fd, (struct sockaddr *)&server_addr, 
            sizeof(server_addr));

    /* 3. listen a socket. */
    /*
     * 5: max connecting number in queue.
     *
     * */
    listen(server_fd, 5);

    while (1) {
        /*4. wait for accepting a connection. */
        connect_fd = accept(server_fd, (struct sockaddr *)NULL, NULL);
        if (connect_fd >= 0) {
            current_time = time(NULL);
            snprintf(time_buffer, MAX_BUFFER, "%s\n", ctime(&current_time));
            write(connect_fd, time_buffer, strlen(time_buffer));
            close(connect_fd);
        }
    }
    return 0;
}
