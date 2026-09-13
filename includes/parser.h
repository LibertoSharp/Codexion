#ifndef PARSER_H
# define PARSER_H

# include "simulation.h"

t_settings	*s_parse(int argc, char **argv);
void			s_print(t_settings *settings);
const char		*s_scheduler_name(int scheduler);
void			s_print_usage(void);

#endif