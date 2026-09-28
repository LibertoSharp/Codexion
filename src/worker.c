#include "simulation.h"
#include "worker.h"
#include "utils/timeutils.h"
#include "utils/ft_utils.h"
#include <stdio.h>
#include <unistd.h>
#include "utils/worker_utils.h"

static long long get_rounded_time(t_simulation *sim)
{
    long long t = TIME - sim->start_time;
    t = ((t + 5) / 10) * 10;
    return t + sim->start_time;
}

static int queue_dongle(t_coder *coder, t_dongle *dongle)
{
    long long cooldown;
    long long remaining;
    struct timespec _timespec;

    pthread_mutex_lock(&dongle->mutex);
    coder->arrival_time = get_rounded_time(coder->sim);
    heap_append(dongle->priority_queue, (void *)coder);
    pthread_mutex_unlock(&dongle->mutex);
    usleep(500);
    pthread_mutex_lock(&dongle->mutex);
    cooldown = coder->sim->settings->dongle_cooldown;
    while (1)
    {
        remaining = get_remaining_cooldown(dongle, cooldown);
        if (remaining <= 3)
            remaining = 0;
        if (!dongle->occupied && remaining <= 0 && heap_peek(dongle->priority_queue) == (void *)coder)
            break;
        if (remaining > 0)
        {
            _timespec = ms_to_timespec(remaining);
            pthread_cond_timedwait(&dongle->cond, &dongle->mutex, &_timespec);
        }
        else
            pthread_cond_wait(&dongle->cond, &dongle->mutex);
        if (!is_running(coder->sim))
        {
            pthread_mutex_unlock(&dongle->mutex);
            return 0;
        }
    }
    dongle->occupied = 1;
    heap_pop(dongle->priority_queue);
    print_status(coder, "has taken a dongle");
    pthread_mutex_unlock(&dongle->mutex);
    return 1;
}

static void release_dongle(t_coder *coder, t_dongle *dongle)
{
    pthread_mutex_lock(&dongle->mutex);
    dongle->occupied = 0;
    dongle->last_time_used = get_rounded_time(coder->sim);
    pthread_cond_broadcast(&dongle->cond);
    pthread_mutex_unlock(&dongle->mutex);
}

void *worker(void *arg)
{
    t_coder *coder;

    coder = (t_coder *)arg;
    if (coder->c_id % 2 != 0)
        ft_swap((void *)&coder->dongles[0], (void *)&coder->dongles[1]);
    while (is_running(coder->sim))
    {
        if (!queue_dongle(coder, coder->dongles[0]))
            return NULL;
        if (!queue_dongle(coder, coder->dongles[1]))
            return NULL;
        pthread_mutex_lock(&coder->mutex);
        coder->last_compilation = get_rounded_time(coder->sim) + 5;
        pthread_mutex_unlock(&coder->mutex);
        print_status(coder, "is compiling");
        precise_sleep(coder->sim->settings->time_to_compile, coder->sim);
        release_dongle(coder, coder->dongles[0]);
        release_dongle(coder, coder->dongles[1]);
        print_status(coder, "is debugging");
        precise_sleep(coder->sim->settings->time_to_debug, coder->sim);
        print_status(coder, "is refactoring");
        precise_sleep(coder->sim->settings->time_to_refactor, coder->sim);
        pthread_mutex_lock(&coder->mutex);
        coder->compilation_count++;
        pthread_mutex_unlock(&coder->mutex);
    }
    return NULL;
}
