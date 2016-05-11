#ifndef PICTURE_H
#define PICTURE_H

#include <stdio.h>
#include "gallery.h"

/**
 *  @file   picture.h
 *  @author Peter Navrátil 445700
 */

/**
 * @brief loadPicture funkcia na nacitanie obrazku zo standartneho vstupu
 * @param rows pocet riadkov obrazku,
 *  ktory sa upravi v tejto funkcii podla nacitaneho vstupu a potom sa posle do funkcie insertGallery
 * @param colums pocet stlpcov obrazku,
 *  ktory sa upravi v tejto funkcii podla nacitaneho vstupu a potom sa posle do funkcie insertGallery
 * @return vrati pointer na novo vytvorene jednorozmerne pole ktore sa vrati do mainu a dalej spracovava
 */

char* loadPicture(size_t *rows, size_t *colums);

#endif // PICTURE_H
