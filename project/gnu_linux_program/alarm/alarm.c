#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>

#define MAX_LINE    (80)


void 
wakeup(int signum)
{
    raise(SIGUSR1);
}

int
main(int argc, char *argv[])
{
    char buffer[MAX_LINE + 1] = {};
    int ret = 0;

    signal(SIGALRM, wakeup);

    printf("You have 3 seconds to enter the password!\n");

    alarm(3);

    ret = read(0, buffer, MAX_LINE);

    alarm(0);

    if (ret > 0) {
        buffer[strlen(buffer) - 1] = '\0';
        printf("User enter %s\n", buffer);
    } else {
        ; 
    }

    return 0;
}
