#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <math.h> // compile with -lm

#define MAXFILES 255
char *printable[MAXFILES];
int maxNameLength = 0;

int parseInfo(DIR *d) // returns size of array after filling it
{
    if(d==NULL){ printf("Could not read directory!\n"); return; }
    struct dirent *direct;
    int x = 0;
    while((direct = readdir(d))!=NULL)
    {
        maxNameLength = (strlen(direct->d_name)>maxNameLength ? strlen(direct->d_name) : maxNameLength);
        printable[x] = direct->d_name;
        x += (printable[x][0]=='.' ? 0 : 1);
    } x -= (printable[x][0]=='.' ? 1 : 0);
    return x;
}

int compare(const void *a, const void *b)
{
    return strcmp(*(char**)a,*(char**) b);
}

int main(int argc, char** argv)
{
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    int columns = w.ws_col;
    int maxFileName = 0;
    DIR *dir;
    dir = opendir(".");
    int visibleFileCount = parseInfo(dir);
    int rowLength = (columns > 10 ? ceil(columns / maxNameLength) : 1);
    int rows = ceil(visibleFileCount/rowLength); // compile with -lm
    int c = 0;
    qsort(printable, visibleFileCount+1,  sizeof (char*), compare);
    if(rowLength>=visibleFileCount+2*visibleFileCount||rows<=1){
        for(c=0; c<=visibleFileCount; c++)
        {
            printf("%s  ", printable[c]);
        }
    }else{
        int printed = 0; int p = 0;
        int line = 0;
        int current = 0;
        if((rowLength+1)*rows<visibleFileCount+1){ printed=((visibleFileCount+1)%((rowLength+1)*rows)); }
        for(line = 0; line<rows; line++)
        {
            int c = 0;
            printf("%s\t", printable[line]);
            for(current=line+rows; c<rowLength; current+=rows){
                if(current<=visibleFileCount+1 && strcmp(printable[current],"..")!=0) printf("%s  ", printable[current]);
                if(current>visibleFileCount) { current = current%visibleFileCount; } c++;
                if(c==rowLength&&printed>=1){ printf(printable[current+rows]); printed--; p++; }
                if(current==visibleFileCount-(rows-1)){ break; }
            }
            printf("\n");
        }
        //printf("vfc %d, rl %d, rs %d, prnt %d", visibleFileCount, rowLength, rows, printed);
    }
    closedir(dir);
    return 0;
}
