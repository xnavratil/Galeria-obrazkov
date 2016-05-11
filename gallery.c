#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "container.h"
#include "picture.h"
#include "gallery.h"
#include "errorHandling.h"

// TODO: gallery implementation


list_t* inicializeGallery(){
     list_t *gallery = malloc(sizeof(list_t));
     if (!gallery){
         return NULL;
     }
     gallery->first = NULL;
     gallery->size = 0;
     return gallery;
}

void insertGallery(char *array, size_t rows, size_t colums, list_t *gallery){
    item_t *newItem = malloc(sizeof(item_t));
    newItem->array = array;
    newItem->next = newItem;
    newItem->prev = newItem;
    newItem->rows = rows;
    newItem->colums = colums;
    newItem->linesBefore = 0;
    newItem->linesAfter = 0;
    if (gallery->first == NULL){
        gallery->first = newItem;
    }else{
        newItem->next = gallery->first;
        newItem->prev = gallery->first->prev;
        gallery->first->prev->next = newItem;
        gallery->first->prev = newItem;
        gallery->first = newItem;
    }
    gallery->size++;
}

void freeGallery(list_t *gallery){
    item_t *temp = gallery->first;
    while(gallery->first != gallery->first->next){
        gallery->first = gallery->first->next;
        temp->prev->next = gallery->first;
        gallery->first->prev = temp->prev;
        free(temp->array);
        free(temp);
        temp = gallery->first;
    }
    free(temp->array);
    free(temp);
    free(gallery);
}

