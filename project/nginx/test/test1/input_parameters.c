#include <stdio.h>
#include <unistd.h>

#define TST_OK      (0)
#define TST_ERROR   (-1)

#define TST_VERSION "1.0.0"


typedef unsigned int        u_int;
typedef unsigned char       u_char;


static u_int        tst_show_help;
static u_int        tst_show_version;
static u_int        tst_show_configure;
static u_char       *tst_conf_file;

static void tst_show_version_info(void);
static u_int tst_get_options(int argc, char *const argv[]);


int
main(int argc, char *argv[])
{
    if (tst_get_options(argc, argv) == TST_ERROR) {
        return TST_ERROR;
    }
    
    if (tst_show_version == 1) {
        tst_show_version_info();
    }
    
    if (tst_conf_file != NULL) {
        fprintf(stdout, "configure file: %s\n", tst_conf_file);
    }
    return 0;
}

static void 
tst_show_version_info(void)
{
    fprintf(stdout, "TST version: %s\n", TST_VERSION);

    if (tst_show_help == 1) {
    
    }

    if (tst_show_configure == 1) {
    
    }
}

static u_int
tst_get_options(int argc, char *const argv[])
{
    int i = 0;
    u_char *p = NULL;

    for (i = 1; i < argc; i++) {
        
        p = (u_char *)argv[i];

        if ((*p++) != '-') {
            fprintf(stderr, "invalid option: \"%s\"\n", argv[i]);
            return TST_ERROR; 
        }

        while(*p) {
            switch (*p++) {
                case '?':
                case 'h':
                    tst_show_help = 1;
                    tst_show_version = 1;
                    break;
                case 'v':
                    tst_show_version = 1;
                    break;
                case 'V':
                    tst_show_configure = 1;
                    tst_show_version = 1;
                    break;
                case 'c':
                    if (*p) {
                        tst_conf_file = p;
                        goto next;
                    }

                    if (argv[++i]) {
                        tst_conf_file = (u_char *)argv[i];
                        goto next;
                    }
                    
                    fprintf(stderr, "option \"-c\" requires file name.\n");
                    return TST_ERROR;
                default:
                    fprintf(stderr, "invalid option: \"%c\"\n", *(p - 1));
                    return TST_ERROR;
            }
        }   

    next:
        continue;
    }

    return TST_OK;
}
