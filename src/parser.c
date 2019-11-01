#include "include/main.h"
int * getLongestLineAndNumberLines()
{
    char * configFilePath = malloc(sizeof(char) * 180);
    getConfigFilePath(configFilePath);
    FILE * file = fopen(configFilePath,"r");
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
    free(configFilePath);
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
/*
char * removeComment(char * line)
{
    if(line == NULL) return NULL;
    if(strlen(line) == 0) return NULL;
    char * lineCorrected = calloc(strlen(line), sizeof(char) * strlen(line));
    u_long i = 0;
    for( ; i < strlen(line); i++) {
        if(line[i] == '#') return lineCorrected;
        else lineCorrected[i] = line[i];
    }
    return lineCorrected;
}
*/
/*
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
*/
int countNbTask(char ** conf)
{
    int * lines = getLongestLineAndNumberLines();
    int nbLines = lines[1];
    int i = 0, counter = 0;
    for( ; i < nbLines; i++ ) {
        if(strncmp(conf[i], "==", 2) == 0 && strlen(conf[i]) == 3) { /* si il y'a == dedans et que le string est "=\n" */
            counter++;
        }
    }
    return counter;
}
int countNbAction(char ** conf)
{
    int * lines = getLongestLineAndNumberLines();
    int nbLines = lines[1];
    int i = 0, counter = 0;
    for ( ; i < nbLines; i++) {
        if(strncmp(conf[i], "=", 1) == 0 && strlen(conf[i]) == 2) {
            counter++;
        }
    }
    return counter;
}
void removeComment(char * line)
{
    char * commentPos;
    commentPos = strchr(line,'#');
    int endOfLineComment = 0;
    if(commentPos) {
        long position =  commentPos - line;
        if(position > 0) endOfLineComment = 1;
        memcpy(line,line, position);
        if(endOfLineComment) line[position++] = '\n';
        line[position] = '\0';
    }
}
void checkKeyAction(char * line, int actionN, int lineN, int new)
{
    if(*line == '=' || *line == ' ' || *line == '\n') return;
    int len = strlen(line), i = 0;
    char c = NULL;
    int main = 0, option = 0;
    printf("\nACTION %d: \n%s", actionN, line);
    for ( ; i < len ; i++ ) {

    }
}
void checkKeyTask(char * line, int actionN, int lineN, int new)
{
    if(*line == '\n') return;
    int len = strlen(line), i = 0;
    printf("\nTASK %d: \n%s",actionN, line);
}
void checkMode(char * line, int * inAction, int * inTask, int * nbActions, int * nbTasks, int * next, int * new)
{
    if(line[0] == '=' && line[1] == '=') {
        *inAction = 0;
        *inTask = 1;
        *nbTasks = *nbTasks + 1;
        *next = 1;
        *new = 1;
    }
    if(line[0] == '=' && line[1] != '=') {
        *inTask = 0;
        *inAction = 1;
        *nbActions = *nbActions + 1;
        *next = 1;
        *new = 1;
    }
}
void checkFileForSyntaxError(FILE * config, task * tasks, action * actions)
{
    char line[300];
    char firstChar[5] = "=({+";
    int countLine = 1;
    int inTask = 0, nbTasks = 0;
    int inAction = 0, nbActions = 0;
    while(fgets(line, 300, config)) {
        line[(strchr(line,'\n') - line)] = '\0';
        removeComment(line); /* work correctly */
        if(!strchr(firstChar, line[0])) {
            fprintf(stderr,"\n%c syntax error at %d:1",*line,countLine);
            return;
        }
        //printf("\n-----\n\n%d : strlen : %d 1: %c 2: %c str: %s \n ------", countLine,(int) strlen(line), line[0], line[1], line);

        int next = 0, new = 1; /* new est là pour savoir quand on passe sur une nouvelle action */
        checkMode(line, &inAction, &inTask, &nbActions, &nbTasks, &next, &new);

        if(inTask) checkKeyTask(line, nbTasks, countLine, new);
        if(inAction) checkKeyAction(line, nbActions, countLine, new);
        countLine = countLine + 1;
    }
}



void freeStrConf(char ** str)
{
    int * lines = getLongestLineAndNumberLines();
    int nbLines = lines[1];
    int i = 0;
    for (; i < nbLines; i++ ) free(str[i]);
    free(str);
}