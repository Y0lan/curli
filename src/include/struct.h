//
// Created by yolan on 01/11/2019.
//

#ifndef CURLI_STRUCT_H
#define CURLI_STRUCT_H
typedef struct action {
    char * name;
    char * url;
    unsigned int max_depth;
    unsigned short versioning;
    char ** type;
} action;

typedef struct task {
    action * actions;
    unsigned long  second; /* Let's say that we will count the time before each action in second */
} task;

#endif //CURLI_STRUCT_H
