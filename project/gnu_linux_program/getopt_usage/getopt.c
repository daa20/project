#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


int 
main(int argc, char *const argv[])
{
	int c = 0;

	while ((c = getopt(argc, argv, "hv:f:d")) != -1) {

		switch (c) {
			case 'h':
				printf("Help menu.\n");
				break;

			case 'v':
				printf("Verbose level: %d\n", atoi(optarg));
				break;

			case 'f':
				printf("File name is: %s\n", optarg);
				break;

			case 'd':
				printf("Debuf mode.\n");
				break;

			case '?':
				printf("Unknown option: %c\n", optopt);
				break;

			default:
				printf("Unknown directive!\n");
				return -1;
		}

	}

	for (c = optind; c < argc; c++) {
		printf("Non option %s\n", argv[c]);
	}

	/* Other... */
	return 0;
}
