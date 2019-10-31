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
void checkKeyAction(char * line, int n)
{
    if(*line != '{' && *line != '+') {
        fprintf(stderr,"\nERROR : %c NOT EXPECTED at 1:%d", *line, n);
    }
}
void checkKeyTask(char * line, int n)
{

}
void checkFileForSyntaxError(FILE * config)
{
    char line[300];
    char firstChar[5] = "=({+";
    int countLine = 1;
    int inTask = 0;
    int inAction = 0;
    while(fgets(line, 300, config)) {
        line[(strchr(line,'\n') - line) + 1] = '\0';
        removeComment(line);
        if(!strchr(firstChar, line[0]) && line[0] != '\n') {
            fprintf(stderr,"\n%c syntax error at %d:1",*line,countLine);
            return;
        }
        if(strlen(line) == 3 && line[0] == '=' && line[1] == '=') {
            inAction = 0;
            inTask = 1;
            continue;
        }
        if(strlen(line) == 2 && line[0] == '=') {
            inTask = 0;
            inAction = 1;
            continue;
        }
        if(inTask) checkKeyTask(line, countLine);
        if(inAction) checkKeyAction(line, countLine);
        countLine = countLine + 1;
    }
}

void readConfigurationFile(FILE * config)
{
    char line[300];
    while(fgets(line,300,config)) {
        removeComment(line);


        //printf("%s", line);
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