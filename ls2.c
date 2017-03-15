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
#include <math.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/types.h>


#define row 100
#define col 100

int cmp(char **a, char **b);
void printSpaces(char* str,int maxstrlen);
struct winsize *get_screen_dimensions();
int longest_word(char **array, int arrlen);
void setup_2d_array(int **arr, int numrows, int numcols);


int cmp (char **a, char **b){
return strcmp(* a,*b);
}

int printInfo(DIR *d, int dHiddens,int order,int rorder)
{
    int count;
    int i=0,j=0,k;
    unsigned char **p=NULL;
    int isize=0;
    char **dirArray= (char**)malloc(sizeof(char*)*512);
    int dirArraylen=0;
    int index1;
    int row2,col2;	
    p=malloc(row * sizeof (unsigned char *));

    if(d==NULL){ printf("Could not read directory!\n"); return; }
    struct dirent *direct;

    while((direct = readdir(d))!=NULL)
    {
        if(direct<0)
	{ printf("Cant open folder"); return;}
        if(direct->d_name[0]!='.'||dHiddens)
	{
		if(order==0 && rorder==0)
		{
			//printf("%s",direct->d_name);
		}
		dirArray[dirArraylen]=direct->d_name;
		dirArraylen++;
       		p[i]= malloc (col * sizeof (unsigned char));
		strcpy(p[i],direct->d_name);
        	i++;
  	}
    }

	int stringLen=sizeof(dirArray)/sizeof(char*);
	int longestWordLen= longest_word(dirArray,dirArraylen); //function call to find longest word	

	
    	struct winsize *winset = get_screen_dimensions();
    	unsigned short scrnwdth = winset->ws_col;
   

    	int numcols = floor(((double)scrnwdth / (longestWordLen + 1)));
    	int numrows = ceil(((double)dirArraylen / numcols));
	   
	int **print_dirs;
	
    	print_dirs = (int **)malloc(numrows * sizeof(*print_dirs));
    	for (index1 = 0; index1 < numrows; index1++)
        	print_dirs[index1] = (int *)malloc(numcols * sizeof(*print_dirs[index1]));

   	 setup_2d_array(print_dirs, numrows, numcols);
	 
    	for (row2 = 0; row2 < numrows; row2++)
    	{
        	for (col2 = 0; col2 < numcols; col2++)
        	{

            		if (print_dirs[row2][col2] > (dirArraylen - 1))
                		continue;
            		else
            		{
                		printSpaces(dirArray[print_dirs[row2][col2]], longestWordLen);
                		printf("%s", dirArray[print_dirs[row2][col2]]);
            		}
        	}

    	}
	printf("\n");
	free(p);
	free(dirArray);
	free(print_dirs);
	free(winset);
}

void setup_2d_array(int **arr, int numrows, int numcols)
{
    /* When looping, this variable represents each index of dirArray */
    int dirIndex = 0;
	int row1,col1;
    /* Loop through each row/col in the matrix, and add the indices */
    for (col1 = 0; col1 < numcols; col1++)
    {
        for (row1 = 0; row1 < numrows; row1++)
        {
            arr[row1][col1] = dirIndex;
            dirIndex++;
        }
    }
}
	
void printSpaces(char* str, int maxstrlen)
{
	size_t currstrlen= strlen(str);
	int numspaces=maxstrlen - currstrlen;
	int i=0;
	for(;i<=numspaces;i++)
	{
		strcat(str," ");
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

struct winsize *get_screen_dimensions()
{
    struct winsize *wbuf = (struct winsize *)malloc(sizeof(struct winsize));
    ioctl(0, TIOCGWINSZ, wbuf);
    return wbuf;
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
