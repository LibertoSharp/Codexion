/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   worker_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luca <luca@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 13:24:30 by luca              #+#    #+#             */
/*   Updated: 2026/09/28 13:33:08 by luca             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils/worker_utils.h"
#include "utils/timeutils.h"
#include <stdio.h>
#include <unistd.h>

void	print_status(t_coder *coder, const char *status)
{
	long long	now;

	pthread_mutex_lock(&coder->sim->print_mutex);
	if (is_running(coder->sim))
	{
		now = get_time_ms() - coder->sim->start_time;
		printf("%lld %d %s\n", now, coder->c_id + 1, status);
	}
	pthread_mutex_unlock(&coder->sim->print_mutex);
}

long long	get_remaining_cooldown(t_dongle *dongle, long long cooldown)
{
	return (cooldown - (get_time_ms() - dongle->last_time_used));
}

void	sleep_remaining_cooldown(t_dongle *d, long long cooldown)
{
	long long	elapsed;

	elapsed = get_time_ms() - d->last_time_used;
	if (elapsed < cooldown)
		usleep((cooldown - elapsed) * 1000);
}

void	precise_sleep(long long duration_ms, t_simulation *sim)
{
	long long	start;
	long long	elapsed;

	start = get_time_ms();
	while (is_running(sim))
	{
		elapsed = get_time_ms() - start;
		if (elapsed >= duration_ms)
			break ;
		if (duration_ms - elapsed > 10)
			usleep((duration_ms - elapsed - 10) * 1000);
		else if (duration_ms - elapsed > 2)
			usleep((duration_ms - elapsed - 2) * 1000);
		else
			usleep(50);
	}
}
