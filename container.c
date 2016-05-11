#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "container.h"
#include "gallery.h"
#include "errorHandling.h"

item_t* copy(list_t *gallery){
    item_t *container = malloc(sizeof(item_t));
    if (!container){
        return NULL;
    }
    if (gallery->size > 0){
        container->array = malloc(((gallery->first->colums * gallery->first->rows) + 1)*sizeof(char));
        strcpy(container->array,gallery->first->array);
        container->rows = gallery->first->rows;
        container->colums = gallery->first->colums;
        container->linesAfter = 0;
        container->linesBefore = 0;
        container->next = container;
        container->prev = container;
    }
    return container;
}

item_t* cut(list_t **gallery){
    item_t *container = NULL;
    if ((*gallery)->size > 1){
        container = (*gallery)->first;
        container->array = (*gallery)->first->array;
        (*gallery)->first = container->next;
        (*gallery)->first->prev = container->prev;
        (*gallery)->first->prev->next = container->next;
        (*gallery)->size--;
        container->next = container;
        container->prev = container;
    }else{
        if ((*gallery)->size == 1){
            container = (*gallery)->first;
            container->array = (*gallery)->first->array;
            container->next = container;
            container->prev = container;
            (*gallery)->first = NULL;
            (*gallery)->size = 0;
        }
    }
    return container;
}

void paste(list_t **gallery, item_t *container){
    item_t *temp = malloc(sizeof(item_t));
    if (!temp){
        errorHandle(ERROR_NO_MEMORY);
        return;
    }
    temp->array = malloc(((container->colums * container->rows) + 1)*sizeof(char));
    strcpy(temp->array,container->array);
    temp->rows = container->rows;
    temp->colums = container->colums;
    temp->linesAfter = 0;
    temp->linesBefore = 0;
    temp->next = temp;
    temp->prev = temp;
    if((*gallery)->size > 0){
        temp->next = (*gallery)->first;
        temp->prev = (*gallery)->first->prev;
        (*gallery)->first->prev = temp;
        temp->prev->next = temp;
        (*gallery)->first = temp;
        (*gallery)->size++;
    }else{
        (*gallery)->first = temp;
        (*gallery)->size++;
    }
}
// TODO: container implementation
