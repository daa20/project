#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>

void
usr1_handler(int sig_num)
{
    fprintf(stdout, "Parent (%d) got the SIGUSR1\n", getpid());
}


int
main(int argc, char *argv[])
{
    pid_t   ret;
    int     status;
    int     role = -1;

    ret = fork();
    if (ret > 0) {
        fprintf(stdout, "This is the parent process (pid %d)\n",getpid());
        signal(SIGUSR1, usr1_handler);

        role = 0;

        pause();

        fprintf(stdout, "Parent: Awaiting child exit\n");

        ret = wait(&status);
    } else if (ret == 0) {
        fprintf(stdout, "Child: This is the child process (pid %d)\n",
                getpid());
        role = 1;

        sleep(1);

        fprintf(stdout, "Child: Sending SIGUSR1 to pid %d\n", getpid());

        kill(getppid(), SIGUSR1);

        sleep(2);
    } else {
        fprintf(stderr, "Parent: Error trying to fork() (%s)\n",
                strerror(errno));
    }

    fprintf(stdout, "%s Exiting...\n",
            (role == 0) ? ("Parent") : ("Child"));
    return 0;
}
