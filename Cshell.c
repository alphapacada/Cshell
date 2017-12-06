#include <stdio.h>
#include <stdbool.h>
#include <dirent.h>
#include <direct.h>
#include<conio.h>
#include<dir.h>
#include <string.h>

#define getCurrDir _getcwd

bool getCommand();
void splitTokens(char string[], char* array[], int* numOfTokens);

char buff[FILENAME_MAX];
const char *wrongSyntax = "/nThe syntax of the command is incorrect.";

int main() {

    bool run = true;
    directory();
    getCommand();

    return 0;
}
void splitTokens(char* string, char* array[], int* numOfTokens) {
    char *token;
    const char delim[2] = " ";
    int i  = 0;
    token = strtok(string, delim);

    while(token!= NULL) {
        array[i] = token;
        token = strtok( NULL, delim);
        i++;

    }
    /*for(i = 0 ; i < sizeof(array); i++) {
        printf("%s\n", array[i]);
    }*/
    *numOfTokens = i;
}

int directory () {

  getCurrDir( buff, FILENAME_MAX );
  printf("%s>\n", buff);
  return 1;
  }
bool getCommand(){

    int MAX_SIZE;
    char str[MAX_SIZE];

    fgets(str,MAX_SIZE, stdin);
    printf("this is the string %s", str2);

    char *array[MAX_SIZE] = {NULL};
    int numOfTokens = 0;
    splitTokens(str, array, &numOfTokens);

    int i = 0;
    for( i = 0; i < numOfTokens; i++ ) {
        printf( "array[%d] = %s\n", i, array[i] );
    }

    return false;
}
