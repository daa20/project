#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>


int 
main(int argc, char *argv[])
{
    pid_t my_pid;
    pid_t my_parent_pid;
    gid_t my_gid;
    uid_t my_uid;

    my_pid = getpid();
    my_parent_pid = getppid();
    my_gid = getgid();
    my_uid = getuid();

    fprintf(stdout, "my process id is : %d\n", my_pid);

    fprintf(stdout, "my parent's process id is %d\n", my_parent_pid);

    fprintf(stdout, "my group id is %d\n", my_gid);

    fprintf(stdout, "my user id is %d\n", my_uid);

    return 0;
}
