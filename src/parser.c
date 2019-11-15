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
void fillActionWithValue(char * key, char * value, struct_action * action)
{
    /* set default */
    action->name = malloc(20);
    strcpy(action->name,"no name");
    action->name = malloc(20);
    strcpy(action->url,"no url");
    action->max_depth = 0;
    action->versioning = 0;
    action->type[0] = malloc(20);
    strcpy(action->type[0], "no type");
    if(strcmp(key,"max-depth") == 0) action->max_depth = isNumber(value);
}
void timeToSeconds(char * time, char * value, int long long * seconds)
{
    if (strcmp(time,"second")  == 0) *seconds += isNumber(value);
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
void checkKey(char * line, int actionN, int action, struct_action * p_action, int taskN, int task, int ** nbActionsPerTasks,  int long long * seconds)
{
    if(*line != '{' && *line != '(') return;
    if(action)
        printf("\n\n\nACTIONS%d : \nline : %s", actionN, line);
    if(task)
        printf("\n\n\nTASKS%d : \nline : %s", taskN, line);
    if(*line == '{') {
        int mode;
        if(action) mode = 1;
        else if(task) mode = 2;
        else return; /* no mode, wtf ?*/
        char * key = calloc(256, sizeof(char));
        char * value = calloc(256, sizeof(char));
        const char delim[4] = "{->}";
        char * token = strtok(line, delim);
        while(token != NULL) {
            /* special case for max-depth */
            if(strcmp(token,"max") == 0) {
                strcpy(key, token);
                strcat(key,"-depth");
            } else if(isKeyActionValid(token, mode)) strcpy(key, token);
            else strcpy(value,token);
            token = strtok(NULL, delim);
        }
        if( strlen(key) != 0 && key && value && strlen(value) != 0) {
            printf("\nkey : %s", key);
            printf("\nvalue : %s", value);
            timeToSeconds(key, value, seconds);
        } else printf("  ---> INVALID LINE\n");
        //fillActionWithValue(key,value,p_action);
    } else {
        /* it's the line in a task that tells what are the actions */
        int countActionPerTask = 0;
        if(*line == '(' && task) {
            printf("\n%s", line);
            char * token = strtok(line, ",");
            if(token) countActionPerTask++;
            while((token = strtok(NULL,",")) != NULL)
                countActionPerTask++;
        }
        if(task) {
            nbActionsPerTasks = realloc(nbActionsPerTasks,sizeof(int*)*taskN);
            nbActionsPerTasks[taskN-1] = malloc(sizeof(int));
            nbActionsPerTasks[taskN-1][0] = countActionPerTask;
        }
    }
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
    if (mode == 1) {
        if ((strcmp(key,"type")             == 0 )||
                (strcmp(key,"versioning")   == 0) ||
                (strcmp(key,"url")          == 0))
            return 1;
    } else if (mode == 2) {
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
void checkMode(const char * line, int * inAction, int * inTask, int * nbActions, int * nbTasks, int * next, int * new)
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
void readConfigurationFile(FILE * config, struct_tasks * tasks, struct_actions * actions)
{
    char line[300];
    char firstChar[5] = "=({+";
    int countLine = 1;
    int inTask = 0, nbTasks = 0;
    int inAction = 0, nbActions = 0;
    int ** nbActionsPerTasks;
    actions = malloc(sizeof(struct_actions));
    actions->action = malloc(sizeof(struct_action));
    int long long seconds = 0;
    int long long * pseconds = &seconds;
    int long long * secondsPerTasks = calloc(1,sizeof(int long long));
    nbActionsPerTasks = malloc(sizeof(int *));
    *nbActionsPerTasks = malloc(sizeof(int));
    while(fgets(line, 300, config)) {
        line[(strchr(line,'\n') - line)] = '\0';
        removeComment(line); /* work correctly */
        if(!strchr(firstChar, line[0])) {
            fprintf(stderr,"\n%c syntax error at %d:1",*line,countLine);
            return;
        }
        int nextAction = 0, newAction = 1; /* check if we are in a new action */
        int currentNbTask = nbTasks; /* check if we are in a new tasks */
        int currentNbAction = nbActions;
        checkMode(line, &inAction, &inTask, &nbActions, &nbTasks, &nextAction, &newAction);
        if(inTask) {
            printf("\nsending &actions->action[%d], memory address : %p", nbActions-1, &actions->action[0]);
            checkKey(line, 0, 0, &actions->action[nbActions-1],nbTasks, 1, nbActionsPerTasks, pseconds);
        }
        if(inAction) {
            printf("\nsending &actions->action[%d], memory address : %p", nbActions-1, &actions->action[0]);
            checkKey(line, nbActions, 1,&actions->action[nbActions-1], 0, 0, 0, 0);
        }
        if(nbTasks || currentNbTask != nbTasks) {
            secondsPerTasks = realloc(secondsPerTasks,nbTasks);
            secondsPerTasks[nbTasks-1] += seconds;
            seconds = 0;
        }
        if(currentNbAction != nbActions) {
            actions->action = realloc(actions->action,sizeof(struct_action)*nbActions);
        }
        countLine = countLine + 1;
    }
    tasks->nbTasks = nbTasks;
    tasks->task = malloc(sizeof(struct_task) * nbTasks);
    for(int i = 0; i < nbTasks; i++) {
        tasks->task[i].actions = malloc(sizeof(struct_action) * *nbActionsPerTasks[i]);
        tasks->task[i].nbActions = *nbActionsPerTasks[i];
        tasks->task[i].second = secondsPerTasks[i];
    }
}
