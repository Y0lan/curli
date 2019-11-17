#include "include/main.h"
void removeComment(char * line)
{
    char * commentPos;
    commentPos = strchr(line,'#');
    if(commentPos) {
        long position =  commentPos - line;
        memcpy(line,line, position);
        /* remove space at the end of the line */
        int i = 1;
        while(line[position - i] == ' ') line[position - i++] = '\0';
        /* doesn't hurt */
        line[position] = '\0';
    }
}
struct_action * fillActionWithValue(char * key, char * value)
{
    struct_action * action = malloc(sizeof(struct_action));
    if(action == NULL) return action;
    if(strcmp(key,"max-depth") == 0) action->max_depth = isNumber(value);
    return action;
}
void timeToSeconds(char * time, char * value, int long long * seconds)
{
    if(strcmp(time,"second")   == 0) *seconds += isNumber(value);
    if(strcmp(time,"seconds")  == 0) *seconds += isNumber(value);
    if(strcmp(time,"minute")   == 0) *seconds += isNumber(value) * 60;
    if(strcmp(time,"minutes")  == 0) *seconds += isNumber(value) * 60;
    if(strcmp(time,"hour")     == 0) *seconds += (isNumber(value) * 60) * 60;
    if(strcmp(time,"hours")    == 0) *seconds += (isNumber(value) * 60) * 60;
    if(strcmp(time,"day")      == 0) *seconds += ((isNumber(value) * 60) * 60) * 24;
    if(strcmp(time,"days")     == 0) *seconds += ((isNumber(value) * 60) * 60) * 24;
    if(strcmp(time,"week")     == 0) *seconds += (((isNumber(value) * 60) * 60) * 24) * 7;
    if(strcmp(time,"weeks")    == 0) *seconds += (((isNumber(value) * 60) * 60) * 24) * 7;
    if(strcmp(time,"month")    == 0) *seconds += ((((isNumber(value) * 60) * 60) * 24) * 7 * 30);
    if(strcmp(time,"months")   == 0) *seconds += ((((isNumber(value) * 60) * 60) * 24) * 7 * 30);
}
void getKeyandKeyValue(char * key, char * value, char * line, int mode)
{
    const char delim[4] = "{->}";
    char * token = strtok(line, delim);
    while(token != NULL) {
        if(isKeyActionValid(token,mode)) {
            strcpy(key, token);
            if(strcmp(key,"max") == 0) strcat(key,"-depth");
        } else strcpy(value,token);
        token = strtok(NULL, delim);
    }
}
int countActionsInTask(char * line)
{
    int counter = 0;
    if(strtok(line, ",") != NULL) counter++;
    while(strtok(NULL,",") != NULL) counter++;
    return counter;
}
void fillStructure(char * line, int mode, int taskN,  int * nbActionsPerTasks,  int long long * seconds, struct_action * action, int nbActions)
{
    /* check if it is a valid key / value type of line */
    if(*line != '{' && *line != '(') return;
    if(*line == '{') {
        char * key = calloc(256, sizeof(char));
        char * value = calloc(256, sizeof(char));
        getKeyandKeyValue(key,value,line,mode);
        if(action) action[nbActions - 1] =  fillActionWithValue(key,value)[0];
        timeToSeconds(key, value, seconds);
    }
    if(*line == '(' && mode == TASK) /* we are on the line containing the action of the tasks */
        nbActionsPerTasks[taskN-1] += countActionsInTask(line);
}
/*
 * check is str is a number
 * return the number if it is
 * return -1 if it is not
 */
