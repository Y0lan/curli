//
// Created by yolan on 17/11/2019.
//

#include "include/scheduler.h"
void showTasks(struct_tasks * tasks)
{
    uint i, j, z;
    for (i = 0; i < tasks->numberOfTasks; i++) {
        printf("\nseconds of tasks->%d : %lld", i+1, tasks->task[i].second);
        printf("\nnumber of actions for tasks->%d : %d", i+1, tasks->task[i].numberOfActions);
        for( j = 0 ; j < tasks->task[i].numberOfActions; j++) {
            printf("\ntask : %d have action: \n",i,j);
            printf("\nname: %s", tasks->task[i].actions[j].name);
            printf("\nurl: %s",tasks->task[i].actions[j].url);
            printf("\nversioning : %d", tasks->task[i].actions[j].versioning);
            printf("\nmax-depth : %d", tasks->task[i].actions[j].max_depth);
            for( z = 0; z < tasks->task[i].actions[j].numberOfTypes; z++) {
                printf("\ntype: %s",tasks->task[i].actions[j].type[z]);
            }
        }
    }

}
void * threadClockFunc( void * args)
{
    struct_tasks * tasks = args;
    uint i, j, z;
    /*
    for (i = 0; i < tasks->numberOfTasks; i++) {
        printf("\nseconds of tasks->%d : %lld", i+1, tasks->task[i].second);
        printf("\nnumber of actions for tasks->%d : %d", i+1, tasks->task[i].numberOfActions);
        for( j = 0 ; j < tasks->task[i].numberOfActions; j++) {
            printf("\ntask : %d have action: \n",i,j);
            printf("\nname: %s", tasks->task[i].actions[j].name);
            printf("\nurl: %s",tasks->task[i].actions[j].url);
            printf("\nversioning : %d", tasks->task[i].actions[j].versioning);
            printf("\nmax-depth : %d", tasks->task[i].actions[j].max_depth);
            for( z = 0; z < tasks->task[i].actions[j].numberOfTypes; z++) {
                printf("\ntype: %s",tasks->task[i].actions[j].type[z]);
            }
        }
    }
     */
//showTasks(tasks);
    int ret;
    for (i = 0; i < tasks->numberOfTasks; i++) {
        pthread_t threadTask;
        ret = pthread_create(&threadTask, NULL, threadClockFunc,&tasks->task[i]);
        if(ret == 0) pthread_join(threadTask,NULL);
    }

    pthread_exit(NULL);
}


void * threadTaskFunc( void * args)
{
    struct_task * task = args;
    uint i = 0, z = 0;
    for( ; i < task->numberOfActions; i++) {
        printf("\ntask : %d have action: \n",i);
        printf("\nname: %s", task[i].actions[i].name);
        printf("\nurl: %s",task[i].actions[i].url);
        printf("\nversioning : %d", task[i].actions[i].versioning);
        printf("\nmax-depth : %d", task[i].actions[i].max_depth);
        for( z = 0; z < task[i].actions[i].numberOfTypes; z++) {
            printf("\ntype: %s",task[i].actions[i].type[z]);
        }
    }
    pthread_exit(NULL);
}
