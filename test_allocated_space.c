/**
 * @file test_allocated_space.c
 *
 * @brief Tests the get_allocated_space() with a single thread.
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
 *      - Checks allocated space
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

    // No blocks allocated, should get space of 0
    printf("1 -- Expected Space: %i, Actual Space: %i\n", 0, get_allocated_space());

    // One blocks allocated, should get space of 10
    mymalloc_bf(10);
    printf("2 -- Expected Space: %i, Actual Space: %i\n", 10, get_allocated_space());

    // Two blocks allocated, should get space of 20
    mymalloc_bf(10);
    printf("3 -- Expected Space: %i, Actual Space: %i\n", 20, get_allocated_space());

    // Three blocks allocated, should get space of 30
    mymalloc_bf(10);
    printf("4 -- Expected Space: %i, Actual Space: %i\n", 30, get_allocated_space());

    // Four blocks allocated, should get space of 40
    mymalloc_bf(10);
    printf("5 -- Expected Space: %i, Actual Space: %i\n", 40, get_allocated_space());

    // Five blocks allocated, should get space of 50
    mymalloc_bf(10);
    printf("6 -- Expected Space: %i, Actual Space: %i\n", 50, get_allocated_space());

    // Six blocks allocated, should get space of 60
    mymalloc_bf(10);
    printf("7 -- Expected Space: %i, Actual Space: %i\n", 60, get_allocated_space());

    // Seven blocks allocated, should get space of 70
    mymalloc_bf(10);
    printf("8 -- Expected Space: %i, Actual Space: %i\n", 70, get_allocated_space());

    // Eight blocks allocated, should get space of 80
    mymalloc_bf(10);
    printf("9 -- Expected Space: %i, Actual Space: %i\n", 80, get_allocated_space());

    // Nine blocks allocated, should get count of 90
    mymalloc_bf(10);
    printf("10 -- Expected Count: %i, Actual Count: %i\n", 90, get_allocated_space());

    // Ten (MAX) blocks allocated, should get space of 100
    mymalloc_bf(10);
    printf("11 -- Expected Space: %i, Actual Space: %i\n", 100, get_allocated_space());

    // Free memory
    mm_destroy();

    return 0;
}
