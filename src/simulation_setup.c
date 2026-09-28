/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_setup.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luca <luca@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 00:00:00 by luca              #+#    #+#             */
/*   Updated: 2026/09/28 13:56:57 by luca             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simulation.h"
#include "utils/ft_utils.h"
#include "utils/timeutils.h"
#include "scheduler_functions.h"

static void	initialize_coder(t_simulation *simulation, t_settings *settings,
		int i)
{
	simulation->coders[i].sim = simulation;
	simulation->coders[i].c_id = i;
	simulation->coders[i].last_compilation = get_time_ms();
	simulation->coders[i].dongles[0] = &simulation->dongles[i];
	simulation->coders[i].dongles[1] = (&simulation->dongles[(i + 1)
			% settings->number_of_coders]);
	pthread_mutex_init(&simulation->dongles[i].mutex, NULL);
	pthread_mutex_init(&simulation->coders[i].mutex, NULL);
	simulation->dongles[i].priority_queue = heap_allocate(2);
	pthread_cond_init(&simulation->dongles[i].cond, NULL);
	set_scheduler_function(settings, simulation->dongles + i);
	simulation->dongles[i].occupied = 1;
}

t_simulation	*create_simulation(t_settings *settings)
{
	t_simulation	*simulation;
	int				i;

	simulation = (t_simulation *)ft_calloc(1, sizeof(t_simulation));
	simulation->settings = settings;
	simulation->coders = (t_coder *)ft_calloc(settings->number_of_coders,
			sizeof(t_coder));
	simulation->dongles = (t_dongle *)ft_calloc(settings->number_of_coders,
			sizeof(t_dongle));
	pthread_mutex_init(&simulation->print_mutex, NULL);
	pthread_mutex_init(&simulation->state_mutex, NULL);
	i = -1;
	while (++i < settings->number_of_coders)
		initialize_coder(simulation, settings, i);
	simulation->running = 1;
	simulation->start_time = get_time_ms();
	return (simulation);
}
