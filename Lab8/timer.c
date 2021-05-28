/*! \file   timer.c
 *  \brief  Implements functions from timer.h
 */

#include <time.h>
#include "timer.h"
#include "input.h"


char* GetTimeString()
{
    struct tm* localTime;
    const time_t timer = time(NULL);
    localTime = localtime(&timer);
    char* result;
    result = (char*) malloc(INPUT_SIZE);
    strftime(result, INPUT_SIZE, "%Y-%m-%d %H:%M:%S", localTime);
    return (result);
}

struct itimerval InitTimer(int seconds, int microSeconds)
{
    struct itimerval timer;
    timer.it_value.tv_sec = seconds;
    timer.it_value.tv_usec = microSeconds;
    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_usec = 0;
    return timer;
}

void RollbackTimer(struct itimerval* timer, int seconds, int microSeconds)
{
    timer->it_value.tv_sec = seconds;
    timer->it_value.tv_usec = microSeconds;
    setitimer(ITIMER_REAL, timer, NULL);
}

struct sigaction CreateSAHandler(void* TimerHandler)
{
    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = TimerHandler;
    return sa;
}
