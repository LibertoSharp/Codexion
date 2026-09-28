/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_monitor.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luca <luca@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 00:00:00 by luca              #+#    #+#             */
/*   Updated: 2026/09/28 14:00:58 by luca             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simulation.h"
#include "utils/timeutils.h"
#include "utils/worker_utils.h"

static int	monitor_coder(t_simulation *simulation, int i)
{
	int	all_completed;

	all_completed = 1;
	pthread_mutex_lock(&simulation->coders[i].mutex);
	if (get_time_ms() - simulation->coders[i].last_compilation
		> simulation->settings->time_to_burnout)
	{
		print_status(&simulation->coders[i], "burned out");
		stop_running(simulation);
	}
	if (simulation->coders[i].compilation_count
		< simulation->settings->number_of_compiles_required)
		all_completed = 0;
	pthread_mutex_unlock(&simulation->coders[i].mutex);
	return (all_completed);
}

void	stop_running(t_simulation *sim)
{
	int	i;

	pthread_mutex_lock(&sim->state_mutex);
	sim->running = 0;
	pthread_mutex_unlock(&sim->state_mutex);
	i = 0;
	while (i < sim->settings->number_of_coders)
	{
		pthread_cond_broadcast(&sim->dongles[i].cond);
		i++;
	}
}

void	monitor(t_simulation *simulation)
{
	int	i;
	int	all_completed;

	while (is_running(simulation))
	{
		i = -1;
		all_completed = 1;
		while (++i < simulation->settings->number_of_coders)
		{
			if (!monitor_coder(simulation, i))
				all_completed = 0;
		}
		if (all_completed)
			stop_running(simulation);
	}
}
