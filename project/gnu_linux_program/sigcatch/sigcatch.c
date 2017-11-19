#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void 
catch_ctlc(int sig_num)
{
    fprintf(stdout, "Caught, Control-C\n");

    fflush(stdout);

    return;
}


int
main(int argc, char *argv[])
{
    signal(SIGINT, catch_ctlc);

    fprintf(stdout, "Go ahead, make my day.\n");

    pause();

    return 0;
}
