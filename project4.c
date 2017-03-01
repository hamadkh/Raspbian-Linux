#include <stdio.h>
#include <dirent.h>
#include <string.h>

int printInfo(DIR *d, int dHiddens)
{
    if(d==NULL){ printf("Could not read directory!\n"); return; }
    struct dirent *direct;
    //dir = opendir(argv[x]);
    while((direct = readdir(d))!=NULL)
    {
        if(direct<0){ printf("Cant open folder"); return; }
        if(direct->d_name[0]!='.'||dHiddens){ printf("%s\n",direct->d_name); }
    }
}

int main(int argc, char** argv)
{
    DIR *dir;
    int a = 0;
    int realArgCount = argc;
    int displayHiddens = 0;
    for(a=0;a<argc;a++)
    {
        if(strcmp(argv[a], "-a")==0) { realArgCount--; displayHiddens = 1; }
    }
    if(realArgCount>=2){
        int x = 0;
        for(x=1;x<argc;x++)
        {
            if(argv[x][0]=='-') continue;
            dir = opendir(argv[x]);
            printInfo(dir, displayHiddens);
            closedir(dir);
        }
    }else{ dir = opendir("."); printInfo(dir, displayHiddens); closedir(dir); }
    return 0;
}
