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

        list_print(new_list);
        
        list_destroy(new_list);
        
        return 0;
}
