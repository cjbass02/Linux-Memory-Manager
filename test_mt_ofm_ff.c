/**
 * @file pthread_testmemmgr.c
 *
 * @brief (Multi-thread) Tests allocating until out of space with first fit.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#include "memory_manager.h"

#define MY_HEAP_SIZE 100
#define ALLOC_SIZE   10
#define THREAD_COUNT 3

/**
 * @brief Pthread routine allocates and frees memory
 * @param args - thread arguments - not used
 * @return NULL
 */
void* thread_routine(void* args) {

    // Loop 4 times and to allocate/
	for(int i = 0; i < 4; i++) {
		char* myptr = mymalloc_ff(ALLOC_SIZE);
		if(myptr != NULL) {
			printf("Thread %lu allocated %d byte(s): %p. Allocation count: %d\n", pthread_self(), ALLOC_SIZE, myptr, get_mymalloc_count());
		} else {
			printf("Thread %lu could not allocate %d byte(s)\n", pthread_self(), ALLOC_SIZE);
		}
	}

	return NULL;
}

/**
 * @brief Program entry procedure - initializes the memory manager and creates threads to request memory
 * @return 0
 */
int main() {

    // Store thread IDs for future join
	pthread_t mythreads[THREAD_COUNT];

    // Initialize the shared heap space
	char my_heap[MY_HEAP_SIZE];
	mm_init(my_heap, MY_HEAP_SIZE);

    // Create threads to use the space
	for(int i = 0; i < THREAD_COUNT; i++) {
		if(pthread_create(&mythreads[i], NULL, thread_routine, NULL) == -1) {
			printf("COULD NOT CREATE A THREAD\n");
			exit(EXIT_FAILURE);
		}
	}

    // Wait for threads to finish
	for(int i = 0; i < THREAD_COUNT; i++) {
		pthread_join(mythreads[i], NULL);
	}

    // Destroy the shared heap and return
	mm_destroy();
	
	return 0;
}
