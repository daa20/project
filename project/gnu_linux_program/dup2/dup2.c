#include <stdio.h>
#include <unistd.h>

#define MAX_LINE 80

int 
main(int argc, char *argv[])
{
    int my_pipe[2];

    if (pipe(my_pipe) == 0) {
        if (fork() == 0) { //children
            close(1); //close stdout
            dup2(my_pipe[1], 1);
            close(my_pipe[0]);
            execlp("ls", "ls", "-l", NULL);  // output result
        } else { //parent
            close(0); //close stdin
            dup2(my_pipe[0], 0);
            close(my_pipe[1]);
            execlp("wc", "wc", "-l", NULL); // input result from my_pipe[1]
        }
    }
    return 0;
}
