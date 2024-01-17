//
// Created by jakub on 12/24/23.
//

#ifndef MROWKA_LANGTONA_PLANSZA_H
#define MROWKA_LANGTONA_PLANSZA_H

#define DEAFULT 0
#define BIALY  1
#define CZARNY 2
#define CZERWONY 3
#define ZIELONY 4
#define NIEBIESKI 5

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

komorka** tworz(int x, int y);

void step(komorka**, mrowka*, int, int);

int* obrot(int* orientacja, int kieunek);

void zmiana(mrowka* m, int kolor, int kierunek);

void druk(komorka**, int, int, mrowka, FILE*);
#endif //MROWKA_LANGTONA_PLANSZA_H
