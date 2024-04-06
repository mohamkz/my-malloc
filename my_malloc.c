#include "my_malloc.h"

void* global_base = NULL;

struct block_meta* find_free_block(struct block_meta** last, size_t size)
{
    struct block_meta* current = global_base;
    while (current && !current->size && current->size < size)
    {
	*last = current;
	current = current->next;
    }
    return current;
}

struct block_meta* request_space(struct block_meta* last, size_t size)
{
    struct block_meta* block = sbrk(0);
    void* request = sbrk(size + META_SIZE);
    if (request == (void*) -1)
	return NULL;
    if (last)
	last->next = block;
    block->size = size;
    block->next = NULL;
    block->free = 0;
    return block;
}

void* my_malloc(size_t size)
{
    struct block_meta* block = NULL;
    if (size <= 0)
	return NULL;

    if (!global_base)
    {
	block = request_space(NULL, size);
	if (!block)
	    return NULL;
	global_base = block;
    }
    else
    {
	struct block_meta* last = global_base;
	block = find_free_block(&last, size);
	if (!block)
	{
	    block = request_space(last, size);
	    if (!block)
		return NULL;
	}
	else
	    block->free = 0;
    }
    return (block + 1);
}

struct block_meta* get_block_ptr(void* ptr)
{
    return (struct block_meta*)ptr - 1;
}

void my_free(void* ptr)
{
    if (!ptr)
	return;

    struct block_meta* block_ptr = get_block_ptr(ptr);
    block_ptr->free = 1;
}

void* my_realloc(void* ptr, size_t size)
{
    if (!ptr)
	return my_malloc(size);

    struct block_meta* block_ptr = get_block_ptr(ptr);
    if (block_ptr->size >= size)
	return ptr;
    void* new_ptr = my_malloc(size);
    if (!new_ptr)
	return NULL;
    memcpy(new_ptr, ptr, block_ptr->size);
    my_free(ptr);
    return new_ptr;
}

void* my_calloc(size_t nmemb, size_t elsize)
{
    size_t size = nmemb * elsize;
    void* ptr = my_malloc(size);
    memset(ptr, 0, size);
    return ptr;
}
