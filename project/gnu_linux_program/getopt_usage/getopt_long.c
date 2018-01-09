#include <stdio.h>
#include <getopt.h>

static struct option longopts[] = {
	{
		"start", 0, NULL, 's'
	},
	{
		"stop", 0, NULL, 't'
	},
	{
		"command", 1, NULL, 'c' 
	},
	{
		NULL, 0, NULL, 0
	}
};


int 
main(int argc, char *const argv[])
{
	int c = 0;
	
	while ((c = getopt_long(argc, argv, "stc:", longopts, NULL)) != -1) {
		switch (c) {
			case 's':
				printf("Start!\n");
				break;

			case 't':
				printf("stop!\n");
				break;

			case 'c':
				printf("Command %s!\n", optarg);
				break;

			case '?':
				printf("Unknown directive: %c.\n", optopt);
				break;

			default:
				printf("Unknown option!\n");
				break;
		}
	}

#if 0
	while (optind < argc) {
		printf("No option: %s\n", argv[optind++]);
	}
	for (c = optind; c < argc; c++) {
		printf("Non option: %s\n", argv[c]);
	}
#endif

	/* Other... */

	return 0;
}
