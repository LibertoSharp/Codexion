/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luca <luca@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 13:29:11 by luca              #+#    #+#             */
/*   Updated: 2026/09/28 13:29:12 by luca             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_UTILS_H
# define FT_UTILS_H

# include <stddef.h>
# define T_SIZE_MAX 18446744073709551615ULL

void	*ft_calloc(size_t nmemb, size_t size);
void	ft_swap(void **a, void **b);

#endif
