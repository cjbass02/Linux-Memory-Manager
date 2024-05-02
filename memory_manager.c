/**
 * @file memory_manager.c
 *
 * @brief Implementation of memory manager functions
 *
 * Course: CSC3210
 * Section: 002
 * Assignment: Memory Manager
 * Name: Sabryn Bley & Christian Basso
 */

#include "memory_manager.h"
#include "linked_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <signal.h>
#include <unistd.h>

/* 
 * Using static causes the compiler to
 * limit visibility of the variables to this file only
 * This can be used to simulate 'private' variables in c
 */
static int allocation_count = 0;
static int total_space;
static void* memory;
bool destroyed;

static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;  // Mutex for thread safety

struct linked_list* free_blocks;  // Linked list to store free memory blocks
struct linked_list* allocated_blocks;  // Linked list to store allocated memory blocks

/**
 * @brief Initialize the memory manager to "manage" the given location
 *        NOTE: Do NOT malloc space for the memory to manage
 *              The invoker of this function will provide the memory
 *              See the sample for how to use this function
 * @param start - the start of the memory to manage
 * @param size - the size of the memory to manage
 */ 
void mm_init(void* start, int size) {
    // try and get lock
    if (pthread_mutex_trylock(&mutex) != 0) {
        return;
    }

    destroyed = false;

	allocation_count = 0;
    memory = start;
    total_space = size;

	//initialize the linked list, make one big free block the size of the heap passed in
    free_blocks = create_linked_list();
    allocated_blocks = create_linked_list();
    struct memory_block* first_block = malloc(sizeof(struct memory_block));
    first_block->size = size;
    first_block->starting_address = start;
    first_block->is_allocated = false;

    //add the new big empty black to the free blocks list
    add_to_end(free_blocks, first_block);

    //unlock the mutex
    pthread_mutex_unlock(&mutex);
}

/**
 * @brief Cleans up any storage used by the memory manager
 *        After a call to mmDestroy:
 *            all allocated spaces become invalid
 *            future allocation attempts fail
 *            future frees result in segmentation faults
 *        NOTE: after a call to mmDestroy a call to mmInit
 *            reinitializes the memory manager to allow allocations
 *            and frees
 */
void mm_destroy() {
    // try and get lock
    if (pthread_mutex_trylock(&mutex) != 0) {
        return;
    }

    // mark this has been destroyed
    destroyed = true;

    //free all the blocks in the free blocks list
    free_list(free_blocks);
    //free all the blocks in the allocated blocks list
    free_list(allocated_blocks);

    //unlock the mutex
    pthread_mutex_unlock(&mutex);
}

/**
 * @brief Requests a block of memory be allocated using first fit placement algorithm
 *        The memory manager must be initialized (mm_init) for this call to succeed
 * @param nbytes - the number of bytes in the requested memory
 * @return a pointer to the start of the allocated space
 */
void* mymalloc_ff(int nbytes) {
    //Get the mutex lock
    if (pthread_mutex_trylock(&mutex) != 0) {
        return NULL;
    }

    // Check if the memory manager has been initialized
    if (destroyed) { // Not initialized
        printf("ERROR: Memory manager has not been initialized. Call mm_init before allocating memory.\n");

        //unlock the mutex
        pthread_mutex_unlock(&mutex);

        return NULL;
    } else {
        //get the head of the free blocks
        struct element* current_block = free_blocks->head;

        //iterate through the free blocks to find the first block that is big enough
        while (current_block != NULL) {
            if (current_block->data->size >= nbytes) {
                //exit loop
                break;
            }
            current_block = current_block->next;
        }

        //check if a block was found
        if (current_block == NULL) {
            printf("ERROR: No block of sufficient size found.\n");

            //unlock the mutex
            pthread_mutex_unlock(&mutex);

            return NULL; //no block found
        }

        // at this point, current_block contains a block that is big enough
        //create a new block to represent the allocated memory
        struct memory_block* new_block = malloc(sizeof(struct memory_block));
        new_block->size = nbytes;
        new_block->starting_address = current_block->data->starting_address;
        new_block->is_allocated = true;

        //add the new block to the allocated blocks list
        add_to_end(allocated_blocks, new_block);
        allocation_count++;

        // Adjust size of free block (remove space now taken by the new block)
        current_block->data->size = current_block->data->size - new_block->size;
        // Adjust the starting position to be shifted by the new block size
        current_block->data->starting_address = current_block->data->starting_address + new_block->size;

        //unlock the mutex
        pthread_mutex_unlock(&mutex);

        //return the pointer to the allocated space. A pointer is a number.
        return new_block->starting_address;
    }
}

