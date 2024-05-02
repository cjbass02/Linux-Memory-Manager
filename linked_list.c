/**
 * @file linked_list.c
 *
 * @brief Implementation of linked list functions.
 *
 * Course: CSC3210
 * Section: 002
 * Assignment: Memory Manager
 * Name: Sabryn Bley & Christian Basso
 */

#include "linked_list.h"
#include "memory_manager.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * @brief Creates a new element for in the list.
 * @param data : The memory block.
 * @return temp : The element to add
 */
struct element* new_element(struct memory_block* data) {
    struct element* temp = malloc(sizeof(struct element));
    temp->data = data;
    temp->next = NULL;
    return temp;
}

/**
 * @brief Creates a new linked list.
 * @return list : The linked list
 */
struct linked_list* create_linked_list() {
    struct linked_list* list = malloc(sizeof(struct linked_list));
    list->head = NULL;
    return list;
}

/**
 * @brief Adds a element to the front of the list.
 * @param list : The list to add to
 * @param data : The memory block to add to the list
 */
void add_to_front(struct linked_list* list, struct memory_block* data) {
    // CREATE NEW ELEMENT
    struct element* new = new_element(data);

    
    // STORE OLD HEAD
    struct element* old = list->head;
    
    // REORDER
    new->next = old;
    
    // ADD TO FRONT
    list->head = new;
    
}

/**
 * @brief Adds a element to the end of the list.
 * @param list : The list to add to
 * @param data : The memory block to add to the list
 */
void add_to_end(struct linked_list* list, struct memory_block* data) {
    // CREATE NEW ELEMENT
    struct element* new = new_element(data);

    // ADD TO LIST
    if (is_empty(list)) {
        list->head = new;

    } else {
        // GET FIRST ELEMENT
        struct element *temp = list->head;

        // GET TO END
        while (temp->next != NULL) {
            temp = temp->next;
        }

        // ASSIGN TO END
        temp->next = new;
    }
}

/**
 * @brief Adds a element to the list at a given index.
 * @param list : The list to add to
 * @param index : The index to insert
 * @param data : The memory block to add to the list
 */
void add_at_index(struct linked_list* list, int index, struct memory_block* data) {
    // CREATE NEW ELEMENT
    struct element* new = new_element(data);

    // ADD TO LIST
    if (is_empty(list)) {
        list->head = new;

    } else {
        // GET FIRST ELEMENT
        struct element *temp = list->head;
        // GET TO INDEX
        int i = 0;

        // if the index is 0
        if(index == 0) {
            new->next = temp;
            list->head = new;
            return;
        }

        while (i != index - 1) {
            printf("got here\n");
            temp = temp->next;
            i++;
        }
        
        // SAVE OLD
        new->next = temp->next;

        // ASSIGN
        temp->next = new;
    }
}

/**
 * @brief Removes a element from the list at a given index.
 * @param list : The list to remove from
 * @param index : The index to remove
 */
void remove_element(struct linked_list* list, int index) {
    if (list == NULL) {
        printf("ERROR: Null list provided.\n");
        return;
    }
    if (is_empty(list)) {
        printf("ERROR: List is empty.\n");
        return;
    }
    if (index < 0 || index >= get_length(list)) {
        printf("ERROR: Index out of bounds.\n");
        return;
    }

    struct element** indirect = &list->head;
    struct element* current = list->head;
    for (int i = 0; i < index && current != NULL; i++) {
        indirect = &current->next;
        current = current->next;
    }

    if (current == NULL) {
        printf("ERROR: Index out of range.\n");
        return;
    }

    *indirect = current->next;
    if (current->data) {
        free(current->data);
    }
    free(current);
}


/**
 * @brief Checks if there are elements in the list.
 * @param list : The list to check
 * @return : 0 if the list has elements, 1 otherwise
 */
int is_empty(struct linked_list* list) {
    return list->head == NULL;
}

/**
 * @brief Displays the contents of a list.
 * TODO
 * @param list : The list to display
 */
void display(struct linked_list* list) {
    struct element* temp = list->head;
    printf("List: ");
    while (temp != NULL) {
        printf("(START: %p, SIZE: %d) --> ", temp->data->starting_address, temp->data->size);
        temp = temp->next;
    }
    printf("NULL\n");
}


/**
 * @brief Gets the number of elements in a list.
 * @param list : The list
 * @return length: The number of elements
 */
int get_length(struct linked_list* list) {
    int length = 0;
    struct element* temp = list->head;

    while (temp != NULL) {
        length++;
        temp = temp->next;
    }

    return length;
}

/**
 * @brief Frees the memory allocations for the list.
 * @param list : The list to free
 */
void free_list(struct linked_list* list){
    struct element* temp = list->head;
    struct element* next;

    while (temp != NULL) {
        next = temp->next;
        free(temp->data);
        free(temp);
        temp = next;
    }

    free(list);
}
