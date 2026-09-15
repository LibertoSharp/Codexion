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

typedef struct s_dongle
{
	long			last_time_used;
	pthread_mutex_t	mutex;
} t_dongle;

typedef struct s_simulation
{
	long			start_time;
	t_settings		*settings;
	t_coder			*coders;
	t_dongle		*dongles;
	int				running;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	state_mutex;
}	t_simulation;

typedef struct s_coder
{
	t_simulation	*sim;
	int				c_id;
	pthread_t		t_id;
	int				compilation_count;
	long			last_compilation;
	pthread_mutex_t	mutex;
}	t_coder;

void	run(t_settings *settings);
int		is_running(t_simulation *sim);
#endif