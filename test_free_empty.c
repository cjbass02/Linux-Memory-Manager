/**
 * @file test_free_empty.c
 *
 * @brief (Single thread) Allocating with first fit until there is no memory space left
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "memory_manager.h"

#define MY_HEAP_SIZE 100

int main() {
    char my_heap[MY_HEAP_SIZE];
	mm_init(my_heap, MY_HEAP_SIZE);

    char* ptr1 = mymalloc_bf(10);
    printf("Allocated ptr1 = %p\n", ptr1);
    myfree(ptr1);
    printf("Freed ptr1.\n");
    printf("Free Space: %d\n", get_remaining_space());
    printf("No blocks are allocated, trying to free ptr1 again should throw seg fault...\n");
    myfree(ptr1);



    
}