#include "simulation.h"
#include <stdio.h>
#include <stdlib.h>
#include "worker.h"
#include "utils/timeutils.h"
#include "utils/ft_utils.h"

static t_simulation	*create_simulation(t_settings *settings)
{
	t_simulation *simulation;
	int i;

	simulation = (t_simulation *)ft_calloc(1, sizeof(t_simulation));
	simulation->settings = settings;
	simulation->coders = (t_coder *)ft_calloc( settings->number_of_coders, sizeof(t_coder));
	simulation->dongles = (t_dongle *)ft_calloc(settings->number_of_coders, sizeof(t_dongle));
    pthread_mutex_init(&simulation->print_mutex, NULL);
	pthread_mutex_init(&simulation->state_mutex, NULL);

	i = 0;
	while (i < settings->number_of_coders)
	{
		simulation->coders[i].sim = simulation;
		simulation->coders[i].c_id = i;
		simulation->coders[i].last_compilation = TIME;
		pthread_mutex_init(&simulation->dongles[i].mutex, NULL);
		pthread_mutex_init(&simulation->coders[i].mutex, NULL);
		i++;
	}
	simulation->running = 1;
	simulation->start_time = TIME;

	return (simulation);
}

int is_running(t_simulation *sim)
{
	int ret;

	pthread_mutex_lock(&sim->state_mutex);
	ret = sim->running;
	pthread_mutex_unlock(&sim->state_mutex);

	return (ret);
}

static void stop_running(t_simulation *sim)
{
	pthread_mutex_lock(&sim->state_mutex);
	sim->running = 0;
	pthread_mutex_unlock(&sim->state_mutex);
}

static void wait_coders(t_simulation *sim)
{
	int i;
	
	i = 0;
	while (i < sim->settings->number_of_coders)
	{
		pthread_join(sim->coders[i].t_id, NULL);
		i++;
	}
}

static void monitor(t_simulation *simulation)
{
	int	i;
	int all_completed;

	while(is_running(simulation))
	{
		i = -1;
		all_completed = 1;
		while (++i < simulation->settings->number_of_coders)
		{
			pthread_mutex_lock(&simulation->coders[i].mutex);
			if (TIME - simulation->coders[i].last_compilation > simulation->settings->time_to_burnout)
			{
				print_status(&simulation->coders[i], "burned out");
				stop_running(simulation);
			}

			if (simulation->coders[i].compilation_count < simulation->settings->number_of_compiles_required)
				all_completed = 0;
			
			pthread_mutex_unlock(&simulation->coders[i].mutex);
		}

		if (all_completed)
			stop_running(simulation);
	}
}

void	run(t_settings *settings)
{
	t_simulation *simulation;
	int i;

	simulation = create_simulation(settings);
	
	i = 0;
	while (i < settings->number_of_coders)
	{
		pthread_create(&simulation->coders[i].t_id, NULL, worker, simulation->coders + i);
		i++;
	}

	monitor(simulation);
	wait_coders(simulation);

	i = 0;
	while (i < settings->number_of_coders)
	{
		pthread_mutex_destroy(&simulation->coders[i].mutex);
		pthread_mutex_destroy(&simulation->dongles[i].mutex);
		i++;
	}
	pthread_mutex_destroy(&simulation->state_mutex);
	pthread_mutex_destroy(&simulation->print_mutex);
	free(simulation->coders);
	free(simulation->dongles);
	free(simulation->settings);
	free(simulation);
}
