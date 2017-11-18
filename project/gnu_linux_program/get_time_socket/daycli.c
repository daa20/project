#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#define MAX_BUFFER              (128)
#define DAYTIME_SERVER_PORT     (13)

int
main(int argc, char *argv[])
{
    int                 connect_fd;
    int                 in;
    int                 index = 0;
    int                 limit = MAX_BUFFER;

    struct sockaddr_in  server_addr;
    char                time_buffer[MAX_BUFFER + 1] = {};

    connect_fd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_port = htons(DAYTIME_SERVER_PORT);

    connect(connect_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));

    while((in = read(connect_fd, &time_buffer[index], limit)) > 0) {
        index = index + in;
        limit = limit - in;
    }

    time_buffer[index] = '\0';

    fprintf(stdout, "receive:\n%s\n", time_buffer);

    close(connect_fd);

    return 0;
}
