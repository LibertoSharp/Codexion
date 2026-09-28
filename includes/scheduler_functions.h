/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scheduler_functions.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luca <luca@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 13:29:05 by luca              #+#    #+#             */
/*   Updated: 2026/09/28 13:29:09 by luca             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCHEDULER_FUNCTIONS_H
# define SCHEDULER_FUNCTIONS_H

# include "simulation.h"

int		fifo(void *e1, void *e2);
int		edf(void *e1, void *e2);
void	set_scheduler_function(t_settings *settings, t_dongle *dongle);

#endif