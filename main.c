#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "container.h"
#include "picture.h"
#include "gallery.h"
#include "errorHandling.h"
/**
 * @brief menu funkcia vypise napovedu
 */
void menu(){
    puts("----  ZAKLADNI PRIKAZY");
    puts("n     nacte novy obrazek v editacnim rezimu");
    puts("d     smaze aktualni obrazek");
    puts("l r   rotece galerie vlevo nebo vpravo");
    puts("s     zjisti pocet obrazku v galerii");
    puts("q     ukonci program");
    puts("----  ROZSIRENE PRIKAZY");
    puts("c x   kopiruje nebo vystrihne obrazek do schranky");
    puts("v     vlozi obrazek ze schranky na aktualni pozici");
}

int main(int argc, char* argv[]){
    char *array = NULL;
    size_t rows = 0;
    size_t colums = 0;
    int command = 0;
    int next = 0;
    bool end = 1;
    item_t *container = NULL;
    list_t *gallery;
    gallery = inicializeGallery(); // prvotne vytvorene galerie
    if (gallery == NULL){
        errorHandle(ERROR_NO_MEMORY);
        return 0;
    }

    if (argc != 1){
        if (strcmp(argv[1],"-s")!=0){
            menu();
        }
    }else{
        menu();
    }

    while(end){  //celu dobu je nastaveny na 1 ale ked sa zavola 'q' tak sa end nastavi na 0 skonci cyklus a ukonci program
        printf(">");
        command = getchar();
        if (command == '\n'){ //ignorovanie prikazu '/n'
            continue;
        }
        next = getchar(); //nacitavam vzdy dva prikazy
        if (next != '\n'){ //ak je 2. prikaz rozny od noveho riadku tak je urcite zly vstup tak error
            errorHandle(ERROR_WRONG_CMD);
            while(1){ // cyklus na docitanie vstupu alebo teda vyprazdnenie
                next = getchar();
                if(next == '\n'){
                    break;
                }
            }
            continue;
        }
        switch(command){ //podla prveho nacitaneho znaku sa rozhodne co sa deje
            case 'n':
                array = loadPicture(&rows, &colums); //nacita sa obrazok
                if (array != NULL){
                    insertGallery(array, rows, colums,gallery); //vlozenie obrazku do galerie
                    array = NULL;
                }else{
                    if (rows != 0){
                        errorHandle(ERROR_WRONG_FORMAT); //ak sa nacita aspon jeden spravny riadok a potom sa nacita jeden zly tak je podmienka splnena a hodi error
                    }else{
                        continue;
                    }
                }
                if (gallery->size > 0){ //nebudem predsa vypisovat ak tam nic neni to plati v kazdom prikaze
                    printGallery(gallery,0);
                }
                break;
            case 'r':
                if (gallery->size > 0){
                    printGallery(gallery,1); //druhy parameter mi naznaci ze sa rotuje 1 je doprava -1 dolava a 0 je ze zostava na mieste
                }
                break;
            case 'l':
                if (gallery->size > 0){
                    printGallery(gallery,-1);
                }
                break;
            case 'd':
                if (gallery->size > 0){  //neda sa mazat z prazdnej
                    deleteItem(&gallery);
                }
                if (gallery->size > 0){
                    printGallery(gallery,0);
                }
                break;
            case 's':
                printf("size: %d\n",(int) gallery->size);
                break;
            case 'c':
                if (gallery->size == 0){ //neda sa nic nakopirovat ak nic nie je v galerii
                    continue;
                }
                if (container != NULL){
                    free(container->array);  // ak mam co nacitat a nieco uz v containeri je tak sa toho treba zbavit
                    free(container);
                }
                container = copy(gallery);
                if (container == NULL){
                    errorHandle(ERROR_NO_MEMORY);
                }
                break;
            case 'x':
                if ((container != NULL)&&(gallery->size > 0)){
                    free(container->array);
                    free(container);
                }
                if (gallery->size == 0){
                    continue;
                }
                container = cut(&gallery);
                if (container == NULL){
                    errorHandle(ERROR_NO_MEMORY);
                }
                if(gallery->size > 0){
                    printGallery(gallery,0);
                }
                break;
            case 'v':
                if (container != NULL){   // ak nie je prazdny tak spustim funkciu na pridanie noveho uzlu
                    if (container->rows != 0){
                        paste(&gallery, container);
                    }
                }
                if(gallery->size > 0){
                    printGallery(gallery,0);
                }
                break;
            case 'q':
                if (gallery->first != NULL){
                    freeGallery(gallery); // uvolni vsetky prvky po jedno
                }else{
                    free(gallery); // uvolni len pointer ak nikam neukazuje
                }
                if (container != NULL){ //ak nieco bolo v containeri tak to treba zmazat
                    free(container->array);
                    free(container);
                }
                end = 0; //podmienka na ukoncenie cyklu
                break;
            default:
                errorHandle(ERROR_WRONG_CMD);
                break;
        }
    }

    return 0;
}
