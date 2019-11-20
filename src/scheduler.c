#include "include/scheduler.h"
void * threadTaskFunc( void * args)
{
    struct_task * task = args;
    uint i = 0, z = 0;
    for( ; i < task->numberOfActions; i++) {
        if(curlLink(task->actions[i].url,NULL,task->actions[i].max_depth,task->actions[i].versioning,task->actions[i].type,task->actions[i].numberOfTypes))
            printf("went well");
        NULL;
    }
    pthread_exit(NULL);
}

