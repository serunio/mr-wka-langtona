//
// Created by jakub on 12/24/23.
//

#include <stdlib.h>
#include <stdio.h>

#include "plansza.h"
#include "../tigr/tigr.h"

komorka** tworz(int x, int y)
{
    komorka** grid = (komorka**)malloc((y+1)*sizeof(komorka*));
    for(int i = 0; i <= y; i++)
        grid[i] = (komorka*)malloc((x+1)*sizeof(komorka));

    for(int i = 0; i <= y; i++)
        for(int j = 0; j <= x; j++)
        {
            grid[i][j].kolor = DEAFULT;
            grid[i][j].x = j;
            grid[i][j].y = i;
        }
    return grid;
}

void step(komorka** grid, mrowka* m, int x, int y)
{
    switch(m->lokacja->kolor)
    {
        case DEAFULT:
        case BIALY:
            zmiana(m, CZERWONY, PRAWO);
            break;
        case CZERWONY:
            zmiana(m, ZIELONY, PRAWO);
            break;
        case ZIELONY:
            zmiana(m, NIEBIESKI, LEWO);
            break;
        case NIEBIESKI:
            zmiana(m, CZARNY, PRAWO);
            break;
        case CZARNY:
            zmiana(m, BIALY, PRAWO);
            break;
    }

    if(m->lokacja->y + m->orientacja[0] > y)
    {
        m->lokacja = &grid[0][m->lokacja->x];
    }
    else
    if(m->lokacja->y + m->orientacja[0] < 0)
    {
        m->lokacja = &grid[y][m->lokacja->x];
    }
    else
    if(m->lokacja->x + m->orientacja[1] > x)
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
    m->orientacja = obrot(m->orientacja, kierunek);
}


void druk(komorka** p, int x, int y, Tigr* screen)
{
    TPixel kolor;

    for(int i = 0; i <= y; i++)
    {
        for (int j = 0; j <= x; j++)
        {
            switch(p[i][j].kolor)
            {
                case BIALY:
                    kolor = tigrRGB(255, 255, 255);
                    break;
                case CZARNY:
                    kolor = tigrRGB(0, 0, 0);
                    break;
                case CZERWONY:
                    kolor = tigrRGB(255, 0, 0);
                    break;
                case ZIELONY:
                    kolor = tigrRGB(0, 255, 0);
                    break;
                case NIEBIESKI:
                    kolor = tigrRGB(0, 0, 255);
                    break;
                default:
                    kolor = tigrRGB(148, 148, 148);
            }
            tigrFillRect(screen, j-1, i-1, 3, 3, kolor);
        }

    }
    tigrUpdate(screen);
}
