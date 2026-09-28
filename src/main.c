/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luca <luca@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 13:01:58 by luca              #+#    #+#             */
/*   Updated: 2026/09/28 13:58:47 by luca             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <stdio.h>
#include "simulation.h"

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
