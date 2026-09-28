/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   worker.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lavverat <lavverat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 13:33:20 by luca              #+#    #+#             */
/*   Updated: 2026/09/28 19:09:23 by lavverat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simulation.h"
#include "worker.h"
#include "utils/timeutils.h"
#include "utils/ft_utils.h"
#include <stdio.h>
#include <unistd.h>
#include "utils/worker_utils.h"

long long	get_rounded_time(t_simulation *sim)
{
	long long	t;

	t = get_time_ms() - sim->start_time;
	t = ((t + 5) / 10) * 10;
	return (t + sim->start_time);
}

static int	wait_for_dongle(t_coder *coder, t_dongle *dongle,
		long long cooldown)
{
	long long		remaining;
	struct timespec	_timespec;

	while (1)
	{
		if (!is_running(coder->sim))
		{
			heap_remove(dongle->priority_queue, coder);
			pthread_mutex_unlock(&dongle->mutex);
			return (0);
		}
		remaining = get_remaining_cooldown(dongle, cooldown);
		if (remaining <= 3)
			remaining = 0;
		if (!dongle->occupied && remaining <= 0
			&& heap_peek(dongle->priority_queue) == (void *)coder)
			break ;
		if (remaining > 0)
		{
			_timespec = ms_to_timespec(remaining);
			pthread_cond_timedwait(&dongle->cond, &dongle->mutex, &_timespec);
		}
		else
			pthread_cond_wait(&dongle->cond, &dongle->mutex);
	}
	return (1);
}

int	queue_dongle(t_coder *coder, t_dongle *dongle)
{
	long long	cooldown;

	pthread_mutex_lock(&dongle->mutex);
	coder->arrival_time = get_rounded_time(coder->sim);
	heap_append(dongle->priority_queue, (void *)coder);
	pthread_mutex_unlock(&dongle->mutex);
	usleep(500);
	pthread_mutex_lock(&dongle->mutex);
	cooldown = coder->sim->settings->dongle_cooldown;
	if (!wait_for_dongle(coder, dongle, cooldown))
		return (0);
	dongle->occupied = 1;
	heap_pop(dongle->priority_queue);
	print_status(coder, "has taken a dongle");
	pthread_mutex_unlock(&dongle->mutex);
	return (1);
}

void	release_dongle(t_coder *coder, t_dongle *dongle)
{
	pthread_mutex_lock(&dongle->mutex);
	dongle->occupied = 0;
	dongle->last_time_used = get_rounded_time(coder->sim);
	pthread_cond_broadcast(&dongle->cond);
	pthread_mutex_unlock(&dongle->mutex);
}

void	*worker(void *arg)
{
	t_coder	*coder;

	coder = (t_coder *)arg;
	if (coder->c_id % 2 != 0)
		ft_swap((void *)&coder->dongles[0], (void *)&coder->dongles[1]);
	while (is_running(coder->sim))
	{
		if (!worker_cycle(coder))
			return (NULL);
	}
	return (NULL);
}
