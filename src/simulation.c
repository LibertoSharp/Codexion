/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luca <luca@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 13:34:35 by luca              #+#    #+#             */
/*   Updated: 2026/09/28 13:49:58 by luca             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simulation.h"
#include <stdio.h>

int	is_running(t_simulation *sim)
{
	int	ret;

	pthread_mutex_lock(&sim->state_mutex);
	ret = sim->running;
	pthread_mutex_unlock(&sim->state_mutex);
	return (ret);
}
