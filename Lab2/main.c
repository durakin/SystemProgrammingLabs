#include <malloc.h>
#include "thread.h"
#include <stdbool.h>
int main(int argc, char* argv[])
{
    int n = 5;

    int aircraftNumber = 1;

    airfield* airfieldObject = (airfield*) malloc(sizeof(airfield));
    airfieldObject->landingStrips = (int*) malloc(n * sizeof(int));
    airfieldObject->numberOfStrips = n;

    for (int i = 0; i < n; i++)
    {
        airfieldObject->landingStrips[i] = EMPTY_STRIP;
    }

    sem_init(&(airfieldObject->airfieldQueueSem), 0, n);
    pthread_mutex_init(&(airfieldObject->airfieldBusyMutex), NULL);

    while (true)
    {
        aircraft* aircraftObject = (aircraft*) malloc(sizeof(aircraft));
        aircraftObject->airfieldObject = airfieldObject;
        aircraftObject->number = aircraftNumber++;
        aircraftObject->strip = NULL;
        pthread_t threadId;
        pthread_create(&threadId, NULL, &aircraftThreadFunction,
                       aircraftObject);

        randomNanosleep(MIN_SLEEP, SMALL_SLEEP);

    }


}