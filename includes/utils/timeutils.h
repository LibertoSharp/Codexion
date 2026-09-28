/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timeutils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luca <luca@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 13:30:39 by luca              #+#    #+#             */
/*   Updated: 2026/09/28 13:32:15 by luca             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TIMEUTILS_H
# define TIMEUTILS_H

long long		get_time_ms(void);
struct timespec	ms_to_timespec(long long milliseconds);

#endif
