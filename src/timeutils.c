#include <time.h>

long long	get_time_ms(void) {
    struct timespec ts;
    clock_gettime(1, &ts);
    return ((long long)ts.tv_sec * 1000) + (ts.tv_nsec / 1000000);
}

struct timespec ms_to_timespec(long long milliseconds)
{
    struct timespec ts;

    clock_gettime(0, &ts);

    ts.tv_sec += milliseconds / 1000;
    ts.tv_nsec += (milliseconds % 1000) * 1000000;

    if (ts.tv_nsec >= 1000000000)
    {
        ts.tv_sec += 1;
        ts.tv_nsec -= 1000000000;
    }

    return (ts);
}
