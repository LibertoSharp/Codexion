#include "scheduler_functions.h"
#include "simulation.h"
#include "utils/timeutils.h"
int fifo(void *e1, void *e2)
{
	(void)e1;
	(void)e2;
	return 1;
}

int edf(void *e1, void *e2)
{
    t_coder *left = (t_coder *)e1;
    t_coder *right = (t_coder *)e2;

    return (left->last_compilation <= right->last_compilation);
}

void set_scheduler_function(t_settings *settings, t_dongle *dongle)
{
	if (settings->scheduler == S_FIFO)
		dongle->priority_queue->order_func = fifo;
	else if (settings->scheduler == S_EDF)
		dongle->priority_queue->order_func = edf;
}
