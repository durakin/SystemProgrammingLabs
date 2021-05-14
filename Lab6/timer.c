#include <time.h>
#include "timer.h"
#include "input.h"


/*!
 * \brief Возвращает текущее время в строковом представлении.
 * \return char* Время
*/
char* GetTimeString()
{
    struct tm* localTime;
    const time_t timer = time(NULL);
    localTime = localtime(&timer);
    char* result;
    result = (char*) malloc(INPUT_SIZE);
    strftime(result, INPUT_SIZE, "%Y-%m-%d %H:%M:%S", localTime);
    return(result);
}


/*!
 * \brief Создает таймер.
 * \param[in] sec Количество секунд.
 * \param[in] usec Количество микросекунд
 * \return Таймер struct itimerval
*/
struct itimerval InitTimer(int sec, int usec)
{
    struct itimerval timer;
    timer.it_value.tv_sec = sec;
    timer.it_value.tv_usec = usec;
    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_usec = 0;
    return timer;
}

/*!
 * \brief Откатывает таймер на определенное время.
 * \param[in] sec Количество секунд, через которые таймер сработает.
 * \param[in] usec Количество микросекунд.
 * \return void
*/
void RollbackTimer(struct itimerval *timer, int sec, int usec)
{
    timer->it_value.tv_sec = sec;
    timer->it_value.tv_usec = usec;
    setitimer(ITIMER_REAL, timer, NULL);
}

/*!
 * \brief Создает обработчик сигналов.
 * \param[in] TimerHandler Функция обработчик sa_handler, принимает один аргумент.
 * \return struct sigaction
*/
struct sigaction CreateSAHandler(void* TimerHandler)
{
    struct sigaction sa;
    memset(&sa, 0, sizeof (sa));
    sa.sa_handler = TimerHandler;
    return sa;
}
