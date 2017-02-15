// who.c
// open & read file UTMP file

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <utmp.h>
#include <time.h>

void show_info(struct utmp *utbufp);
void showtime(time_t);

int main(int argc, char const *argv[])
{
	struct utmp current_record;
	int utmpfd;
	int reclen = sizeof(current_record);
	if((utmpfd = open(UTMP_FILE, O_RDONLY)) == -1)
	{
		perror(UTMP_FILE);
		exit(1);
}
	while(read(utmpfd, &current_record, reclen) == reclen)
		show_info(&current_record);
	close(utmpfd);
	return 0;
}

void show_info(struct utmp *utbufp)
{
	printf("%-8.8s", utbufp->ut_name);  /*name*/
	printf("    ");
	printf("%-8.8s", utbufp->ut_line);  /*tty */
	printf("    ");
	showtime(utbufp->ut_time);          /* display the time*/
	printf("    ");
	#ifdef SHOWHOST
        printf("(%s)", utbufp->ut_host);
    #endif
	printf("\n");
}

void showtime(time_t timeval)
{

char *ctime();
char *cp;    			/*holds address of the time*/
cp=ctime(&timeval);		/*convert time to string*/
printf("%12.12s",cp+4);		/* picks 12 characters from position 4 */

}
