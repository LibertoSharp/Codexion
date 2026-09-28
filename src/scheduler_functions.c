/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scheduler_functions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luca <luca@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 13:44:37 by luca              #+#    #+#             */
/*   Updated: 2026/09/28 13:45:11 by luca             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scheduler_functions.h"
#include "simulation.h"
#include "utils/timeutils.h"

int	fifo(void *e1, void *e2)
{
	t_coder	*left;
	t_coder	*right;

	left = (t_coder *)e1;
	right = (t_coder *)e2;

	if (left->arrival_time != right->arrival_time)
		return (left->arrival_time < right->arrival_time);
	return (left->c_id < right->c_id);
}

int	edf(void *e1, void *e2)
{
	t_coder	*left;
	t_coder	*right;

	left = (t_coder *)e1;
	right = (t_coder *)e2;

	if (left->last_compilation != right->last_compilation)
		return (left->last_compilation < right->last_compilation);
	if (left->compilation_count != right->compilation_count)
		return (left->compilation_count > right->compilation_count);
	return (left->c_id > right->c_id);
}

void	set_scheduler_function(t_settings *settings, t_dongle *dongle)
{
	if (settings->scheduler == S_FIFO)
		dongle->priority_queue->order_func = fifo;
	else if (settings->scheduler == S_EDF)
		dongle->priority_queue->order_func = edf;
}
