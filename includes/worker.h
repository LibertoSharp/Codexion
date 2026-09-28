/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   worker.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luca <luca@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 13:27:37 by luca              #+#    #+#             */
/*   Updated: 2026/09/28 13:49:43 by luca             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WORKER_H
# define WORKER_H

# include "simulation.h"

void		*worker(void *arg);
void		print_status(t_coder *coder, const char *status);
long long	get_rounded_time(t_simulation *sim);
int			queue_dongle(t_coder *coder, t_dongle *dongle);
void		release_dongle(t_coder *coder, t_dongle *dongle);
int			worker_cycle(t_coder *coder);

#endif