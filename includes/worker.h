/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   worker.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luca <luca@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 13:27:37 by luca              #+#    #+#             */
/*   Updated: 2026/09/28 13:27:37 by luca             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WORKER_H
# define WORKER_H

void	*worker(void *arg);
void	print_status(t_coder *coder, const char *status);

#endif