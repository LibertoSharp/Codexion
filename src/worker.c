#include "simulation.h"
#include "worker.h"
#include "timeutils.h"
#include <stdio.h>
#include <unistd.h>

static void take_dongles(t_coder *coder)
{
	int count;
	int left;
	int right;
	long left_remaining;
	long right_remaining;

	count = coder->sim->settings->number_of_coders;
	left = coder->c_id;
	right = (coder->c_id+1) % count;

	if (coder->sim->dongles[left].busy || coder->sim->dongles[right].busy)
	{
		left_remaining = coder->sim->settings->dongle_cooldown - TIME + coder->sim->dongles[left].last_time_used;
		right_remaining = coder->sim->settings->dongle_cooldown - TIME + coder->sim->dongles[right].last_time_used;

		pthread_cond_timedwait(coder.cond, dummy, ms_to_timespec(max(left_remaining, right_remaining)));
	}

	pthread_mutex_lock(&coder->sim->dongles[left].mutex);
	pthread_mutex_lock(&coder->sim->dongles[right].mutex);
	coder->sim->dongles[left].busy = 1;
	coder->sim->dongles[right].busy = 1;
}

static void release_dongles(t_coder *coder)
{
	int count;
	int index;

	count = coder->sim->settings->number_of_coders;
	index = ((coder->c_id+offset) % count + count) % count;

	pthread_mutex_unlock(&coder->sim->dongles[index].mutex);
	coder->sim->dongles[index].last_time_used = TIME;
	coder->sim->dongles[index].busy = 1;
}

static void compile(t_coder *coder)
{
	long long time;

	time = TIME - coder->sim->start_time;
	take_dongles(coder);
	printf("%lld %d has taken a dongle\n", time, coder->c_id);
	printf("%lld %d has taken a dongle\n", time, coder->c_id);

	printf("%lld %d is compiling\n", time, coder->c_id);
	usleep(coder->sim->settings->time_to_compile * 1000);
	release_dongles(coder);
	coder->compilation_count++;
}

void	*worker(void *arg)
{
	t_coder *coder;
	long long time;

	coder = (t_coder *)arg;
	while(coder->sim->running)
	{
		time = TIME - coder->sim->start_time;

		compile(coder);
		
		printf("%lld %d is debugging\n", time, coder->c_id);
		usleep(coder->sim->settings->time_to_debug * 1000);

		printf("%lld %d is refactoring\n", time, coder->c_id);
		usleep(coder->sim->settings->time_to_refactor * 1000);
	}
	return NULL;
}
