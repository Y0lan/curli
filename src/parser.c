#include "include/main.h"
#include "include/parser.h"
typedef struct action {
    char * name;
    char * url;
    unsigned int max_depth;
    unsigned short versioning;
    char ** type;
} action;

typedef struct task {
    action * actions;
    unsigned long long * second; /* Let's say that we will count the time before each action in second */
    /* second[0] -> timer for actions[0], second[1] (> timer for actions[1], etc... */
} task;

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
char ** confToStr()
{
    int * lines = getLongestLineAndNumberLines(); /* lines[0] longest line : lines[1] number of lines */
    char ** strOfConf = malloc(sizeof(char **) * lines[1]);
    if(strOfConf == NULL) return (char **) EXIT_FAILURE;
    int i = 0;
    for(; i<lines[1] ; i++) {
        strOfConf[i] = malloc(sizeof(char) * lines[0]);
        if(strOfConf[i] == NULL) return (char **) EXIT_FAILURE;
    }

    return strOfConf;
}


void freeStrConf(char ** str)
{
    int * lines = getLongestLineAndNumberLines();
    int nbLines = lines[1];
    int i = 0;
    for (; i < nbLines; i++ ) free(str[i]);
    free(str);
}