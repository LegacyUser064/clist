#ifndef LIST_H
#define LIST_H

typedef struct list_node {
    struct list_node* next;
    struct list_node* previous; 
    void* data;
} list_node_t;

/* struct list
 * - head: always points to first node in the list
 * - tail: always points to last node  in the list, and the
 *         list node pointed to points to the head node
 * - length: how many nodes are within the list
 */

//brad why do you have a separate tail? In a doubly linked list, tail
// is just head->previous.
typedef struct list {
    list_node_t* head;
    list_node_t* tail;
    int length;
} list_t;

/* list_node_new(void* data)
 *
 * Creates and initializes a new list node then returns it
 */
list_node_t* list_node_new(void* data);

/* list_t* list_new(void)
 *
 * Creates and initializes a new list then returns it
 */
list_t* list_new(void);

/* void list_destroy(list_t* list)
 *
 * Frees the given list and its members
 */
void list_destroy(list_t* list);

/* void list_append(list_t* list, list_node_t* node)
 *
 * Places given node at the end of the supplied list
 *
 * NOTE: List can be empty
 */
//brad suggest renaming to list_append_node()
void list_append(list_t* list, list_node_t* node);

/*  */
//brad suggest renaming to list_delete_node()
void list_delete(list_t* list, list_node_t* node);

/*  */
//brad suggest renaming to list_insert_node_after()
void list_insert_after(list_t* list, list_node_t* node, list_node_t* new_node);

/*  */
list_t* list_split_after(list_t* list, list_node_t* node);

/* list_node_t* list_find_index(list_t* list, int index)
 *
 * NOTE: If index is greater than (list.length - 1), then this function
 *       will return */
//brad What do you mean by "...then this function will return"?
list_node_t* list_find_index(list_t* list, int index);

#endif // LIST_H