/**
 * @brief Requests a block of memory be allocated using worst fit placement algorithm
 *        The memory manager must be initialized (mm_init) for this call to succeed
 * @param nbytes - the number of bytes in the requested memory
 * @return a pointer to the start of the allocated space
 */
void* mymalloc_wf(int nbytes) {
    //get lock
    if (pthread_mutex_trylock(&mutex) != 0) {
        return NULL;
    }

    // Check if the memory manager has been initialized
    if (destroyed) { // Not initialized
        printf("ERROR: Memory manager has not been initialized. Call mm_init before allocating memory.\n");

        // unlock the mutex
        pthread_mutex_unlock(&mutex);

        return NULL;
    } else {
        //get the head of the free blocks
        struct element* current_block = free_blocks->head;

        //keep track of the largest block 
        struct memory_block* largest_block = NULL;
        int largest_block_size = 0;

        //iterate through the free blocks to find the first block that is big enough
        while (current_block != NULL) {
            if (current_block->data->size >= nbytes && current_block->data->size > largest_block_size) {
                //update the largest block
                largest_block_size = current_block->data->size;
                largest_block = current_block->data;
            }
            current_block = current_block->next;
        }

        //check if a block was found
        if (largest_block == NULL) {
            printf("ERROR: No block of sufficient size found.\n");

            //unlock the mutex
            pthread_mutex_unlock(&mutex);

            return NULL; //no block found
        }

        //create a new block to represent the allocated memory
        struct memory_block* new_block = malloc(sizeof(struct memory_block));
        new_block->size = nbytes;
        new_block->starting_address = largest_block->starting_address;
        new_block->is_allocated = true;

        //add the new block to the allocated blocks list
        add_to_end(allocated_blocks, new_block);
        allocation_count++;

        // Adjust size of free block (remove space now taken by the new block)
        largest_block->size = largest_block->size - new_block->size;

        // Adjust the starting position to be shifted by the new block size
        largest_block->starting_address = largest_block->starting_address + new_block->size;

        // unlock the mutex
        pthread_mutex_unlock(&mutex);

        // return the pointer to the allocated space. A pointer is a number.
        return new_block->starting_address;
    }
}

/**
 * @brief Requests a block of memory be allocated using best fit placement algorithm
 *        The memory manager must be initialized (mm_init) for this call to succeed
 * @param nbytes - the number of bytes in the requested memory
 * @return a pointer to the start of the allocated space
 */
void* mymalloc_bf(int nbytes) {
    //get lock
    if (pthread_mutex_trylock(&mutex) != 0) {
        return NULL;
    }

    // Check if the memory manager has been initialized
    if (destroyed) { // Not initialized
        printf("ERROR: Memory manager has not been initialized. Call mm_init before allocating memory.\n");

        // unlock the mutex
        pthread_mutex_unlock(&mutex);

        return NULL;
    } else {
        //get the head of the free blocks
        struct element* current_block = free_blocks->head;

        //keep track of the smallest block 
        struct memory_block* smallest_block = NULL;
        int smallest_block_size = total_space + 1;

        //iterate through the free blocks to find the first block that is big enough
        while (current_block != NULL) {
            if (current_block->data->size >= nbytes && current_block->data->size < smallest_block_size) {
                //update the largest block
                smallest_block_size = current_block->data->size;
                smallest_block = current_block->data;
            }
            current_block = current_block->next;
        }

        //check if a block was found
        if (smallest_block == NULL) {
            printf("ERROR: No block of sufficient size found.\n"); // TODO this doesn't fit example output... need to remove?

            //unlock the mutex
            pthread_mutex_unlock(&mutex);

            return NULL; //no block found
        }

        //create a new block to represent the allocated memory
        struct memory_block* new_block = malloc(sizeof(struct memory_block));
        new_block->size = nbytes;
        new_block->starting_address = smallest_block->starting_address;
        new_block->is_allocated = true;

        //add the new block to the allocated blocks list
        add_to_end(allocated_blocks, new_block);
        allocation_count++;

        // Adjust size of free block (remove space now taken by the new block)
        smallest_block->size = smallest_block->size - new_block->size;
        // Adjust the starting position to be shifted by the new block size
        smallest_block->starting_address = smallest_block->starting_address + new_block->size;

        //unlock the mutex
        pthread_mutex_unlock(&mutex);

        //return the pointer to the allocated space. A pointer is a number.
        return new_block->starting_address;
    }
}

/**
 * @brief Requests a block of memory be freed and the storage made available for future allocations
 *        The memory manager must be initialized (mm_init) for this call to succeed
 * @param ptr - a pointer to the start of the space to be freed
 *        Signals a SIGSEGV if a free is not valid
 *            - memory manager is not initialized
 *            - memory manager has been destroyed
 *            - ptr is not allocated (e.g. double free)
 */
