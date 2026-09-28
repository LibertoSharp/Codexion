/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   worker_cycle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luca <luca@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 00:00:00 by luca              #+#    #+#             */
/*   Updated: 2026/09/28 13:58:11 by luca             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "worker.h"
#include "simulation.h"
#include "utils/timeutils.h"
#include "utils/worker_utils.h"

int	worker_cycle(t_coder *coder)
{
	if (!queue_dongle(coder, coder->dongles[0]))
		return (0);
	if (!queue_dongle(coder, coder->dongles[1]))
		return (0);
	pthread_mutex_lock(&coder->mutex);
	coder->last_compilation = get_rounded_time(coder->sim) + 5;
	pthread_mutex_unlock(&coder->mutex);
	print_status(coder, "is compiling");
	precise_sleep(coder->sim->settings->time_to_compile, coder->sim);
	release_dongle(coder, coder->dongles[0]);
	release_dongle(coder, coder->dongles[1]);
	print_status(coder, "is debugging");
	precise_sleep(coder->sim->settings->time_to_debug, coder->sim);
	print_status(coder, "is refactoring");
	precise_sleep(coder->sim->settings->time_to_refactor, coder->sim);
	pthread_mutex_lock(&coder->mutex);
	coder->compilation_count++;
	pthread_mutex_unlock(&coder->mutex);
	return (1);
}