int long long isNumber(char * s)
{
    char * endptr;
    errno = 0; // reset error number
    int long long res = strtoll(s,&endptr,10);
    /* number too small or too large */
    if(errno == ERANGE)
        return -1;
    /* no character was read */
    else if(endptr == s)
        return -1;
    /*
     * if *endptr != '\0' it means it is not the end of the string
     * we did not convert the all string
    */
    else if(*endptr)
        return -1;
    return res;
}
/*
 * mode :
 * action = 1
 * task   = 2
*/
int isKeyActionValid(char * key, int mode)
{
    if (strcmp(key,"name") == 0) return 1;
    if (mode == ACTION) {
        if ((strcmp(key,"type")             == 0 )||
                (strcmp(key,"versioning")   == 0) ||
                (strcmp(key,"url")          == 0))
            return 1;
    } else if (mode == TASK) {
        if ((strcmp(key,"second")       == 0)   ||
                (strcmp(key,"seconds")  == 0)   ||
                (strcmp(key,"minute")   == 0)   ||
                (strcmp(key,"minutes")  == 0)   ||
                (strcmp(key,"hour")     == 0)   ||
                (strcmp(key,"hours")    == 0)   ||
                (strcmp(key,"day")      == 0)   ||
                (strcmp(key,"days")     == 0)   ||
                (strcmp(key,"week")     == 0)   ||
                (strcmp(key,"weeks")    == 0)   ||
                (strcmp(key,"month")    == 0)   ||
                (strcmp(key,"months")   == 0))
            return 1;
    }
    return 0;
}
int checkMode(const char * line, int * nbActions, int * nbTasks, int current)
{
    if(line[0] == '=' && line[1] == '=') {
        *nbTasks = *nbTasks + 1;
        return TASK;
    }
    if(line[0] == '=' && line[1] != '=') {
        *nbActions = *nbActions + 1;
        return ACTION;
    }
    return current;
}
int checkSyntaxErrorOnFirstCharacterOfLine(char c, char * line, int lineNumber)
{
    char firstChar[5] = "=({+"; // the allowed character at the beginning of a line in conf file
    if (!strchr(firstChar, c)) {
        fprintf(stderr, "\n'%c' ->  syntax error at %d:1\n\t%s",c,lineNumber, line);
        return 1;
    }
    return 0;
}
void removeNewLineEOL(char * line)
{
    line[(strchr(line, '\n') - line)] = '\0';
}

void readConfigurationFile(FILE * config, struct_tasks * tasks, struct_actions * actions)
{
    char * line = malloc(300); // buffer for each line read, assume the longest line is 300
    int countLine = 1; // track wich line in the config file we are on
    int nbTasks = 0, nbActions = 0; // check if we are reading tasks and count the nb of tasks
    int *nbActionsPerTasks;
    int long long seconds = 0;
    int long long *pseconds = &seconds;
    int long long *secondsPerTasks = calloc(1, sizeof(int long long));
    nbActionsPerTasks = malloc(sizeof(int));
    int mode = 0;
    while (fgets(line, 300, config)) {
        removeNewLineEOL(line);
        removeComment(line); /* work correctly */
        if(checkSyntaxErrorOnFirstCharacterOfLine(line[0], line, countLine) == -1) return;
        int currentNbTask = nbTasks;
        int currentNbAction = nbActions;
        mode = checkMode(line, &nbActions, &nbTasks, mode);
        if ( mode == TASK ) {
            fillStructure(line, mode, currentNbTask,nbActionsPerTasks, pseconds, NULL, nbActions);
        }
        if ( mode == ACTION ) {
            fillStructure(line, mode, currentNbTask,nbActionsPerTasks, pseconds,actions->action, nbActions);
        }
        if (nbTasks || currentNbTask != nbTasks) {
            secondsPerTasks = realloc(secondsPerTasks, nbTasks);
            secondsPerTasks[nbTasks - 1] += seconds;
            seconds = 0;
        }
        if(nbActions || currentNbAction != nbActions) {
            actions->action = realloc(actions->action, sizeof(struct_action *) * nbActions);
        }
        countLine = countLine + 1;
    }
    actions->numberOfActions = nbActions;
    tasks->numberOfTasks = nbTasks;
    tasks->task = malloc(sizeof(struct_task *) * nbTasks);
    for (int i = 0; i < nbTasks; i++) {
        tasks->task[i].actions = malloc(sizeof(struct_action *) * nbActionsPerTasks[i]);
        tasks->task[i].numberOfActions = nbActionsPerTasks[i];
        tasks->task[i].second = secondsPerTasks[i];
    }
}
