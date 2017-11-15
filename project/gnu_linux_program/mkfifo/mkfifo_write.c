#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>

#define PATHNAME "/tmp/cmd_mkfifo"

int 
main(int argc, char *argv[])
{
    int ret = -1;
    FILE *pfp = NULL;

    ret = mkfifo(PATHNAME, S_IFIFO | 0666);
    if (ret == 0) {
        pfp = fopen(PATHNAME, "w+");
        if (pfp == NULL) {
            fprintf(stderr, "open %s failed!\n", PATHNAME);
            return -1;
        }

        while (1) {
            fprintf(pfp, "Here is a test string!\n");
            fprintf(stdout, "Here is a test string!\n");
            sleep(5);
        }
        
        fclose(pfp);
    } else {
        fprintf(stderr, "make create mkfifo failed![%s]\n", strerror(errno));
    }
    return 0;
}
