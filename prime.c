#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>

void sighandler(int);
int currentPrime=0;
int main()
{
  int currentNum = 2;
  signal(SIGINT, sighandler);
   while(1)
   {
     currentNum += 1;
     int x = 0;
     int divisors = 0;
     for(x=1;x<=currentNum;x++)
     {
         if(currentNum%x==0)
         divisors++;
     }
     if(divisors<3){
       currentPrime=currentNum;
     }
     sleep(1);
   }
   return 0;
}

void sighandler(int signum)
{
   char buff[1]={""};
   printf("\t%d\tQuit [y/n]?", currentPrime);
   scanf("%s",buff);
   if(strcmp(buff,"y")==0 || strcmp(buff,"Y")==0)
   {
      exit(1);
   }
}
