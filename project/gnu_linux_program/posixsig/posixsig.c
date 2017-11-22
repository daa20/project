#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>

static int stop_child = 0;


void 
sig_handler(int sig, siginfo_t *siginfo, void *ignore)
{
    printf("Got SIGUSR1 from %d\n", siginfo->si_pid);
    
    stop_child = 1;

    return;
}


int 
main(int argc, char *argv[])
{
    pid_t child_pid;

    int status;
    int role = -1;

    child_pid = fork();

    if (child_pid == 0) {
        struct sigaction act;
        printf("Child: This is Child process (pid: %d)\n",
                getpid());
        act.sa_flags = SA_SIGINFO;
        act.sa_sigaction = sig_handler;
        sigaction(SIGUSR1, &act, 0);

        printf("Child Waiting...\n");
        while (!stop_child);

        role = 1;
    } else if (child_pid > 0) {
        printf("Parent: This is the parent process (pid %d)\n",
                getpid());
        
        /* Let the Child init. */
        sleep(1);
        
        kill(child_pid, SIGUSR1);
        
        child_pid = wait(&status);

        role = 0;
    } else {
        printf("%s: Exiting...\n", ((role == 0)?("Parent"):("Child")));
    }

    return 0;
}
