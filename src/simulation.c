#include "simulation.h"
#include <stdio.h>
#include <stdlib.h>
#include "worker.h"


static t_simulation	*create_simulation(t_settings *settings)
{
	t_simulation *simulation;
	int i;

	simulation = (t_simulation *)malloc(sizeof(t_simulation));
	simulation->coders = (t_coder *)malloc(sizeof(t_coder) * settings->number_of_coders);

	i = 0;
	while (i < settings->number_of_coders)
	{
		simulation->coders[i].sim = simulation;
		simulation->coders[i].c_id = i;
		i++;
	}
	simulation->running = 1;

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
		pthread_create(&simulation->coders->t_id, NULL, worker, simulation->coders + i);
		i++;
	}

	i = 0;
	while(i < settings->number_of_coders)
		pthread_join(simulation->coders[i++].t_id, NULL);
	
}
