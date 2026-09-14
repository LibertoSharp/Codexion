#include "simulation.h"
#include <stdio.h>
#include <stdlib.h>
#include "worker.h"
#include "timeutils.h"

static t_simulation	*create_simulation(t_settings *settings)
{
	t_simulation *simulation;
	int i;

	simulation = (t_simulation *)malloc(sizeof(t_simulation));
	simulation->settings = settings;
	simulation->coders = (t_coder *)malloc(sizeof(t_coder) * settings->number_of_coders);
	simulation->dongles = (t_dongle *)malloc(sizeof(t_dongle) * settings->number_of_coders);

	i = 0;
	while (i < settings->number_of_coders)
	{
		simulation->coders[i].sim = simulation;
		simulation->coders[i].c_id = i;
		pthread_mutex_init(&simulation->dongles[i].mutex, NULL);
		i++;
	}
	simulation->running = 1;
	simulation->start_time = TIME;

	return (simulation);
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

	while(simulation->running)
	{
		i = 0;
		while (i < settings->number_of_coders)
		{
			if (simulation->coders[i++].compilation_count < settings->number_of_compiles_required)
				continue;
			simulation->running = 0;
		}
	}
}
