#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

#define PATHNAME "/tmp/cmd_mkfifo"
#define MAX_LINE 80

int 
main(int argc, char *argv)
{
    char buffer[MAX_LINE + 1] = {};
    FILE *pfp = NULL;

    pfp = fopen(PATHNAME, "r");
    if (pfp == NULL) {
        fprintf(stderr, "open %s failed!\n", PATHNAME);
        return -1;
    } 
    
    while (1) {
        fgets(buffer, MAX_LINE, pfp);
        fprintf(stdout, "%s\n", buffer);
    }

    fclose(pfp);

    return 0;
}