void printGallery(list_t *gallery, int rotation){
    size_t maxRows = 0;

    if (gallery->size == 1){
        for(size_t i = 0; i < gallery->first->rows; i++){
            for(size_t j = 0; j < gallery->first->colums; j++){
                printf("%c",gallery->first->array[i*gallery->first->colums + j]);
            }
            printf("\n");
        }
    }
    if (gallery->size == 2){
        item_t *first = gallery->first;
        item_t *second = gallery->first->prev;
        if (rotation != 0){
            first = first->next;
            second = first->next;
            gallery->first = first;
        }

   /*     if(first->rows == second->rows){
            for(size_t i = 0; i < first->rows; i++){
                for(size_t j = 0; j < first->colums; j++){
                    printf("%c",first->array[i*first->colums + j]);
                }
                printf(" | ");
                for(size_t j = 0; j < second->colums; j++){
                    printf("%c",second->array[i*second->colums + j]);
                }
                printf("\n");
            }
        }*/
       // if(first->rows != second->rows){
            if (first->rows > second->rows){
                second->linesBefore = first->rows - second->rows;
                maxRows = first->rows;
                if(second->linesBefore%2 == 0){
                    second->linesBefore /= 2;
                    second->linesAfter = second->linesBefore;
                }else{
                    second->linesAfter = second->linesBefore/2;
                    second->linesBefore = second->linesAfter + 1;
                }
            }else{
                first->linesBefore = second->rows - first->rows;
                maxRows = second->rows;
                if(first->linesBefore%2 == 0){
                    first->linesBefore /= 2;
                    first->linesAfter = first->linesBefore;
                }else{
                    first->linesAfter = first->linesBefore/2;
                    first->linesBefore = first->linesAfter + 1;
                }
        }
        for(size_t i = 0; i < maxRows; i++){
            if(((first->linesBefore != 0)&&(first->linesBefore > i))||((first->linesAfter != 0)&&((first->linesBefore + first->rows - 1) < i ))){
                for(size_t j = 0; j < first->colums; j++){
                    printf(" ");
                }
            }else{
                for(size_t j = 0; j < first->colums; j++){
                    printf("%c",first->array[(i-first->linesBefore)*first->colums + j]);
                }
            }
            printf(" | ");
            if(((second->linesBefore != 0)&&(second->linesBefore > i))||((second->linesAfter != 0)&&(( second->linesBefore + second->rows - 1) < i))){
                for(size_t j = 0; j < second->colums; j++){
                    printf(" ");
                }
            }else{
                for(size_t j = 0; j < second->colums; j++){
                    printf("%c",second->array[(i-second->linesBefore)*second->colums + j]);
                }
            }
            printf("\n");
        }
    //    }
        first->linesAfter = 0;
        first->linesBefore = 0;
        second->linesAfter = 0;
        second->linesBefore = 0;
    }


    if (gallery->size >= 3){
        item_t *first = gallery->first->prev;
        item_t *second = gallery->first;
        item_t *third = gallery->first->next;
        switch(rotation){
            case -1:
                first = first->next;
                second = second->next;
                third = third->next;
                gallery->first = second;
                break;
            case 1:
                first = first->prev;
                second = second->prev;
                third = third->prev;
                gallery->first = second;
                break;
            case 0:
                break;
        }
      /*  if ((first->rows == second->rows) && (first->rows == third->rows)){
            for(size_t i = 0; i < first->rows; i++){
                for(size_t j = 0; j < first->colums; j++){
                    printf("%c",first->array[i*first->colums + j]);
                }
                printf(" | ");
                for(size_t j = 0; j < second->colums; j++){
                    printf("%c",second->array[i*second->colums + j]);
                }
                printf(" | ");
                for(size_t j = 0; j < third->colums; j++){
                    printf("%c",third->array[i*third->colums + j]);
                }
                printf("\n");
            }
        }else{*/
            if(first->rows > second->rows){
                maxRows = first->rows;
            }else{
                maxRows = second->rows;
            }if(maxRows < third->rows){
                maxRows = third->rows;
            }
            first->linesAfter = maxRows - first->rows;
            if(first->linesAfter % 2 == 0){
                first->linesAfter /= 2;
                first->linesBefore = first->linesAfter;
            }else{
                first->linesAfter /= 2;
                first->linesBefore = first->linesAfter + 1;
            }

            second->linesAfter = maxRows - second->rows;
            if(second->linesAfter % 2 == 0){
                second->linesAfter /= 2;
                second->linesBefore = second->linesAfter;
            }else{
                second->linesAfter /= 2;
                second->linesBefore = second->linesAfter + 1;
            }

            third->linesAfter = maxRows - third->rows;
            if(third->linesAfter % 2 == 0){
                third->linesAfter /= 2;
                third->linesBefore = third->linesAfter;
            }else{
                third->linesAfter /= 2;
                third->linesBefore = third->linesAfter + 1;
            }

            for(size_t i = 0; i < maxRows; i++){
                if(((first->linesBefore != 0)&&(first->linesBefore > i))||((first->linesAfter != 0)&&((first->linesBefore + first->rows - 1) < i))){
                    for(size_t j = 0; j < first->colums; j++){
                        printf(" ");
                    }
                }else{
                    for(size_t j = 0; j < first->colums; j++){
                        printf("%c",first->array[(i-first->linesBefore)*first->colums + j]);
                    }
                }
                printf(" | ");
                if(((second->linesBefore != 0)&&(second->linesBefore > i))||((second->linesAfter != 0)&&((second->linesBefore + second->rows - 1) < i))){
                    for(size_t j = 0; j < second->colums; j++){
                        printf(" ");
                    }
                }else{
                    for(size_t j = 0; j < second->colums; j++){
                        printf("%c",second->array[(i-second->linesBefore)*second->colums + j]);
                    }
                }
                printf(" | ");
                if(((third->linesBefore != 0)&&(third->linesBefore > i))||((third->linesAfter != 0)&&((third->linesBefore + third->rows - 1) < i))){
                    for(size_t j = 0; j < third->colums; j++){
                        printf(" ");
                    }
                }else{
                    for(size_t j = 0; j < third->colums; j++){
                        printf("%c",third->array[(i-third->linesBefore)*third->colums + j]);
                    }
                }
                printf("\n");
            }
      //  }
        first->linesAfter = 0;
        first->linesBefore = 0;
        second->linesAfter = 0;
        second->linesBefore = 0;
        third->linesAfter = 0;
        third->linesBefore = 0;
    }
}

void deleteItem(list_t **gallery){
    item_t *temp = (*gallery)->first;
    if (temp == (*gallery)->first->prev){
        free(temp->array);
        free(temp);
        (*gallery)->first = NULL;
        (*gallery)->size--;
    }else{
        item_t *before = (*gallery)->first->prev;
        item_t * after = (*gallery)->first->next;
        before->next = after;
        after->prev = before;
        (*gallery)->first = after;
        free(temp->array);
        free(temp);
        (*gallery)->size--;
    }
}
