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

typedef struct
{
    int x, y;
    int kolor;
}komorka;

typedef struct
{
    komorka* lokacja;
    int* orientacja;
}mrowka;

typedef struct
{
    komorka** plansza;
    mrowka* mrowki;
}calosc;


komorka** tworz(int x, int y, int procent);

calosc* zczytaj(FILE*);

void druk(komorka**, int, int, mrowka, FILE*);
#endif //MROWKA_LANGTONA_PLANSZA_H
