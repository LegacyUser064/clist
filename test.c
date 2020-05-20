#include <stdio.h>
#include "list.h"

int main(void) 
{
        list_t* new_list = list_new();

        double data[] = {5, 6, 7, 8};
                
        list_append(new_list, list_node_new(&data[0]));
        list_append(new_list, list_node_new(&data[1]));
        list_append(new_list, list_node_new(&data[2]));

        list_destroy(new_list);
        
        return 0;
}
