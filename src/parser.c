#include "../include/parser.h"
typedef struct action{
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