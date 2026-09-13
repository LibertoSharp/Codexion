#include "parser.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static int	get_positive_integer(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < 48 || str[i] > 57)
			return (-1);
		i++;
	}
	return (atoi(str));
}

t_simulation	*s_parse(int argc, char **argv)
{
	t_simulation	*sim;
	int				i;

	if (argc != 9)
		return (NULL);
	sim = (t_simulation *)malloc(sizeof(t_simulation));
	if (sim == NULL)
		return (NULL);

	i = 0;
	while (i < 7)
	{
		((int *)sim)[i] = get_positive_integer(argv[i+1]);
		if (((int *)sim)[i++] == -1)
			return (free(sim), NULL);
	}

	if (strcmp("fifo", argv[8]) == 0)
		sim->scheduler = S_FIFO;
	else if (strcmp("edf", argv[8]) == 0)
		sim->scheduler = S_EDF;
	else
		return (free(sim), NULL);

	return (sim);
}

void	s_print(t_simulation *sim)
{
	printf("Simulation Settings:");

	if (sim == NULL)
	{
		printf(" NULL\n");
		return;
	}

	printf("\n - number_of_coders: %d", sim->number_of_coders);
	printf("\n - time_to_burnout: %d", sim->time_to_burnout);
	printf("\n - time_to_compile: %d", sim->time_to_compile);
	printf("\n - time_to_debug: %d", sim->time_to_debug);
	printf("\n - time_to_refactor: %d", sim->time_to_refactor);
	printf("\n - number_of_compiles_required: %d", sim->number_of_compiles_required);
	printf("\n - dongle_cooldown: %d", sim->dongle_cooldown);
	printf("\n - scheduler: %s\n", s_scheduler_name(sim->scheduler));
}

const char *s_scheduler_name(int scheduler)
{
	static const char *literals[] = {"FIFO", "EDF"};

	if (scheduler != S_FIFO && scheduler != S_EDF)
		return ("UKNOWN");
	return (literals[scheduler]);
}

void	s_print_usage(void)
{
	printf("Usage: codexion [CODERS] [TIME_TO_BURNOUT] ");
	printf("[TIME_TO_COMPILE] [TIME_TO_DEBUG] ");
	printf("[TIME_TO_REFACTOR] [COMPILES_REQUIRED] ");
	printf("[DONGLE_COOLDOWN] [SCHEDULER: fifo/edf]\n");
}
