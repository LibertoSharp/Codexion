#include "utils/worker_utils.h"
#include "utils/timeutils.h"
#include <stdio.h>
#include <unistd.h>

void print_status(t_coder *coder, const char *status)
{
    long long now;

    pthread_mutex_lock(&coder->sim->print_mutex);
    
    if (is_running(coder->sim))
    {
        now = TIME - coder->sim->start_time;
        printf("%lld %d %s\n", now, coder->c_id + 1, status);
    }
    
    pthread_mutex_unlock(&coder->sim->print_mutex);
}

void sleep_remaining_cooldown(t_dongle *d, long long cooldown)
{
    long long elapsed = TIME - d->last_time_used;
    if (elapsed < cooldown)
        usleep((cooldown - elapsed) * 1000);
}