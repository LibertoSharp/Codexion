#include "parser.h"
#include <stdio.h>

int	main(int argc, char **argv)
{
	t_settings	*settings;

	settings = s_parse(argc, argv);
	if (settings == NULL)
	{
		s_print_usage();
		return (0);
	}
	run(settings);
	return (0);
}
