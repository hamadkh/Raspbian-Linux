// Hamad Khawaja
// ls2
// -a
// -r
// -s
// CS355


#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <getopt.h>
#include <stdlib.h>
#include <sys/ioctl.h>

#define row 100
#define col 100

int cmp(char **a, char **b);
int cmpr(char **a, char **b);
void printSpaces(char* str,int maxstrlen);
int longest_word(char **array, int arrlen);


int cmp (char **a, char **b){
return strcmp(* a,*b);
}

int cmpr (char **a, char **b){
return strcmp(* b,*a);
}

int printInfo(DIR *d, int dHiddens,int order,int rorder)
{
    struct dirent *direct;
    int columnsWin=0;
    int i=0,j=0;
    int idir=0;
    char **dirArray= (char**)malloc(sizeof(char*));
    int dirArraylen=0;
    struct winsize wbuf;


    if(d==NULL){ printf("Could not read directory!\n"); return; }
  
    while((direct = readdir(d))!=NULL)
    {
        if(direct<0)
	{ printf("Cant open folder"); return;}
        if(direct->d_name[0]!='.'||dHiddens)
	{
		dirArray[dirArraylen]=direct->d_name;
		dirArraylen++;
        	idir++;
  	}
    }
	if(order==1){
	qsort(dirArray,idir,sizeof (char*) ,(int (*)(const void *, const void *)) cmp);
	}
	if(rorder==1){
	qsort(dirArray,idir,sizeof (char*) ,(int (*)(const void *, const void *)) cmpr);
	}
	
	
	int longestWordLen= longest_word(dirArray,dirArraylen); //function call to find longest word	
	if( ioctl(0, TIOCGWINSZ, &wbuf) != -1 )
	columnsWin = wbuf.ws_col;
	
	int numCols = (int) (columnsWin/ (longestWordLen + 4));
	int numRows = (int) (idir/ numCols);
		if( (idir % numCols) != 0 ) 
		{numRows++;}

	for(; i < numRows; i++)
		{
			for(j = i; j < idir; j += numRows)
			{
				printf("%s  ", dirArray[j]);
				printSpaces(dirArray[j],longestWordLen);
					
			}
			printf("\n");
		}
	

}
	
void printSpaces(char* str, int maxstrlen)
{
	size_t currstrlen= strlen(str);
	int numspaces=maxstrlen - currstrlen;
	int i=0;
	for(;i<=numspaces;i++)
	{
		printf(" ");
	}
}

// Calculates the longest file name in the directory

int longest_word(char** arr, int arrlen)
{
	size_t longestlen=0;
	int index=0;
	for(;index<arrlen;index++)
	{
		size_t currstrlen= strlen(arr[index]);
		if(currstrlen > longestlen)
		longestlen=currstrlen;
	}
	//printf("*%d*",longestlen);
	return longestlen;
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
		if((strcmp(argv[k],"-as")==0)|| (strcmp(argv[k],"-a")==0)|| (strcmp(argv[k],"-r")==0) || (strcmp(argv[k],"-s")==0)|| strcmp(argv[k],"-ar")==0)
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
