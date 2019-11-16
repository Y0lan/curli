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
    unsigned int numberOfTypes;
} struct_action;

typedef struct struct_actions {
    struct_action * action;
    int numberOfActions; // OK
} struct_actions;

typedef struct struct_task {
    struct_action * actions;
    unsigned long long  second; // OK
    unsigned int numberOfActions; // OK
} struct_task;

typedef struct struct_tasks {
    struct_task * task; // OK
    unsigned int numberOfTasks; // OK
} struct_tasks;

#endif //CURLI_STRUCT_H
