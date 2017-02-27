#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <getopt.h>

  int main(int argc, char * argv[]) {
    int y = 0;
    int x = 0;
    int c = 0;
    int currentFileHndl = -1;
    char buffer[1024];
    int delim = -1; // for e
    int lineNumbers = -1; // for n
    int lineNumbersb = -1; // for  b
    int trim = -1; // for s
    int lineCount = 1;
    int lc = 1;

    while ((c = getopt(argc, argv, "bens")) != -1) {
      switch (c) {
      case 'b':
        lineNumbersb = 1;
        break;
      case 'e':
        delim = 1;
        break;
      case 'n':
        lineNumbers = 1;
        break;
      case 's':
        trim = 1;
        break;
      default:
        exit(EXIT_FAILURE);
      }
    }

    if (lineNumbers > 0) {
      printf("1");
    } // if the n is as command

    for (x = 1; x < argc; x++) // open files for reading
    {
      if (argv[x][0] == '-') {
        continue;
      } // skip flags
      currentFileHndl = open(argv[x], O_RDONLY);
      if (currentFileHndl < 0) {
        printf("Unable to open %s\n!", argv[x]);
        continue;
      }
      char currentLine[2048];
      while (read(currentFileHndl, & buffer, sizeof buffer) > 0) {
        int len = 0;
        int pl = -1;
        int printLine = 1;
        int printLineb = 1;
        int charLineCount = 0;
        int count = 0;
        for (len = 0; len < strlen(buffer); len++) {
          currentLine[charLineCount] = buffer[len];
          currentLine[charLineCount + 1] = 0; // build line string,
          //dont forget null terminate
          charLineCount++; //next char index

          if (buffer[len] == '\n') {
            lineCount++;
            lc++;
            charLineCount = 0;
            count = 0;
          } // new line encounter
          if (currentLine[0] == '\n' || currentLine[0] == '\r') {
            lc--;
          }

          if (buffer[len] != '\n' && lineNumbersb > 0) {
            int k = 0;
            pl = -1;
            for (k = 0; k < strlen(currentLine) - 1; k++) {
              if (currentLine[k] != 32 && strlen(currentLine) > 1) //32 space ascii
              {
                pl++;
              }
            }
            if (count == 0 && pl>-1) {
              printf("%d", lc);
              count++;
            }
          }

          if (buffer[len] == '\n') {
            if (trim > 0) // if argument is s
            {
              int x = 0;
              printLine = -1;
              for (x = 0; x < strlen(currentLine) - 1; x++) {
                if (currentLine[x] != 32 && strlen(currentLine) > 1) //32 space ascii
                {
                  printLine = 1;
                }
              }
            }

            if (printLine < 0) {

              lineCount--;
            }

            int z;
            // if -e is argument
            for (z = 0; z < strlen(currentLine); z++) {
              if (printLine > 0)
                printf((delim > 0 && currentLine[z] == '\n' ? "$%c" : "%c"), currentLine[z]);
            }

          }

          // if n is argument
          if (lineNumbers > 0 && buffer[len] == '\n' && printLine > 0) {
            printf("%d", lineCount);
          }

        }
        printLine = -1;

      }
    }
  }
