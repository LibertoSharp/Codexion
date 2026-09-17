#include "heap.h"
#include "utils/ft_utils.h"
#include <stdlib.h>

t_heap *heap_allocate(int amount, int (*order_func)(void *e1, void *e2))
{
	t_heap *heap;

	heap = (t_heap *)ft_calloc(1, sizeof(t_heap));
	heap->elements = (void **)ft_calloc(amount, sizeof(void *));
	heap->order_func = order_func;
	heap->capacity = amount;
	heap->size = 0;
	return heap;
}

static void heap_order(t_heap *heap)
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

void heap_append(t_heap *heap, void *element)
{
	if (heap->size >= heap->capacity)
		return -1;

	heap->elements[heap->size] = element;
	heap->size++;

	heap_order(heap);
	return 0;
}

void heap_free(t_heap *heap)
{
	free(heap->elements);
	free(heap);
}
