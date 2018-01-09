#include <stdio.h>
#include <time.h>


int 
main(int argc, char *const argv[])
{
	time_t 		current_time;
	struct tm 	*tm_time;

	current_time = time(NULL);
	tm_time = localtime(&current_time);

	printf("Localtime: %04d-%02d-%02d %02d:%02d:%02d\n", 
			tm_time->tm_year, tm_time->tm_mon, 
			tm_time->tm_mday, tm_time->tm_hour, 
			tm_time->tm_min, tm_time->tm_sec);

	printf("Ctime: %s\n", ctime(&current_time));

	printf("from asctime/localtime: %s\n", asctime(tm_time));

	printf("\n-----------------\n");

	tm_time = gmtime(&current_time);
	printf("gmtime: %04d-%02d-%02d %02d:%02d:%02d\n", 
			tm_time->tm_year, tm_time->tm_mon, 
			tm_time->tm_mday, tm_time->tm_hour, 
			tm_time->tm_min, tm_time->tm_sec);
	
	printf("from asctime/gmtime: %s\n", asctime(tm_time));

	printf("\n-----------------\n");

	current_time = mktime(tm_time);
	printf("from ctime/mktime: %s\n", ctime(&current_time));

	return 0;
}
