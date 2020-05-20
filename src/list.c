#include <stdlib.h>
#include <stddef.h>
#include "list.h"

list_node_t* list_node_new(void* data)
{
        list_node_t* new_node = malloc(sizeof(list_node_t));
        if (new_node == NULL) return NULL;
        
        new_node->data = data;
        new_node->next = NULL;
        new_node->previous =  NULL;

        return new_node;
}

list_t* list_new(void)
{
        list_t* new_list = malloc(sizeof(list_t));
        if (new_list == NULL) return NULL;

        new_list->head = NULL;
        new_list->tail = NULL;
        new_list->length = 0;

        return new_list;
}

void list_destroy(list_t* list)
{
        list_node_t* current_node = list->head;
        list_node_t* temp_node = NULL;
                
        for (int i = 0; i < list->length; i++) {
                temp_node = current_node;
                current_node = current_node->next;
                free(temp_node);
        }

        free(list);
}

void list_append(list_t* list, list_node_t* node)
{
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

        list->length--;
}
