/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_run.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lavverat <lavverat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 00:00:00 by luca              #+#    #+#             */
/*   Updated: 2026/09/28 18:58:26 by lavverat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simulation.h"
#include "worker.h"
#include "utils/timeutils.h"
#include <stdlib.h>
#include <unistd.h>

static void	start_workers(t_simulation *simulation)
{
	int	i;

	i = 0;
	while (i < simulation->settings->number_of_coders)
	{
		pthread_create(&simulation->coders[i].t_id, NULL, worker,
			simulation->coders + i);
		i++;
	}
}

static void	initialize_runtime(t_simulation *simulation, t_settings *settings)
{
	int	i;

	usleep(50000);
	simulation->start_time = get_time_ms();
	i = 0;
	while (i < settings->number_of_coders)
	{
		simulation->coders[i].last_compilation = simulation->start_time;
		simulation->dongles[i].last_time_used = simulation->start_time
			- settings->dongle_cooldown;
		i++;
	}
	i = 0;
	while (i < settings->number_of_coders)
	{
		pthread_mutex_lock(&simulation->dongles[i].mutex);
		simulation->dongles[i].occupied = 0;
		pthread_cond_broadcast(&simulation->dongles[i].cond);
		pthread_mutex_unlock(&simulation->dongles[i].mutex);
		i++;
	}
}

void	cleanup_simulation(t_simulation *simulation)
{
	int	i;

	i = 0;
	while (i < simulation->settings->number_of_coders)
	{
		pthread_join(simulation->coders[i].t_id, NULL);
		pthread_mutex_destroy(&simulation->coders[i].mutex);
		pthread_mutex_destroy(&simulation->dongles[i].mutex);
		pthread_cond_destroy(&simulation->dongles[i].cond);
		heap_free(simulation->dongles[i].priority_queue);
		i++;
	}
	pthread_mutex_destroy(&simulation->state_mutex);
	pthread_mutex_destroy(&simulation->print_mutex);
	free(simulation->coders);
	free(simulation->dongles);
	free(simulation->settings);
	free(simulation);
}

void	run(t_settings *settings)
{
	t_simulation	*simulation;

	simulation = create_simulation(settings);
	initialize_runtime(simulation, settings);
	start_workers(simulation);
	monitor(simulation);
	cleanup_simulation(simulation);
}
