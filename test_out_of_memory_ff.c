/**
 * @file test_out_of_memory_ff.c
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

    char* ptr1 = mymalloc_ff(20);
    printf("Allocated ptr1 = %p\n", ptr1);
    char* ptr2 = mymalloc_ff(20);
    printf("Allocated ptr2 = %p\n", ptr2);
    char* ptr3 = mymalloc_ff(20);
    printf("Allocated ptr3 = %p\n", ptr3);
    char* ptr4 = mymalloc_ff(20);
    printf("Allocated ptr4 = %p\n", ptr4);
    char* ptr5 = mymalloc_ff(20);
    printf("Allocated ptr5 = %p\n", ptr5);
    printf("Next malloc should not fit\n"); 
    //should fail
    char* ptr6 = mymalloc_ff(20);
    printf("ptr6 = %p\n", ptr6);
    
}