#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

void search(char* query, char* drct);
struct stat fileInfo;

int main(int argc, char** argv)
{
    switch(argc)
    {
    case 0: break;
    case 2:
        search(argv[1], ".");
        break;
    case 3:
        search(argv[1], argv[2]); // query then path
        break;
    default: printf("usage: ./main [Query] [Path] ...\n");
    }
    return 0;
}

char* permissions(mode_t s)
{
    int i;
    char *p;
    static char perms[10];
    p = perms;
    strcpy(perms, "---------");
    for (i=0; i < 3; i++) {
        if (s & (DT_DIR  >> i)) *p = '-';
        p++;
        if (s & (S_IREAD >> i*3)) *p = 'r';
        p++;
        if (s & (S_IWRITE >> i*3)) *p = 'w';
        p++;
      }
      return(perms);
  }

  void search(char*  query, char* drct)
  {
      DIR *dir = opendir(drct);
      if(dir==NULL)
           {
                   return;
           }
        struct dirent *d;
        char buff[512]={0};
        char filet[512]={0};
        int length=0;
        int len=0;
        int count=0;
      while((d=readdir(dir))!=NULL)
      {
          stat(d->d_name, &fileInfo);
          char* lowerFile = malloc(strlen(drct) + 1 + strlen(d->d_name) + 1);
          strcpy(lowerFile, drct);
          strcat(lowerFile, "/");
           strcat(lowerFile, d->d_name);
          int i=0;
           if(!strcmp(d->d_name, query) || strstr(d->d_name, query)!=NULL)
           {
              strcpy(buff,lowerFile);
              strcpy(filet,d->d_name);
              length=strlen(filet);
              len= strlen(lowerFile)-1;
              for(i=len;i>(len-length);i--)
                  {
                          buff[i]='\0';
                  }
              if(count==0){
              printf("%s\n",buff);count++;}

              printf("%s\t",d->d_name);

              if(d->d_type==DT_DIR)
              {printf("(1");}
             else
             {printf("(0");}

         printf("%o/%s)\n",(fileInfo.st_mode & (S_IRWXU | S_IRWXG | S_IRWXO)), permissions(fileInfo.st_mode) );

     }
     if(strcmp(d->d_name, ".") && strcmp(d->d_name, "..") &&  S_ISDIR(fileInfo.st_mode))
              {
                  search(query, lowerFile);
              }
 }

}
