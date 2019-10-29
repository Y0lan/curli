#include "include/main.h"
int * getLongestLineAndNumberLines()
{
    FILE * file = fopen(CONFIGURATION_FILE,"r");
    int c;
    int nbChar = 0;
    int nbLine = 1;
    int longestLine = 0;
    int currentLine = 0;
    while((c = getc(file)) != EOF) {
        if(c == '\n') {
            if(currentLine > longestLine) longestLine = currentLine;
            currentLine = 0;
            nbLine++;
        }
        nbChar++;
        currentLine++;
    }
    int * result = malloc(sizeof(int) * 2);
    result[0] = longestLine;
    result[1] = nbLine;
    fclose(file);
    return result;
}
char ** confToStr(FILE * file)
{
    int * lines = getLongestLineAndNumberLines(); /* lines[0] longest line : lines[1] number of lines */
    char ** strOfConf = malloc(sizeof(char **) * lines[1]);
    int longestLine = lines[0], nbLines = lines[1];
    if(strOfConf == NULL) return (char **) EXIT_FAILURE;
    int i = 0;
    for(; i<nbLines ; i++) {
        strOfConf[i] = calloc(longestLine,sizeof(char) * longestLine);
        if(strOfConf[i] == NULL) return (char **) EXIT_FAILURE;
    }

    char * l = malloc(longestLine);
    fgets(l,longestLine,file);
    strcpy(strOfConf[0],l);
    strcat(*strOfConf,"\0");
    for( i = 1; i < nbLines; i++) {
        fgets(l,longestLine,file);
        strcat(strOfConf[i], l);
        strcat(strOfConf[i], "\0");
    }
    return strOfConf;
}

char * removeComment(char * line)
{
    if(line == NULL) return NULL; /* fils de pute */
    if(strlen(line) == 0) return NULL; /* there is no line */
    char * lineCorrected = calloc(strlen(line), sizeof(char) * strlen(line));
    u_long i = 0;
    for( ; i < strlen(line); i++) {
        if(line[i] == '#') return lineCorrected;
        else lineCorrected[i] = line[i];
    }
    return lineCorrected;
}

void removeAllComments(char ** str)
{
    int i = 0, j = 0;
    int * lines = getLongestLineAndNumberLines();
    char ** strWithoutComments = calloc(lines[1],sizeof(char **) * lines[1]);
    int nbLines = lines[1];
    for( ;  i < nbLines; i++) {
        strWithoutComments[j] = calloc(lines[0], sizeof(char) * lines[0]);
        if(removeComment(str[i]) != NULL) strcpy(strWithoutComments[j++],removeComment(str[i]));
    }
}

int countNbTask(char ** conf)
{
    int * lines = getLongestLineAndNumberLines();
    int nbLines = lines[1];
    int i = 0, counter = 0;
    for( ; i < nbLines; i++ ) {
        if(strcmp(conf[i], "=") > 0) {
            counter++;
        }
    }
    return counter;
}

void freeStrConf(char ** str)
{
    int * lines = getLongestLineAndNumberLines();
    int nbLines = lines[1];
    int i = 0;
    for (; i < nbLines; i++ ) free(str[i]);
    free(str);
}