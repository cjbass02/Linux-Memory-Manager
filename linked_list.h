#ifndef LINKED_LIST_H
#define LINKED_LIST_H

/**
 * @brief Structure to be stored in a linked list.
 * @property data : The memory block.
 * @property next : The element after in the list.
 */
struct element {
    struct memory_block* data;
    struct element* next;
};

/**
 * @brief Structure to store data.
 * @property head : The first element.
 */
struct linked_list {
    struct element* head;
} ;

/**
 * @brief Creates a new element for in the list.
 * @param data : The memory block.
 * @return temp : The element to add
 */
struct element* new_element(struct memory_block* data);

/**
 * @brief Creates a new linked list.
 * @return list : The linked list
 */
struct linked_list* create_linked_list();

/**
 * @brief Adds a element to the front of the list.
 * @param list : The list to add to
 * @param data : The memory block to add to the list
 */
void add_to_front(struct linked_list* list, struct memory_block* data);

/**
 * @brief Adds a element to the end of the list.
 * @param list : The list to add to
 * @param data : The memory block to add to the list
 */
void add_to_end(struct linked_list* list, struct memory_block* data);

/**
 * @brief Adds a element to the list at a given index.
 * @param list : The list to add to
 * @param index : The index to insert
 * @param data : The memory block to add to the list
 */
void add_at_index(struct linked_list* list, int index, struct memory_block* data);

/**
 * @brief Removes a element from the list at a given index.
 * @param list : The list to remove from
 * @param index : The index to remove
 * @return data : The memory block removed
 */
void remove_element(struct linked_list* list, int index);

/**
 * @brief Checks if there are elements in the list.
 * @param list : The list to check
 * @return : 0 if the list has elements, 1 otherwise
 */
int is_empty(struct linked_list* list);

/**
 * @brief Displays the contents of a list.
 * @param list : The list to display
 */
void display(struct linked_list* list);

/**
 * @brief Gets the number of elements in a list.
 * @param list : The list
 * @return length: The number of elements
 */
int get_length(struct linked_list* list);

/**
 * @brief Frees the memory allocations for the list.
 * @param list : The list to free
 */
void free_list(struct linked_list* list);

#endif /* LINKED_LIST_H */
