// Hamad Khawaja
// myls
// -a
// -r
// -s
// CS355


#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <getopt.h>
#include <stdlib.h>

int cmp (char **a, char * *b){
return strcmp(* a,*b);
}

int printInfo(DIR *d, int dHiddens,int order,int rorder)
{
    int count;
    int i=0,j=0,k;
    char temp[50];
    unsigned char **p=NULL;
    p=malloc(row * sizeof (unsigned char *));

    if(d==NULL){ printf("Could not read directory!\n"); return; }
    struct dirent *direct;

    while((direct = readdir(d))!=NULL)
    {
        if(direct<0)
	{
	 printf("Cant open folder"); return;
	    }
        if(direct->d_name[0]!='.'||dHiddens)
	{
	if(order==0 && rorder==0){
	printf("%s\n",direct->d_name);}
       	p[i]= malloc (col * sizeof (unsigned char));
	strcpy(p[i],direct->d_name);
        i++;
  	 }
    }

	if(order==1){
	printf("LEXICOGRAPHICAL ORDER ! \n");

	qsort(p,i,sizeof (char*) ,(int (*)(const void *, const void *)) cmp);

	for(j=0;j<i;j++)
	{printf("%s\n",p[j]);}
	}

	if(rorder==1){
	printf("REVERSE LEXICOGRAPHICAL ORDER !\n ");
        if(order !=1)
	{qsort(p,i,sizeof (char*) ,(int (*)(const void *, const void *)) cmp);}

	for(k=i-1;k>=0;k--)
	{printf("%s\n",p[k]);}
	}
	free(p);
}


int main(int argc, char* argv[])
{
    DIR *dir;
    int a = 0;
    int argCount = argc;
    int displayHiddens = 0;
    int rorder = 0;
    int order = 0;
 
    while((a = getopt(argc, argv, "ars")) != -1) {
	switch(a) {
	case 'a':
	displayHiddens=1;
	break;
	case 'r':
	rorder=1;
	break;
	case 's':
	order=1;
	break;
	default:
	exit(EXIT_FAILURE);
	}
     }

	//if check current file directory
	int k;
	for(k=0;k<argc;k++)
	{
		if((strcmp(argv[k],"-ars")==0)|| (strcmp(argv[k],"-a")==0)|| (strcmp(argv[k],"-r")==0) || (strcmp(argv[k],"-s")==0)|| strcmp(argv[k],"-ar")==0)
		{
		    argCount--;
			}
	}

	if(argCount >=2)
	{
	int x;

	for(x=1;x<argc;x++)
	{
		if(argv[x][0]=='-') continue;
		dir=opendir(argv[x]);
		printInfo(dir, displayHiddens,order,rorder);
		closedir(dir);
		}
	}
	else
	{
	dir= opendir(".");
	printInfo(dir, displayHiddens,order,rorder);
	closedir(dir);
	}

    return 0;
}
