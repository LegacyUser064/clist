#include <stdlib.h>
#include <stddef.h>
#include "list.h"

list_node_t* list_node_new(void* data)
{
        list_node_t* new_node = malloc(sizeof(list_node_t));
        if (new_node == NULL) return NULL;
        
        new_node->data = data;
        new_node->next = NULL;

        return new_node;
}

list_t* list_new(void)
{
        list_t* new_list = malloc(sizeof(list_t));
        if (new_list == NULL) return NULL;

        new_list->head = NULL;
        new_list->tail = new_list->head;
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
                list->tail = list->head;
                node->next = list->tail;
        } else {
                list->tail->next = node;
                list->tail = node;
                node->next = list->head;
        }

        list->length++;
}
