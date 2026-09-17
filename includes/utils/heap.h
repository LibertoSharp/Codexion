#ifndef HEAP_H
# define HEAP_H

typedef struct s_heap
{
	int capacity;
	int size;
	void **elements;
	int (*order_func)(void *e1, void *e2);
}	t_heap;

t_heap	*heap_allocate(int amount);
int		heap_append(t_heap *heap, void *element);
int		heap_contains(t_heap *heap, void *element);
void	heap_remove(t_heap *heap, void *element);
void	heap_pop(t_heap *heap);
void	*heap_peek(t_heap *heap);
void	heap_free(t_heap *heap);

#endif