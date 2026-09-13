#ifndef SIMULATION_H
# define SIMULATION_H

#include <pthread.h>
# define S_FIFO 0
# define S_EDF 1

typedef struct s_settings
{
	int	number_of_coders;
	int	time_to_burnout;
	int	time_to_compile;
	int	time_to_debug;
	int	time_to_refactor;
	int	number_of_compiles_required;
	int	dongle_cooldown;
	int	scheduler;
}	t_settings;

typedef struct s_coder t_coder;

typedef struct s_simulation
{
	t_settings	*settings;
	t_coder		*coders;
	int			*dongles;
	int			running;
}	t_simulation;

typedef struct s_coder
{
	t_simulation	*sim;
	int c_id;
	pthread_t t_id;
}	t_coder;

void	run(t_settings *settings);
#endif