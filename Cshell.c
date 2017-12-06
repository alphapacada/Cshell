#include <stdio.h>
#include <stdbool.h>
#include <dirent.h>
#include <direct.h>
#include <conio.h>
#include <dir.h>
#include <string.h>
#include <windows.h>
#include <time.h>
#include <dos.h>
#define getCurrDir _getcwd
#define WIN32_LEAN_AND_MEAN
#include <stdint.h> // portable: uint64_t   MSVC: __int64
/*
#ifdef _LIBC

extern const struct __locale_data _nl_C_LC_TIME attribute_hidden;
# define ab_weekday_name \
  (&_nl_C_LC_TIME.values[_NL_ITEM_INDEX (ABDAY_1)].string)
#else
*/
static char* const ab_weekday_name[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};


bool getCommand();
void splitTokens(char string[], char* array[], int* numOfTokens, char delim[]);
int makeDirectory(char* path);
int changeDirectory(char* path);



const char *wrongSyntax = "/nThe syntax of the command is incorrect.";
const char *wrongDate = "/nThe system cannot accept the date entered.";

char buff[FILENAME_MAX];
int main() {

    bool run = true;

    while( run ) {
        printf("loop");
        directory();
        getCommand();
    }

    return 0;
}
typedef struct timevalue {
    long tv_sec;
    long tv_msec;
} timevalue;

int gettimeofday(struct timevalue * tp, struct timezone * tzp)
{
    // Note: some broken versions only have 8 trailing zero's, the correct epoch has 9 trailing zero's
    // This magic number is the number of 100 nanosecond intervals since January 1, 1601 (UTC)
    // until 00:00:00 January 1, 1970
    static const uint64_t EPOCH = ((uint64_t) 116444736000000000ULL);

    SYSTEMTIME  system_time;
    FILETIME    file_time;
    uint64_t    time;

    GetSystemTime( &system_time );
    SystemTimeToFileTime( &system_time, &file_time );
    time =  ((uint64_t)file_time.dwLowDateTime )      ;
    time += ((uint64_t)file_time.dwHighDateTime) << 32;

    tp->tv_sec  = (long) ((time - EPOCH) / 10000000L);
    tp->tv_msec = (long) (system_time.wMilliseconds * 10);
    return 0;
}
void splitTokens(char* string, char* array[], int* numOfTokens, char delim[]) {
printf("SP");
    char *token;
    int i  = 0;
    token = strtok(string, delim);

    while(token!= NULL) {
        array[i] = token;
        token = strtok( NULL, delim);
        i++;
    }

    *numOfTokens = i;
    printf("num of tokens %d", *numOfTokens);
}

int directory () {

  getCurrDir(buff, FILENAME_MAX );
  printf("%s>\n", buff);
  return 1;

  }

int makeDirectory(char* path) {

    int n = 1;
    n = mkdir(path);
    if( n != 0 ) {
        printf("The system cannot find the path specified.\n");
    }
}

int changeDirectory(char* path) {

    int n = chdir(path);
    if( n == 0 ) {
    }
    else
        printf("The system cannot find the path specified.\n");
}

int date() {

time_t t = time(NULL);
struct tm tm = *localtime(&t);
//int month;
int day;
int year;
char weekday[20], month[20];
//char buffer[100];
char *dateTokens[5] = {NULL};

int numOfTokens = 0;
printf("The current date is: %s %d/%02d/%d\n", ab_weekday_name[tm.tm_wday], tm.tm_mon + 1, tm.tm_mday,   tm.tm_year + 1900, tm.tm_hour, tm.tm_min, tm.tm_sec);
printf("Enter the new date: (mm-dd-yy)");
char ch;
//while ((ch=getchar()) != EOF && ch != '\n');
//scanf("%s", buffer);
char buffer[] = "2011-02-31";
splitTokens(buffer, dateTokens, &numOfTokens, " /-");
return 0;
}

int getTime() {

    timevalue tp;
    gettimeofday(&tp, 0);
    time_t curtime = tp.tv_sec;
    struct tm tm = *localtime(&curtime);
    printf("The current time is: %02d:%02d:%02d.%2d\n", tm.tm_hour, tm.tm_min, tm.tm_sec, tp.tv_msec/100);
    printf("Enter the new time: ");
    //gets(tim);//token[0]
}

void cmd() {
      printf("Microsoft Windows [Version 10.0.14393]\n(c) 2017 Microsoft Corporation. All rights reserved.\n\n");
}

int clrscr() {
    HANDLE                     hStdOut;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD                      count;
    DWORD                      cellCount;
    COORD                      homeCoords = { 0, 0 };

    hStdOut = GetStdHandle( STD_OUTPUT_HANDLE );
    if (hStdOut == INVALID_HANDLE_VALUE) return;

    /* Get the number of cells in the current buffer */
    if (!GetConsoleScreenBufferInfo( hStdOut, &csbi )) return;
    cellCount = csbi.dwSize.X *csbi.dwSize.Y;

    /* Fill the entire buffer with spaces */
    if (!FillConsoleOutputCharacter(
    hStdOut,
    (TCHAR) ' ',
    cellCount,
    homeCoords,
    &count
    )) return;

    /* Fill the entire buffer with the current colors and attributes */
    if (!FillConsoleOutputAttribute(
    hStdOut,
    csbi.wAttributes,
    cellCount,
    homeCoords,
    &count
    )) return;

    /* Move the cursor home */
    SetConsoleCursorPosition( hStdOut, homeCoords );
    return 1;

}
bool getCommand() {
    int MAX_SIZE = 100;
    char str[MAX_SIZE];
    scanf ("%[^\n]%*c", str);
    char *array[5] = {NULL};

    int numOfTokens = 0;

    splitTokens(str, array, &numOfTokens, " ");

    int i = 0;

    if(numOfTokens > 0) {
        if(strcmp(array[0], "cmd") == 0) {  //cmd
            cmd();
        }

        if(strcmp (array[0], "mkdir") == 0) { //mkdir

            makeDirectory(array[1]);
        }

        if(strcmp (array[0], "chdir") == 0) {

            changeDirectory(array[1]);
        }

        if(strcmp (array[0], "cls") == 0) {
            clrscr();
        }

        if(strcmp (array[0], "date") == 0) {
            date();

        }
        if(strcmp (array[0], "time") == 0) {
            getTime();
        }
        if(strcmp (array[0], "exit") == 0) {
            return false;
        }

    }
    free(str);
    return true;
}

