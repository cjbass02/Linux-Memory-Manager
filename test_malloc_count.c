/**
 * @file test_malloc_count.c
 *
 * @brief Tests the get_malloc_count() with a single thread.
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
 *      - Checks allocation count
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

    // No blocks allocated, should get count of 0
    printf("1 -- Expected Count: %i, Actual Count: %i\n", 0, get_mymalloc_count());

    // One blocks allocated, should get count of 1
    mymalloc_bf(10);
    printf("2 -- Expected Count: %i, Actual Count: %i\n", 1, get_mymalloc_count());

    // Two blocks allocated, should get count of 2
    mymalloc_bf(10);
    printf("3 -- Expected Count: %i, Actual Count: %i\n", 2, get_mymalloc_count());

    // Three blocks allocated, should get count of 3
    mymalloc_bf(10);
    printf("4 -- Expected Count: %i, Actual Count: %i\n", 3, get_mymalloc_count());

    // Four blocks allocated, should get count of 4
    mymalloc_bf(10);
    printf("5 -- Expected Count: %i, Actual Count: %i\n", 4, get_mymalloc_count());

    // Five blocks allocated, should get count of 5
    mymalloc_bf(10);
    printf("6 -- Expected Count: %i, Actual Count: %i\n", 5, get_mymalloc_count());

    // Six blocks allocated, should get count of 6
    mymalloc_bf(10);
    printf("7 -- Expected Count: %i, Actual Count: %i\n", 6, get_mymalloc_count());

    // Seven blocks allocated, should get count of 7
    mymalloc_bf(10);
    printf("8 -- Expected Count: %i, Actual Count: %i\n", 7, get_mymalloc_count());

    // Eight blocks allocated, should get count of 8
    mymalloc_bf(10);
    printf("9 -- Expected Count: %i, Actual Count: %i\n", 8, get_mymalloc_count());

    // Nine blocks allocated, should get count of 9
    mymalloc_bf(10);
    printf("10 -- Expected Count: %i, Actual Count: %i\n", 9, get_mymalloc_count());

    // Ten (MAX) blocks allocated, should get count of 10
    mymalloc_bf(10);
    printf("11 -- Expected Count: %i, Actual Count: %i\n", 10, get_mymalloc_count());

    // Free memory
    mm_destroy();

    return 0;
}
