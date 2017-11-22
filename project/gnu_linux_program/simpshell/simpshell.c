#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>


#define MAX_LINE    (80)

int 
main(int argc, char *argv[])
{
    int     status;
    pid_t   child_pid;
    char    cmd[MAX_LINE + 1] = {};
    char    *sret = NULL;

    while(1) {
        printf("myshell> ");
        sret = fgets(cmd, sizeof(cmd), stdin);
        if (sret == NULL) {
            exit(-1);
        }

        cmd[strlen(cmd) - 1] = '\0';

        if (strncmp(cmd, "bye", strlen("bye")) == 0) {
            exit(0);
        }

        child_pid = fork();

        if (child_pid == 0) {
            execlp(cmd, cmd, NULL);
        } else if (child_pid > 0) {
            waitpid(child_pid, &status, 0);
        } else {
            printf("error: create child process failed![%s]\n", strerror(errno));
            exit(0);
        }
        printf("\n");
    }
    return 0;
}
