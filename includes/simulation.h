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

t_simulation	*s_parse(int argc, char **argv);
void			s_print(t_simulation *sim);
const char		*s_scheduler_name(int scheduler);
void			s_print_usage(void);
#endif