# my-malloc

A custom implementation of the standard C library dynamic memory allocation functions. This project provides a basic memory allocator using the `sbrk` system call, managing memory blocks via a linked list. 

## Features

This library implements the following standard memory management functions:
* **`my_malloc(size_t size)`**: Allocates a block of memory of the specified size.
* **`my_free(void* ptr)`**: Frees a previously allocated block of memory, making it available for future allocations.
* **`my_realloc(void* ptr, size_t size)`**: Resizes a previously allocated memory block.
* **`my_calloc(size_t nmemb, size_t elsize)`**: Allocates memory for an array of elements, initializing the allocated memory to zero.

## Getting Started

### Prerequisites
* GCC (or compatible C compiler)
* Make

### Building the Project
This project uses a `Makefile` to compile the source code into a shared library (`libmy_malloc.so`). 

To build the library, simply run:
```bash
make
