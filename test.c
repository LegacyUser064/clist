#include <stdio.h>
#include "list.h"

void list_print(list_t* list)
{
        list_node_t* current_node = list->head;

        printf("%s\n\n", "List Dump");

        for (int i = 0; i < list->length; i++) {
                printf("%d\n", *(int*) current_node->data);
                current_node = current_node->next;
        }

        printf("%c", '\n');
}

int main(void) 
{
        list_t* list = list_new();

        int a = 2;
        int b = 6;
        int c = 8;
                       
        list_append(list, list_node_new(&a));
        list_append(list, list_node_new(&b));
        list_append(list, list_node_new(&c));
        list_append(list, list_node_new(&b));
        list_append(list, list_node_new(&b));

        //list_print(list);

        list_insert_after(list, list->head, list_node_new(&b));
        list_append(list, list_node_new(&a));

        //list_print(list);

        list_t* new_list = list_split_after(list, list->head->next->next);

        list_print(list);

        list_print(new_list);
        
        list_destroy(list);
        
        return 0;
}
