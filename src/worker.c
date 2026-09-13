#include "simulation.h"
#include "worker.h"
#include <stdio.h>

void	*worker(void *arg)
{
	t_coder *coder;

	coder = (t_coder *)arg;

	while(coder->sim->running)
	{
		printf("Coder %d is working...\n", coder->c_id);
	}
	return NULL;
}