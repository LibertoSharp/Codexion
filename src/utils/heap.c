#include "utils/heap.h"
#include "utils/ft_utils.h"
#include <stdlib.h>
#include <string.h>

t_heap	*heap_allocate(int amount)
{
	t_heap	*heap;

	heap = (t_heap *)ft_calloc(1, sizeof(t_heap));
	heap->elements = (void **)ft_calloc(amount, sizeof(void *));
	heap->capacity = amount;
	heap->size = 0;
	return (heap);
}

static void	heap_order(t_heap *heap)
{
	int	i;

	i = 0;
	while (i < heap->size - 1)
	{
		if (heap->order_func(heap->elements[i],heap->elements[i + 1]))
			i++;
		else
		{
			i = 0;
			ft_swap(&heap->elements[i], &heap->elements[i + 1]);
		}
	}
}

int	heap_append(t_heap *heap, void *element)
{
	if (heap->size >= heap->capacity || heap->order_func == NULL || heap_contains(heap, element))
		return (-1);

	heap->elements[heap->size] = element;
	heap->size++;

	heap_order(heap);
	return (0);
}

int	heap_contains(t_heap *heap, void *element)
{
	int	i;

	i = 0;
	while (i < heap->size)
	{
		if (heap->elements[i] == element)
			return (1);
		i++;
	}
	return (0);
}

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

void *heap_peek(t_heap *heap)
{
	return heap->elements[0];
}
