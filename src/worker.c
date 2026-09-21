#include "simulation.h"
#include "worker.h"
#include "utils/timeutils.h"
#include "utils/ft_utils.h"
#include <stdio.h>
#include <unistd.h>
#include "utils/worker_utils.h"

static int take_dongle(t_coder *coder, t_dongle *dongle)
{
	pthread_mutex_lock(&dongle->mutex);
	heap_append(dongle->priority_queue, (void *)coder);

	sleep_remaining_cooldown(dongle, coder->sim->settings->dongle_cooldown);

	while (is_running(coder->sim)
		&& heap_peek(dongle->priority_queue) != (void *)coder)
	{
		pthread_cond_wait(&dongle->cond, &dongle->mutex);
	}
	if (!is_running(coder->sim))
	{
		heap_remove(dongle->priority_queue, coder);
		pthread_cond_broadcast(&dongle->cond);
		pthread_mutex_unlock(&dongle->mutex);
		return (0);
	}

	print_status(coder, "has taken a dongle");
	return (1);
}

static void release_dongle(t_dongle *dongle)
{
	dongle->last_time_used = TIME;
	heap_pop(dongle->priority_queue);
	pthread_cond_broadcast(&dongle->cond);
	pthread_mutex_unlock(&dongle->mutex);
}

static int compile(t_coder *coder, t_simulation *sim)
{
	t_dongle		*left;
	t_dongle		*right;

	left = &sim->dongles[coder->c_id];
	right = &sim->dongles[(coder->c_id + 1) % sim->settings->number_of_coders];

	if (coder->c_id == sim->settings->number_of_coders-1)
		ft_swap((void **)&left, (void **)&right);

	if (!take_dongle(coder, left))
		return (0);

	if (left == right)
	{
		while (is_running(coder->sim))
			pthread_cond_wait(&left->cond, &left->mutex);
		release_dongle(left);
		return (0);
	}

	if (!take_dongle(coder, right))
	{
		release_dongle(left);
		return (0);
	}

	print_status(coder, "is compiling");
	usleep(sim->settings->time_to_compile * 1000);

	release_dongle(left);
	release_dongle(right);

	pthread_mutex_lock(&coder->mutex);
	coder->compilation_count++;
	coder->last_compilation = TIME;
	pthread_mutex_unlock(&coder->mutex);
	return (1);
}

void	*worker(void *arg)
{
	t_coder			*coder;
	t_simulation	*simulation;

	coder = (t_coder *)arg;
	simulation = coder->sim;
	while(is_running(coder->sim))
	{
		if (!compile(coder, simulation))
			continue;

		print_status(coder, "is debugging");
		usleep(simulation->settings->time_to_debug * 1000);
		print_status(coder, "is refactoring");
		usleep(simulation->settings->time_to_refactor * 1000);
	}
	return NULL;
}
