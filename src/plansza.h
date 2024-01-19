//
// Created by jakub on 12/24/23.
//

#ifndef MROWKA_LANGTONA_PLANSZA_H
#define MROWKA_LANGTONA_PLANSZA_H

#define BIALY  1
#define CZARNY 2

#define PRAWO 0
#define LEWO 1

#include <stdio.h>
#include "mrowka.h"

typedef struct
{
    int x, y;
    int kolor;
}komorka;

komorka** tworz(int x, int y, int procent);

komorka** zczytaj(FILE*);

void druk(komorka**, int, int, mrowka, FILE*);
#endif //MROWKA_LANGTONA_PLANSZA_H
