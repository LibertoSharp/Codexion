#include "simulation.h"
#include "worker.h"
#include "utils/timeutils.h"
#include "utils/ft_utils.h"
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

static void sleep_remaining_cooldown(t_dongle *d, long long cooldown)
{
    long long elapsed = TIME - d->last_time_used;
    if (elapsed < cooldown)
        usleep((cooldown - elapsed) * 1000);
}

static void take_dongles(t_coder *coder)
{
	coder.
}

static void unlock_dongles(t_coder *coder)
{
	int numbers_of_coders;

	numbers_of_coders = coder->sim->settings->number_of_coders;
	t_dongle *left = &coder->sim->dongles[(coder->c_id) % numbers_of_coders];
	t_dongle *right = &coder->sim->dongles[(coder->c_id + 1) % numbers_of_coders];

	left->last_time_used = TIME;
	right->last_time_used = TIME;

	pthread_mutex_unlock(&left->mutex);
	pthread_mutex_unlock(&right->mutex);
}

void	*worker(void *arg)
{
	t_coder *coder;

	coder = (t_coder *)arg;
	while(is_running(coder->sim))
	{
		if (!try_take_dongles_FIFO(coder))
			continue;

		print_status(coder, "has taken a dongle");
		print_status(coder, "has taken a dongle");
		print_status(coder, "is compiling");
		usleep(coder->sim->settings->time_to_compile * 1000);

		pthread_mutex_lock(&coder->mutex);
		coder->last_compilation = TIME;
		coder->compilation_count++;
		pthread_mutex_unlock(&coder->mutex);

		unlock_dongles(coder);
		
		print_status(coder, "is debugging");
		usleep(coder->sim->settings->time_to_debug * 1000);

		print_status(coder, "is refactoring");
		usleep(coder->sim->settings->time_to_refactor * 1000);
	}
	return NULL;
}
