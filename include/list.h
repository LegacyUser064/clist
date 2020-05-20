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
 * - length: how many members are within the list
 */
typedef struct list {
        list_node_t* head;
        list_node_t* tail;
        int length;
} list_t;

/* list_node_new(void* data)
 * - data: data member of new list node
 *
 * Creates and initializes a new list node then returs it
 */
list_node_t* list_node_new(void* data);

/* list_t* list_new(void)
 *
 * Creates and initializes a new list then returns it
 */
list_t* list_new(void);

/* void list_destroy(list_t* list)
 * - list: list that is to be freed
 *
 * Frees the given list and its members
 */
void list_destroy(list_t* list);

/* void list_append(list_t* list, list_node_t* node)
 * - list: list to append to
 * - node: new node to append
 *
 * Places given node at the end of the supplied list
 *
 * NOTE: List can be empty
 */
void list_append(list_t* list, list_node_t* node);

/*  */
void list_delete(list_t* list, list_node_t* node);

/*  */
void list_insert_after(list_t* list, list_node_t* node, list_node_t* new_node);

#endif // LIST_H
