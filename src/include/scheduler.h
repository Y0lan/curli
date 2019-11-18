//
// Created by yolan on 17/11/2019.
//

#ifndef CURLI_SCHEDULER_H
#define CURLI_SCHEDULER_H

#include "main.h"
/*
pthread_cond_t condition = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
 */

void * threadTask( void * args);
void * threadClock( void * args);
void * threadUpdateScheduler( void * args);


#endif //CURLI_SCHEDULER_H
