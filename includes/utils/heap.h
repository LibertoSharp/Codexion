#ifndef HEAP_H
# define HEAP_H

typedef struct s_heap
{
	int capacity;
	int size;
	void **elements;
	int (*order_func)(void *e1, void *e2);
}	t_heap;

t_heap	*heap_allocate(int amount, int (*order_func)(void *e1, void *e2));
int		heap_append(t_heap *heap, void *element);
void	heap_free(t_heap *heap);

#endif