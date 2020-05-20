#include <stdio.h>
#include "list.h"

void list_print(list_t* list)
{
        list_node_t* current_node = list->head;

        for (int i = 0; i < list->length; i++) {
                printf("%d\n", *(int*) current_node->data);
                current_node = current_node->next;
        }
}

int main(void) 
{
        list_t* new_list = list_new();

        int a = 2;
        int b = 6;
        int c = 8;
                       
        list_append(new_list, list_node_new(&a));
        list_append(new_list, list_node_new(&b));
        list_append(new_list, list_node_new(&c));
        list_append(new_list, list_node_new(&b));
        list_append(new_list, list_node_new(&b));

        list_delete(new_list, new_list->tail);
        list_delete(new_list, new_list->head->next);
        list_delete(new_list, new_list->head);
        
        list_print(new_list);

        list_insert_after(new_list, new_list->head, list_node_new(&b));
        list_append(new_list, list_node_new(&a));

        list_print(new_list);
        
        list_destroy(new_list);
        
        return 0;
}
