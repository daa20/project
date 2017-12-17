#include <stdio.h>
#include <string.h>

#define TST_OK          (0)
#define TST_ERROR       (-1)

#define TST_VERSION     "1.0.0"


typedef unsigned int u_int;
typedef unsigned char u_char;


static u_int    tst_show_help;
static u_int    tst_show_version;
static u_char   *tst_conf_file;
static u_char   *tst_signal;

static u_int tst_get_options(int argc, char *const *argv);
static void tst_show_version_info(void);

int 
main(int argc, char *const argv[])
{
    if (tst_get_options(argc, argv) == TST_ERROR) {
        return TST_ERROR;
    }

    if (tst_show_version == 1) {
        tst_show_version_info();
    }

    if (tst_signal) {
        fprintf(stdout, "signal: %s\n", tst_signal);
        //return tst_signal_process(tst_signal);
    }

    fprintf(stdout, "OK!\n");
    
    return TST_OK;
}

static u_int 
tst_get_options(int argc, char *const *argv)
{
    u_int   i = 0;
    u_char  *p = NULL;

    for (i = 1; i < argc; i++) {

        p = (u_char *)argv[i];
        
        if (*p++ != '-') {
            fprintf(stderr, "invalid option: \"%s\"\n", argv[i]);
            return TST_ERROR;
        }

        while (*p) {
            switch (*p++) {
                case '?':
                case 'h':
                    tst_show_help = 1;
                    tst_show_version = 1;
                    break;

                case 'v':
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
                case 's':
                    if (*p) {
                    
                        tst_signal = p;
                   
                    } else if (argv[++i]) {
                       
                        tst_signal = (u_char *)argv[i];

                    } else {
                        fprintf(stderr, "option: \"-s\" requires parameter.\n");
                        return TST_ERROR;
                    }
                    
                    if (strcmp((char *)tst_signal, "quit") == 0
                            || strcmp((char *)tst_signal, "stop") == 0
                            || strcmp((char *)tst_signal, "reopen") == 0
                            || strcmp((char *)tst_signal, "reload") == 0) {
                            
                        goto next;
                    
                    } 

                    fprintf(stderr, "invalid option: \"-s %s\"\n", tst_signal);
                    return TST_ERROR;
                default:
                    fprintf(stderr, "invalid option: \"%c\"\n", *(p-1));
                    return TST_ERROR;
            }
        }

    next: 
        continue;

    }
    return TST_OK;
}

static void 
tst_show_version_info(void)
{
    fprintf(stdout, "Version: %s\n", TST_VERSION);
    
    if (tst_show_help == 1) {
        fprintf(stdout, "Usage: signal.bin [-?hv] [-c file name].\n" \
                "-?, -h         : this help.\n"\
                "-v             : show version.\n"\
                "-c             : set configure file.\n");
    }
    
}
