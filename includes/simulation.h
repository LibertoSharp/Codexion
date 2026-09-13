#ifndef SIMULATION_H
# define SIMULATION_H

# define S_FIFO 0
# define S_EDF 1

typedef struct s_simulation
{
	int	number_of_coders;
	int	time_to_burnout;
	int	time_to_compile;
	int	time_to_debug;
	int	time_to_refactor;
	int	number_of_compiles_required;
	int	dongle_cooldown;
	int	scheduler;
}	t_simulation;

#endif