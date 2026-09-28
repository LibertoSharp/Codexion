/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   worker_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luca <luca@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 13:29:15 by luca              #+#    #+#             */
/*   Updated: 2026/09/28 13:29:40 by luca             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WORKER_UTILS_H
# define WORKER_UTILS_H
# include "simulation.h"

void		sleep_remaining_cooldown(t_dongle *d, long long cooldown);
void		print_status(t_coder *coder, const char *status);
long long	get_remaining_cooldown(t_dongle *dongle, long long cooldown);
void		precise_sleep(long long duration_ms, t_simulation *sim);

#endif
