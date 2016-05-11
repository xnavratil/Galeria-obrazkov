#ifndef CONTAINER_H
#define CONTAINER_H

/**
 *  @file   container.h
 *  @author Peter Navrátil 445700
 */

#include "gallery.h"
/**
 * @brief copy funkcia ktora zkopiruje (hlboka kopia) prvy prvok v gallery a ulozi do containera
 * @param gallery galeria obrazkov su v nej ulozene vsetky obrazky
 * @return vracia mi pointer na alokovanu pamat a ulozim ju do containeru v maine
 */
item_t *copy(list_t *gallery);
/**
 * @brief cut urobi plytku kopiu prveho obrazku v galerii a vymaze ostatne pointre na tento obrazok,
 * aby sa nestalo ze k nemu pristupim z ineho obrazku (prelinkujem ostatne co ostali v galerii)
 * @param gallery galeria obrazkov su v nej ulozene vsetky obrazky
 * @return vracia mi pointer na alokovanu pamat a ulozim ju do containeru v maine
 */
item_t *cut(list_t **gallery);
/**
 * @brief paste funkcia vytvori hlboku kopiu kontainera a vlozi ho na prve miesto do galerie a prelinkuje
 * @param gallery galeria obrazkov su v nej ulozene vsetky obrazky
 */
void paste(list_t **gallery, item_t *);
// TODO: container declarations

#endif // CONTAINER_H