void myfree(void* ptr) {
    // get lock
    if (pthread_mutex_trylock(&mutex) != 0) {
        return;
    }


    // Check if the memory manager has been initialized
    if (destroyed) { // Not initialized / destroyed
        printf("ERROR: A memory manager does not exist. Call mm_init before allocating memory.\n");

        pid_t pid = getpid();
        if (kill(pid, 11) == -1) {
            printf("ERROR: Could not send SIGSEGV signal.");
        }
    } else {
        //index is used to remove the element from the allocated blocks list
        int index = 0;

        // Find the referenced allocation block
        struct element* current = allocated_blocks->head;
        while (current->data->starting_address != ptr && current != NULL) { // address is not correct, and not a null terminator
            current = current->next;
            index++;
        }

        // If block was not found, print error and send signal
        if (current == NULL) {
            printf("ERROR: Could not find block at %p.\n", ptr);

            pid_t pid = getpid();
            pthread_mutex_lock(&mutex);
            if (kill(pid, 11) == -1) {
                printf("ERROR: Could not send SIGSEGV signal.");
            }
        }

        // Block should be valid from here on out...

        //flags to keep track of elements neighboring blocks
        bool before = false;
        bool after = false;

        //see if there is a free block before this block
        // Iterate through all free blocks and see if the ending address is the same as this block's starting address
        struct element *itt = free_blocks->head;

        while(itt != NULL){
            int *ending_add = itt->data->starting_address + itt->data->size;
            if (ending_add == current->data->starting_address) {
                // block found
                // update flag
                before = true;
                break;
            }
            itt = itt->next;
        }

        //see if there are any free blocks after this block
        //Iterate through all free blocks and see if the starting address is the same as this block's ending address
        struct element *itt2 = free_blocks->head;
        int *currents_ending_add = current->data->starting_address + current->data->size;
        while(itt2 != NULL){
            if(currents_ending_add == itt2->data->starting_address){
                //update flag
                after = true;

                //block found
                break;
            }
            itt2 = itt2->next;
        } 

        //Big if-statement ahead...
        if (before && after) { //if there are free blocks before and after, merge them
            // adjust before block size
            // before = before + new space + after
            itt->data->size += current->data->size + itt2->data->size;
            
            // remove after block
            remove_element(free_blocks, index + 1);
        } else if (before) { //if there is a free block before, merge them
            // adjust block size
            // before = before + new space
            itt->data->size += current->data->size;

        } else if (after) { //if there is a free block after, merge them
            // adjust starting address
            // after = new space
            itt2->data->starting_address = current->data->starting_address;

            // adjust block size
            // after = after + new space
            itt2->data->size += current->data->size;

        } else { // no free block before or after
            
            // create new free block
            struct memory_block* new_free = malloc(sizeof(struct memory_block));
            new_free->starting_address = current->data->starting_address;
            new_free->size = current->data->size;

            // find index to store it
            int free_i = 0;
            struct element* iterator = free_blocks->head;
            
            while (iterator->data->starting_address + iterator->data->size < new_free->starting_address) { // ending address < starting address
                free_i++;
                iterator = iterator->next;
            }

            // add to free linked list
            if(index == 0) {
                add_to_front(free_blocks, new_free);
            } else {
                add_at_index(free_blocks, free_i, new_free);
            }
        }
        //drop old allocated block from allocated block list
        remove_element(allocated_blocks, index);
    }
    //unlock the mutex
    pthread_mutex_unlock(&mutex);
}

/**
 * @brief Retrieve the current amount of space allocated by the memory manager (in bytes)
 * @return the current number of allocated bytes
 */
int get_allocated_space() {
    // Iterate through all active allocation blocks, count size
    struct element * current = allocated_blocks->head;
    int total_space = 0;
    while (current != NULL) {
        total_space += current->data->size;
        current = current->next;
    }

	return total_space;
}

/**
 * @brief Retrieve the current amount of available space in the memory manager (in bytes)
 *        (e.g. sum of all free blocks)
 * @return the current number of free bytes
 */
int get_remaining_space() {
    // Iterate through all active free block, count size
    struct element * current = free_blocks->head;
    int total_space = 0;
    while (current != NULL) {
        total_space += current->data->size;
        current = current->next;
    }

    return total_space;
}

/**
 * @brief Retrieve the current amount of free blocks (i.e. the count of all the block, not the size)
 * @return the current number of free blocks
 */
int get_fragment_count() {
	return get_length(free_blocks);;
}

/**
 * @brief Retrieve the number of successful malloc calls (for all placement types)
 * @return the total number of successful mallocs
 */
int get_mymalloc_count() {
	return allocation_count;
}
