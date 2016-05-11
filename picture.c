#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "picture.h"
#include "gallery.h"
#include "errorHandling.h"


char* loadPicture(size_t * rows, size_t * colums){
    char *string;
    int letter = 0;
    size_t i = 0;
    (*colums) = 0;
    (*rows) = 1;
    unsigned int size = 1;
    bool end = 1;
    bool badInput = 0;

    string = malloc(size*sizeof(char));
    if (!string){
        errorHandle(0);
        return NULL;
    }

    while(1){
        letter = getchar();
        if (letter == '\n'){
            break;
        }
        if (i >= size){
            size = size << 1;
            string = realloc(string,sizeof(char)*size);
            if (!string){
                errorHandle(0);
                break;
            }
        }
        string[i] = letter;
        i++;

    }
    if (i == 0){
        free(string);
        (*rows) = 0;
        return NULL;
    }
    (*colums) = i;
    i = 0;

    while(1){
        letter = getchar();
        if(letter == '\n'){
            if (end == 1){
                if (badInput == 1){
                    free(string);
                    return NULL;
                }
                if ((*rows) * (*colums) >= size){
                    size++;
                    string = realloc(string,sizeof(char)*size);
                    if (!string){
                        errorHandle(ERROR_NO_MEMORY);
                        break;
                    }
                }
                else{
                    size = ((*rows) * (*colums)) + 1;
                    string = realloc(string,sizeof(char)*size);
                    if (!string){   // pouzit mozno docasnu premennu aby som neprisiel o pointer na tu pamat ked zlyha realloc
                        errorHandle(ERROR_NO_MEMORY);
                        break;
                    }
                }
                string[(*colums)*(*rows)]= '\0';
                return string;
            }else{
                end = 1;
                (*rows)++;
                if(i != (*colums)){
                    badInput = 1;
                }
                i = 0;
                continue;
            }
        }
        end = 0;
        if (((*rows) * (*colums) + i) >= size){
            size = size << 1;
            string = realloc(string,sizeof(char)*size);
            if (!string){
                errorHandle(ERROR_NO_MEMORY);
                break;
            }
        }
        string[(*colums) * (*rows)+i] = letter;
        i++;
    }
    return string;
}

// TODO: picture implementation
