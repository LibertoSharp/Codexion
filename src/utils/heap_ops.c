/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_ops.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luca <luca@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 00:00:00 by luca              #+#    #+#             */
/*   Updated: 2026/09/28 13:49:18 by luca             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils/heap.h"
#include <stdlib.h>
#include <string.h>

void	heap_remove(t_heap *heap, void *element)
{
	int	i;

	i = 0;
	while (i < heap->size && heap->elements[i] != element)
		i++;
	if (i == heap->size)
		return ;
	while (i < heap->size - 1)
	{
		heap->elements[i] = heap->elements[i + 1];
		i++;
	}
	heap->elements[heap->size - 1] = NULL;
	heap->size--;
}

void	heap_free(t_heap *heap)
{
	free(heap->elements);
	free(heap);
}

void	heap_clear(t_heap *heap)
{
	memset(heap->elements, 0, heap->size);
	heap->size = 0;
}

void	heap_pop(t_heap *heap)
{
	int	i;

	if (heap->size == 0)
		return ;
	i = 0;
	while (i < heap->size - 1)
	{
		heap->elements[i] = heap->elements[i + 1];
		i++;
	}
	heap->elements[heap->size - 1] = NULL;
	heap->size--;
}

void	*heap_peek(t_heap *heap)
{
	return (heap->elements[0]);
}
