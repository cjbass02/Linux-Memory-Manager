/**
 * @file test_small_heap.c
 *
 * @brief (Single thread) This file tests smallest heap possible (1 byte)
 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "memory_manager.h"

#define MY_HEAP_SIZE 1

int main() {
    char my_heap[MY_HEAP_SIZE];
	mm_init(my_heap, MY_HEAP_SIZE);

    char* ptr1 = mymalloc_bf(1);
    if(ptr1 == NULL) {
        printf("1 byte can not be allocated\n");
    } else {
        printf("Allocated ptr1 with 1 byte = %p\n", ptr1);
    }

    myfree(ptr1);
    printf("freed ptr1\n");

    char* ptr2 = mymalloc_bf(2);
    if(ptr2 == NULL) {
        printf("2 byte can not be allocated\n");
    } else {
        printf("Allocated ptr2 with 2 byte = %p\n", ptr1);
    }

    return 0;

    
}