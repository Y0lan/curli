//
// Created by yolan on 01/11/2019.
//

#ifndef CURLI_STRUCT_H
#define CURLI_STRUCT_H
typedef struct struct_action {
    char * name;
    char * url;
    unsigned int max_depth;
    unsigned short versioning;
    char ** type;
} struct_action;

typedef struct struct_actions {
    struct_action * action;
    int nbActions;
} struct_actions;

typedef struct struct_task {
    struct_action * actions;
    unsigned long long  second; /* Let's say that we will count the time before each action in second */
    unsigned int nbActions;
} struct_task;

typedef struct struct_tasks {
    struct_task * task;
    unsigned int nbTasks;
} struct_tasks;

#endif //CURLI_STRUCT_H
