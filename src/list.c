#include <stdlib.h>
#include <stddef.h>
#include <list.h>

list_node_t* list_node_new(void* data)
{
    list_node_t* new_node;
        
    new_node = malloc(sizeof(list_node_t));

    if (NULL != new_node)
    {
        new_node->data = data;
        new_node->next = NULL;
        new_node->previous =  NULL;
    }

    return new_node;
}

list_t* list_new(void)
{
    list_t* new_list;

    new_list = malloc(sizeof(list_t));

    if (NULL != new_list) {
        new_list->head = NULL;
        new_list->tail = NULL;
        new_list->length = 0;
    }

    return new_list;
}

void list_destroy(list_t* list)
{
    list_node_t* current_node;
    list_node_t* temp_node;

    current_node = list->head;
    temp_node = current_node;
                
    for (int i = 0; i < list->length; i++) {
        temp_node = current_node;
        current_node = current_node->next;

        free(temp_node);

        temp_node = NULL;
    }

    free(list);

    list = NULL;
}

static int list_find_length(list_t* list)
{
    list_node_t* current_node;
    int length;

    current_node = list->head;
    length = 0;

    if (NULL != list->head) {
        length = 1;
                
        while (current_node != list->tail) {
            current_node = current_node->next;
            length++;
        }
    }
        
    return length;
}

void list_append(list_t* list, list_node_t* node)
{
    //brad if (0 == list->length)
    if (list->length == 0) {
        list->head = node;
        list->tail = node;

        node->previous = list->tail;
        node->next = list->tail;
    } else {
        list->tail->next = node;

        node->previous = list->tail;
        node->next = list->head;
                                
        list->tail = node;
    }

    list->length++;
}

void list_delete(list_t* list, list_node_t* node)
{
    //brad if (1 == list->length)
    if (list->length == 1) {
        free(node);

        list->head = NULL;
        list->tail = NULL;
    } else if (node == list->tail) {
        list->tail = list->tail->previous;

        free(node);

        list->tail->next = list->head;
        list->head->previous = list->tail;
    } else if (node == list->head) {
        list->head = list->head->next;

        free(node);

        list->tail->next = list->head;
        list->head->previous = list->tail;
    } else {
        node->next->previous = node->previous;
        node->previous->next = node->next;

        free(node);
    }

    node = NULL;
        
    list->length--;
}

void list_insert_after(list_t* list, list_node_t* node, list_node_t* new_node)
{
    new_node->next = node->next;
    new_node->previous = node;

    node->next->previous = new_node;
    node->next = new_node;

    list->length++;
}

list_t* list_split_after(list_t* list, list_node_t* node)
{
    list_t* new_list;

    //brad Put on separate lines:
    // if (blahblah) {
    //     return NULL;
    // }
    if (node == list->tail || list->length == 1) return NULL;

    new_list = malloc(sizeof(list_t));
    //brad What if new_list is NULL?

    new_list->head = node->next;
    new_list->tail = list->tail;
        
    new_list->head->previous = new_list->tail;
    new_list->tail->next = new_list->head;

    list->tail = node;
    list->head->previous = node;
    node->next = list->head;

    list->length = list_find_length(list);
    new_list->length = list_find_length(new_list);

    return new_list;
}

list_node_t* list_find_index(list_t* list, int index)
{
    list_node_t* current_node;

    current_node = list->head;

    for (int i = 0; i != index && i < list->length; i++) {
        current_node = current_node->next;
    }

    return current_node;
}

