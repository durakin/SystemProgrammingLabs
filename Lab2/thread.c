/*! \file   thread.c
 *  \brief  Implements a function of thread.c
 */

#include "thread.h"


void* aircraftThreadFunction(void* arg)
{
    srand(time(NULL));


    Aircraft* aircraftObject = (Aircraft*) arg;

    printf("Aircraft %d is asking for land\n", aircraftObject->number);

    sem_wait(&(aircraftObject->airfieldObject->airfieldQueueSem));
    printf("Aircraft %d is permitted to land\n", aircraftObject->number);

    pthread_mutex_lock(&(aircraftObject->airfieldObject->airfieldBusyMutex));
    landAircraft(aircraftObject);
    printf("Aircraft %d has just landed\n",
           aircraftObject->number);

    pthread_mutex_unlock(
            &(aircraftObject->airfieldObject->airfieldBusyMutex));


    randomNanosleep(MIN_SLEEP, BIG_SLEEP);


    printf("Aircraft %d is getting parked\n", aircraftObject->number);
    *(aircraftObject->strip) = EMPTY_STRIP;
    aircraftObject->strip = NULL;

    sem_post(&(aircraftObject->airfieldObject->airfieldQueueSem));
    printf("Aircraft %d has just been parked\n",
           aircraftObject->number);

    free(aircraftObject);

    return NULL;
}
