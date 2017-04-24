#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <utmp.h>
#include <time.h>

int main (int ac, char *av[])
{
        int fd,utmpfile,foundTar;
        struct utmp utmpp;
        char msg[128], buf[BUFSIZ];
        char eof[] = "EOF\n";
        char pline[50];

        if(ac != 3)
        {
                fprintf(stderr,"Incorrect Usage");
                exit(1);
        }

        if( (utmpfile = open(UTMP_FILE, O_RDONLY)) == -1 )
        {
                perror(UTMP_FILE); //error for  UTMP file
                exit(1);
        }


        if( (fd = open(av[2], O_WRONLY)) == -1 )
        {
                perror(av[2]); //error for file not found or no permission
                exit(1);
        }

        while( read(utmpfile, &utmpp, sizeof(utmpp)) == sizeof(utmpp) )
        {
                if(strcmp(utmpp.ut_user,av[1]) == 0)
                {
                        foundTar++;
                        char *cp = ctime(&(utmpp.ut_time)); //time
                        strcpy(msg,"\nMessage from ");
                        strcat(msg, utmpp.ut_user); //user
                        strcat(msg,"@");
                        strcat(msg, utmpp.ut_host); //host address
			strcat(msg," on ");
 			strcat(msg, utmpp.ut_line);
 			strcat(msg," on ");
 			strcat(msg,cp); //display time
 			strcat(msg,"\n");
 break;
}
}

if(foundTar==0)
{
printf("Target not found");
exit(1);
}

write( fd, msg, strlen(msg) );
while( fgets( buf, BUFSIZ, stdin ) != NULL )
if( write( fd, buf, strlen(buf) ) == -1 )
 break;

write( fd, eof, strlen(eof) );
close(utmpfile);
      close(fd);
      return 0;
}

