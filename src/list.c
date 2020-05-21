#include <stdlib.h> //brad
#include <stddef.h> // <-- good! always list "standard" headers before project headers
#include "list.h" // <-- but why "" around list.h? If your makefile is good, you should be able to put it in <>

list_node_t* list_node_new(void* data)
{
//brad always indent by 4 spaces. it's the right tradeoff between readability and line length
        list_node_t* new_node = malloc(sizeof(list_node_t));
//brad it hurts readability to have more than one statement per line.
// I suggest the following:
    /*
    //brad if you get into the habit of putting the constant first in an "==" expression,
    // you'll never mistakenly compile "if (new_node = NULL)". It's not an easy thing to debug,
    // because your mind wants to see "==" really badly resulting in reading the statement
    // incorrectly about 50,000 times before finally figuring it out.
    if (NULL == new_node) {
        return NULL;
    }
    */
        if (new_node == NULL) return NULL;
        //brad best practice is, if possible, only 1 return statement per function.
        // I'd suggest:
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
                //brad it's good practice to set something to NULL or 0 after you free it.
                // One of the hardest things to debug is a memory overwrite, and it's enormously
                // helpful if you know you set pointers to NULL when you freed them.
                free(temp_node);
                //brad
                // temp_node = NULL;
        }

        free(list);
        //brad
        // list = NULL;
}

//brad why do you walk the list when you have a length field?
static int list_length(list_t* list)
{
        list_node_t* current_node = list->head;
        //brad it'd be better to init length to 0. Then you can write:
        // if (NULL != list->head) {
        //     while (current_node != list->tail)
        //        etc. etc.
        // }
        int length = 1;

        if (list->head == NULL) return 0;

        while (current_node != list->tail) {
                current_node = current_node->next;
                length++;
        }

        return length;
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

        if (node == list->tail || list->length == 1) return NULL;

        new_list = malloc(sizeof(list_t));

        new_list->head = node->next;
        new_list->tail = list->tail;
        
        new_list->head->previous = new_list->tail;
        new_list->tail->next = new_list->head;

        list->tail = node;
        list->head->previous = node;
        node->next = list->head;

        list->length = list_length(list);
        new_list->length = list_length(new_list);

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

