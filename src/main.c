#include "parser.h"
#include <stdio.h>

int	main(int argc, char **argv)
{
	t_simulation	*sim;

	sim = s_parse(argc, argv);
	if (sim == NULL)
	{
		s_print_usage();
		return (0);
	}
	s_print(sim);
	return (0);
}
