#ifndef GALLERY_H
#define GALLERY_H

#include <stdlib.h>


/**
 *  @file   gallery.h
 *  @author Peter Navrátil 445700
 */
/**
 * struktura ktora si pamata pointer na jednorozmerne pole charakterov (obrazok)
 * prev a next ukazuju na ostatne struktury v galerii
 * rows a colums si pamataju pocet riadkov a stplcov obrazku
 * linesBefore a linesAfter pouzivam ako pomocne premenne pri vypise kvoli zarovnaniu
 */
typedef struct item{
    char *array;
    struct item *next;
    struct item *prev;
    size_t rows;
    size_t colums;
    size_t linesBefore;
    size_t linesAfter;
}item_t;
/**
 * struktura ktoru pouzivam na galeriu, pamata si ukazatel na prvy prvok
 * pamata si aj velkost galerie kvoli vypisovaniu velkosti
 */

typedef struct list{
    item_t *first;
    size_t size;
}list_t;

/**
 * @brief insertGallery vytvori uzol a vlozi ho do galerie
 * @param array "obrazok" ktory vlozim do noveho uzlu
 * @param rows pocet riadkov ktory ulozim do noveho uzlu
 * @param colums pocet stlpcov ktore ulozim do noveho uzlu
 * @param gallery pointer na galeriu obrazkov do ktorej budem pridavat obrazok
 */
void insertGallery(char *array, size_t rows, size_t colums, list_t *gallery);
/**
 * @brief inicializeGallery v tejto funkcii mallocujem galeriu
 *  a nastavujem jej povodne hodnoty na 0/ NULL pre pokoj v dusi
 * @return vracia mi pointer na mallocovanu strukturu galerie
 */
list_t *inicializeGallery();
/**
 * @brief freeGallery pri zadani prikazu q uvolnim celu pamat galerie a ukoncim cyklus nacitavania prikazov
 * @param gallery galeria ktoru uvolnujem
 */
void freeGallery(list_t *gallery);
/**
 * @brief printGallery funkcia vypise obrazky v galerii
 * @param gallery galeria ktoru bude funkcia vypisovat
 * @param rotation parameter podla ktoreho posuniem pointre a znova vypisem (mam jednu funkciu na rotacie a vypis)
 */
void printGallery(list_t *gallery, int rotation);
/**
 * @brief deleteItem vymaze jeden prvok z galerie, ten na ktory ukazuje first
 * @param gallery galeria z ktorej sa bude mazat
 */
void deleteItem(list_t **gallery);

#endif // GALLERY_H
