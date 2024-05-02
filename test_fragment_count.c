/**
 * @file test_fragment_count.c
 *
 * @brief Tests the get_fragment_count() with a single thread.
 *
 * Course: CSC3210
 * Section: 002
 * Assignment: Memory Manager
 * Name: Sabryn Bley & Christian Basso
 *
 * Algorithm:
 *  - Creates a memory manager object
 *  - Until out of room...
 *      - Allocates a block
 *      - Checks the fragment count
 */

#include <stdio.h>

#include "memory_manager.h"

#define MY_HEAP_SIZE 100

/**
 * @brief Program entry procedure - creates the memory manager and uses it
 * @return 0
 */
int main() {

    // Allocate heap space
    char my_heap[MY_HEAP_SIZE];
    mm_init(my_heap, MY_HEAP_SIZE);

    // No blocks allocated, should get count of 1
    printf("1 -- Expected Count: %i, Actual Count: %i\n", 1, get_fragment_count());

    // One blocks allocated, should get count of 1
    char* first_block = mymalloc_ff(10);
    printf("2 -- Expected Count: %i, Actual Count: %i\n", 1, get_fragment_count());

    // Two blocks allocated, should get count of 1
    char* second_block =  mymalloc_ff(10);
    printf("3 -- Expected Count: %i, Actual Count: %i\n", 1, get_fragment_count());

    // Free first allocated block, should get count of 2
    myfree(first_block);
    printf("4 -- Expected Count: %i, Actual Count: %i\n", 2, get_fragment_count());

    // Free second allocated block, should get count of 1
    myfree(second_block);
    printf("5 -- Expected Count: %i, Actual Count: %i\n", 1, get_fragment_count());

    // Free memory
    mm_destroy();

    return 0;
}
