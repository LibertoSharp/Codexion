#ifndef PARSER_H
# define PARSER_H

# include "simulation.h"

t_simulation	*s_parse(int argc, char **argv);
void			s_print(t_simulation *sim);
const char		*s_scheduler_name(int scheduler);
void			s_print_usage(void);

#endif