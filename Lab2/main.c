/*! \file   main.c
 *  \brief  Main file of the program. Contains main function
 */

#include <malloc.h>
#include "thread.h"
#include "input.h"
#include <stdbool.h>


/*! \brief Main function
 *
 *  \details Main function. Initialise Airfield, aircrafts numeration
 *  variable, and performs a task. Also provides minimal UI.
 *
 *  \return Doesn't return anything. According to the task, works infinitely.
 */
int main()
{
    printf("Enter number of landing strips ( [1, 1000] )\n");
    int n = CheckedInputInt(NumberOfStripsInputCheck);

    int aircraftNumber = FIRST_AIRCRAFT_NUMBER;

    Airfield* airfieldObject = (Airfield*) malloc(sizeof(Airfield));
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
        Aircraft* aircraftObject = (Aircraft*) malloc(sizeof(Aircraft));
        aircraftObject->airfieldObject = airfieldObject;
        aircraftObject->number = aircraftNumber++;
        aircraftObject->strip = NULL;
        pthread_t threadId;
        pthread_create(&threadId, NULL, &aircraftThreadFunction,
                       aircraftObject);

        randomNanosleep(MIN_SLEEP, SMALL_SLEEP);

    }

}