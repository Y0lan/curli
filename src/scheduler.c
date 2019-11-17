//
// Created by yolan on 17/11/2019.
//

#include "include/scheduler.h"

void * threadTask( void * args){
    pthread_exit(NULL);
}
void * threadTimer(void * args){

}
void * threadClock( void * args){
    while(1){
        pthread_t threadTask;
        pthread_t threadTimer;
    }
    pthread_exit(NULL);
}

void * threadUpdateScheduler( void * args){
    pthread_exit(NULL);
}

