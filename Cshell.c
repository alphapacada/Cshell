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
#include <sys/stat.h>
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
char* directory();
void splitTokens(char string[], char* array[], int* numOfTokens, char delim[]);
int makeDirectory(char* path);
int changeDirectory(char* path);
int deleteFile(char* path);



const char *wrongSyntax = "\nThe syntax of the command is incorrect.";
const char *wrongDate = "\nThe system cannot accept the date entered.";
const char *missingFile = "\nThe system cannot find the file specified.";

char buff[FILENAME_MAX];
int main() {

    bool run = true;

    while( run ) {
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

    char *token;
    int i  = 0;
    token = strtok(string, delim);

    while(token!= NULL) {
        array[i] = token;
        token = strtok( NULL, delim);
        i++;
    }

    *numOfTokens = i;
}

char* directory () {

  getCurrDir(buff, FILENAME_MAX );
  printf("%s>", buff);
  return buff;

  }
char* getDirectory() {
    getCurrDir(buff, FILENAME_MAX );
    return buff;

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

long GetAvailableSpace(const char* path)
{
    /*
  struct statvfs stat;

  if (statvfs(path, &stat) != 0) {
    // error happens, just quits here
    return -1;
  }

  // the available size is f_bsize * f_bavail
  return stat.f_bsize * stat.f_bavail;
  */
  return 1;
}
int concatStr(char* dest, char* append) {

   for(;*dest!='\0';dest++){
   }
   while((*dest++ = *append++)!='\0'){
   }
   append='\0';
   return 0;
}

int removeDirectory(char *path) {
    rmdir(path);
}
int deleteFile(char* path) {
    char* dir = getDirectory();
    char allowDelete = 'Y';
   // char* pathToDel = strstr(dir, path) != NULL ? path : concatStr(dir,path);
    if(checkPathType(path) == 1 ) {
        printf("%s\\*, Are you sure (Y/N)?", directory());
        scanf("%c", &allowDelete);
        if(allowDelete == 'Y') {
            printf("%s", path);
                removeDirectory(path);
        }

    } else {
         if(remove(path) == 0)
		  printf("File %s  deleted.\n", path);
		else
		  fprintf(stderr, "Error deleting the file %s.\n", path);
    }



    return 0;
}
//returns 1 if it is a path to a folder
//returns 0 if it is a path to a file
int checkPathType(char* path) {
    struct stat s;
    if( stat(path,&s) == 0 )
    {
        if( s.st_mode & S_IFDIR )
        {
            //it's a directory
            return 1;

        }
        else if( s.st_mode & S_IFREG )
        {
            //it's a file
            return 0;
        }
        else
        {
            return -1;
        }
    }
    else
    {
        //error
        return -1;
    }
}
int dir (char* path) {
    char *starting_dir = getcwd(NULL,0);

    if(path != NULL){
        chdir(path);
    }

    DIR *dir;
    struct dirent *ent;
    char *current_dir = getcwd(NULL,0);
    struct stat st;
    int size;
    int file_count = 0;
    int dir_count = 0;
    struct tm *time_;
    char buf[100];


    printf("Volume in drive C is Acer.\nVolume Serial Number is E2B3-F876 \n\n  Directory of %s\n\n", current_dir);

    if ((dir = opendir (current_dir)) != NULL) {
      /* print all the files and directories within directory */
        while ((ent = readdir(dir)) != NULL) {
            stat(ent->d_name, &st);
            time_= localtime(&(st.st_mtime));
            strftime(buf, sizeof(buf), "%m/%d/%Y  %I:%M %p", time_);

            printf(buf);

            struct stat s;

            if(stat(ent->d_name,&s) == 0){
                if(s.st_mode & S_IFDIR){ //If path entry is a directory
                    dir_count++;
                    printf ("   <DIR>\t%.0d\t%s\n", st.st_size, ent->d_name);
                }else if( s.st_mode & S_IFREG ){ //If path entry is a regular file
                    file_count++;
                    printf ("        \t%d\t%s\n", st.st_size , ent->d_name);
                }else{
                    printf("Type not dir nor regular file.");
                }
            }else{
                printf("Error: INVALID TYPE");
            }

            size = st.st_size + size;
        }

        printf("\t    %d File(s) \t\t%d bytes \n", file_count, size);
        printf("\t    %d Dir(s) \t\t%d bytes \n", dir_count, GetAvailableSpace(path));
        closedir (dir);

    }

    chdir(starting_dir);
}

int typeFile(char *filepath) {
    FILE *fptr;
    char c;

    // Open file
    fptr = fopen(filepath, "r");
    if (fptr == NULL)
    {
        printf("%s", missingFile);
        exit(0);
    }

    // Read contents from file
    c = fgetc(fptr);
    while (c != EOF)
    {
        printf ("%c", c);
        c = fgetc(fptr);
    }

    fclose(fptr);
    return 0;
}
int renameFile(char** filenames) {
    int ret = 1;

   // printf("%s",filenames[1]);
   // printf("%s",filenames[2]);
   if((sizeof(filenames) - 1) % 2 == 0) {
     return 0;
   }

   int start = 1;
   int i = 0 ;
   for(i = 1; i < sizeof(filenames); i+=2) {
        //printf("%d", i);
      ret = rename(filenames[i], filenames[i+1]);
      if(ret != 0 ) {
        printf("The system cannot find the file specified.\n");
      }
   }


   if(ret == 0) {
      printf("File renamed successfully");
   } else {
      printf("Error: unable to rename the file");
   }

}
int copyFile(char** token) {
    char *starting_dir = getcwd(NULL,0);

    char *dirc, *basec, *bname, *dname;
    char *path = token[2];

    dirc = strdup(path);
    basec = strdup(path);
    dname = dirname(dirc);
    bname = basename(basec);


    char *dirc2, *basec2, *bname2, *dname2;
    char *path2 = token[1];

    dirc2 = strdup(path2);
    basec2 = strdup(path2);
    dname2 = dirname(dirc2);
    bname2 = basename(basec2);

                if(token[1] == NULL || token[2] == NULL) {
        printf("Too few arguments\n");
      } else {
        char ch;
        FILE *source, *target;
        chdir(dname2);
        source = fopen(bname2, "r");
        if(source == NULL) {
          printf("Source file cannot be found.\n");
        } else {
          if(strcmp(token[1], token[2]) == 0) {
            printf("Source file must not be same with target file.\n");
          }
           else {
                chdir(dname);
            target = fopen(bname, "w");
            ch = fgetc(source);
            while (ch != EOF) {
                fputc(ch, target);
                ch = fgetc(source);
            }
            fclose(target);
          }
           printf("Successful Copy!\n\n");
          fclose(source);
          chdir(starting_dir);
        }
      }
}
int count(char** array) {
    int numberofelements = 0;
    int i;
   // printf("%d ", sizeof(array));
    for(i=0; i < sizeof(array); i++) {

   if(array[i] != NULL)    // If pointer is NULL then increase the elements
      ++numberofelements;
    }
   // printf("%d", numberofelements);
    return numberofelements;
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
        if(strcmp (array[0], "dir") == 0) {
            dir(array[1]);
        }
        if(strcmp (array[0], "exit") == 0) {
            return false;
        }
        if(strcmp (array[0], "del") == 0) {
            deleteFile(array[1]);
        }
        if(strcmp (array[0], "rename") == 0) {

        }
        if(strcmp (array[0], "type") == 0) {
            typeFile(array[1]);
        }
        if(strcmp (array[0], "rmdir") == 0) {
            removeDirectory(array[1]);
        }
         if(strcmp (array[0], "cd..") == 0) {
            changeDirectory("..");
        }
        if(strcmp (array[0], "cd") == 0) {
            int n = count(array);
            if( n == 1) {
                printf("%s\n\n", getDirectory());
            } else {
                chdir(array[1]);
            }

        }
        if(strcmp (array[0], "cd/") == 0 || strcmp (array[0], "cd\\") == 0 ) {
            changeDirectory("/");
        }

        if(strcmp (array[0], "rename") == 0) {
            renameFile(array);
        }

        if(strcmp (array[0], "copy") == 0) {
            copyFile(array);
        }


    }
    free(str);
    char ch;
    //while ((ch=getchar()) != EOF && ch != '\n');
    return true;
}

