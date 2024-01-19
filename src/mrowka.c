//
// Created by cheese on 19.01.2024.
//

#include "mrowka.h"

#include <stdlib.h>

void step(komorka** grid, mrowka* m, int x, int y)
{
    switch(m->lokacja->kolor)
    {
        case BIALY:
            zmiana(m, CZARNY, PRAWO);
            break;
        case CZARNY:
            zmiana(m, BIALY, LEWO);
            break;
    }
    if(m->orientacja == NULL) return;
    if(m->lokacja->y + m->orientacja[0] == y)
    {
        m->lokacja = &grid[0][m->lokacja->x];
    }
    else
    if(m->lokacja->y + m->orientacja[0] < 0)
    {
        m->lokacja = &grid[y][m->lokacja->x];
    }
    else
    if(m->lokacja->x + m->orientacja[1] == x)
    {
        m->lokacja = &grid[m->lokacja->y][0];
    }
    else
    if(m->lokacja->x + m->orientacja[1] < 0)
    {
        m->lokacja = &grid[m->lokacja->y][x];
    }
    else
        m->lokacja = &grid[m->lokacja->y + m->orientacja[0]][m->lokacja->x + m->orientacja[1]];
}

int* obrot(int* orientacja, int kierunek)
{
    int* nowa = (int*)malloc(2*sizeof(int));
    if(nowa==NULL) return NULL;
    if(kierunek == LEWO)
    {
        nowa[0] = orientacja[1] == 1 ? -1 : orientacja[1] == -1 ? 1 : 0;
        nowa[1] = orientacja[0] == 1 ? 1 : orientacja[0] == -1 ? -1 : 0;
    }
    else
    if(kierunek == PRAWO)
    {
        nowa[0] = orientacja[1] == 1 ? 1 : orientacja[1] == -1 ? -1 : 0;
        nowa[1] = orientacja[0] == 1 ? -1 : orientacja[0] == -1 ? 1 : 0;
    }
    return nowa;
}

void zmiana(mrowka* m, int kolor, int kierunek)
{
    m->lokacja->kolor = kolor;
    int* temp = m->orientacja;
    m->orientacja = obrot(m->orientacja, kierunek);
    free(temp);
}

