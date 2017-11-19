#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>

int
main(int argc, char *argv[])
{
    pid_t ret = -1;
    int status;
    int index = 0;
    int role = -1;
    
    ret = fork();

    if (ret > 0) {
        fprintf(stdout, "Parent: [pid: %d]\n", getpid());
        for (index = 0; index < 6; index++){
            fprintf(stdout, "Parent: At count %d\n", index);
            sleep(1);
        }

        ret = wait(&status);

        role = 0;
    } else if (ret == 0) {
        fprintf(stdout, "Child: [pid: %d]\n", getpid());

        for (index = 0; index < 6; index++){
            fprintf(stdout, "Child: At count %d\n", index);
            sleep(1);
        }

        role = 1;
    } else {
        fprintf(stdout, "Parent: error{%s}\n", strerror(errno));
    }

      
    fprintf(stdout, "%s: Exiting...\n", ((role == 0) ? ("Parent") : ("Child")));
    return 0;
}
