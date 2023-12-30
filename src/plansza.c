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
            zmiana(m, CZARNY, PRAWO);
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
            zmiana(m, BIALY, LEWO);
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

void druk0(komorka** p, int x, int y)
{
    for(int i = 0; i <= y; i++)
    {
        for (int j = 0; j <= x; j++)
        {
            int kolor = p[i][j].kolor;
            switch(kolor)
            {
                case BIALY:
                    printf("\033[107m \033[0m");
                    break;
                case CZARNY:
                    printf("\033[40m \033[0m");
                    break;
                case ZIELONY:
                    printf("\033[102m \033[0m");
                    break;
                case NIEBIESKI:
                    printf("\033[104m \033[0m");
                    break;
                case CZERWONY:
                    printf("\033[101m \033[0m");
                    break;
                default:
                    printf(" ");
                    break;
            }
        }
        printf("\n");
    }
}

void druk(komorka** p, int x, int y, Tigr** screen)
{
    TPixel tlo = tigrRGB(148, 148, 148);
    TPixel bialy = tigrRGB(255, 255, 255);
    TPixel czarny = tigrRGB(0, 0, 0);

    for(int i = 0; i <= y; i++)
    {
        for (int j = 0; j <= x; j++)
        {
            int kolor = p[i][j].kolor;
            switch(kolor)
            {
                case BIALY:
                    tigrFillRect(*screen, i*5, j*5, 5, 5, bialy);
                    break;
                case CZARNY:
                    tigrFillRect(*screen, i*5, j*5, 5, 5, czarny);
                    break;
            }
        }

    }
}