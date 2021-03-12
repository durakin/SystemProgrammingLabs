//
// Created by Albert Nepomnyashiy on 3/13/2021.
//

#include <semaphore.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>
#ifndef TASK11_H
#define TASK11_H

enum constants
{
    EMPTY_STRIP = -1,
    SMALL_SLEEP = 2,
    BIG_SLEEP = 30,
    MIN_SLEEP = 1
};

typedef struct
{
    int numberOfStrips;
    int* landingStrips;
    sem_t airfieldQueueSem;
    pthread_mutex_t airfieldBusyMutex;
} airfield;

typedef struct
{
    int number;
    int* strip;
    airfield* airfieldObject;
} aircraft;

void landAircraft(aircraft* aircraftToLand);

void randomNanosleep(int minSeconds, int maxSeconds);


#endif //TASK11_H
