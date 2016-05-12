
#include <stdio.h>
#include <utmp.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include <sys/types.h>
#include <fcntl.h>



#define SHOWHOST
#define NRECS 16
#define NULLUT ((struct utmp *) NULL)
#define UTSIZE (sizeof (struct utmp))

static char utmpbuf[NRECS *UTSIZE];
static int num_recs;
static int cur_rec;
static int fd_utmp = -1;

void show_info(struct utmp*);
void showtime(time_t);

int main()
{
	struct utmp *utbufp, /* holds pointer to next rec */
		*utmp_next();
	if(utmp_open(UTMP_FILE) == -1){
		perror(UTMP_FILE);
		exit(1);
	}
	while((utbufp = utmp_next()) != ((struct utmp *)NULL))
		show_info(utbufp);
	utmp_close();
	return 0;
}

void show_info(struct utmp *utbufp)
{
	if(utbufp->ut_type != USER_PROCESS)
		return;
	printf("%-8.8s",utbufp->ut_name); /* the logname*/
	printf(" ");
	printf("%-8.8s",utbufp->ut_line);
	printf(" ");
	showtime(utbufp->ut_time);
#ifdef SHOWHOST
	if(utbufp->ut_host[0] != '\0')
		printf(" (%s)", utbufp->ut_host); /* the host */
#endif    /*newline */
	printf("\n");
}
void showtime(long timeval)
/*
* displays time in a format fit for human consumption 
* uses ctime to build a string then npicks parts out of it 
* note: %12,12s prints a string 12 chars wide and LIMITS
*it to 12 chars.
*/

{ 
	char *cp; /* to hold address of time*/
	cp  = ctime(&timeval); /*convert time to string(*/
	
	printf("%12.12s",cp+4);
}
utmp_open( char *filename)
{
	fd_utmp = open(filename, O_RDONLY);
	cur_rec = num_recs = 0;
	return fd_utmp;
}
struct utmp *utmp_next()
{
	struct utmp *recp;
	if(fd_utmp == -1)
		return NULLUT;
	if(cur_rec == num_recs && utmp_reload() == 0)
		return NULLUT;

	recp = (struct utmp *) &utmpbuf[cur_rec *UTSIZE];
	cur_rec++;
	return recp;
}
int utmp_reload()
{
	int amt_read;
	amt_read = read( fd_utmp, utmpbuf, NRECS * UTSIZE);
	num_recs = amt_read/UTSIZE;
	cur_rec = 0;
	return num_recs;
}
utmp_close()
{	
	if(fd_utmp != -1)
		close(fd_utmp);
}





