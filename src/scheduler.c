//
// Created by yolan on 17/11/2019.
//

#include "include/scheduler.h"

void * threadTask( void * args)
{
    pthread_exit(NULL);
}
void * threadTimer(void * args)
{
    pthread_exit(NULL);
}
void * threadClock( void * args)
{
    struct_tasks * tasks = args;

    for (int i = 0; i < tasks->numberOfTasks; i++) {
        printf("\nseconds of tasks %d : %lld", i+1, tasks->task[i].second);
        printf("\nnumber of actions for tasks %d : %d", i+1, tasks->task[i].numberOfActions);
    }
    pthread_exit(NULL);
}

void * threadUpdateScheduler( void * args)
{
    pthread_exit(NULL);
}

