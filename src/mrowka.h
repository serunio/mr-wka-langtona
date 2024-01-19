//
// Created by cheese on 19.01.2024.
//

#ifndef MR_WKA_LANGTONA_MROWKA_H
#define MR_WKA_LANGTONA_MROWKA_H

#include "plansza.h"

typedef struct
{
    komorka* lokacja;
    int* orientacja;
}mrowka;

void step(komorka**, mrowka*, int, int);

int* obrot(int* orientacja, int kieunek);

void zmiana(mrowka* m, int kolor, int kierunek);

#endif //MR_WKA_LANGTONA_MROWKA_H
