#include <stdio.h>
#include "list.h"

//brad Can this be declared static?
void list_print(list_t* list)
{
    list_node_t* current_node = list->head;

    printf("%s\n\n", "List Dump");

    for (int i = 0; i < list->length; i++) {
        printf("%d\n", *(int*) current_node->data);
        current_node = current_node->next;
    }

    //brad You can just do printf("\n");
    printf("%c", '\n');
}

int main(void) 
{
    list_t* list = list_new();
    //brad What if list is NULL?

    int a = 2;
    int b = 6;
    int c = 8;

    //brad What if list_node_new() returns NULL?
    list_append(list, list_node_new(&a));
    list_append(list, list_node_new(&b));
    list_append(list, list_node_new(&c));
    list_append(list, list_node_new(&b));
    list_append(list, list_node_new(&b));

    list_print(list);

    list_t* new_list = list_split_after(list, list_find_index(list, 2));

    list_delete(list, list->tail);

    list_print(list);
    list_print(new_list);

    list_destroy(list);
    list_destroy(new_list);
        
    return 0;
}
