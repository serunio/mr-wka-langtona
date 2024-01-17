//
// Created by jakub on 12/24/23.
//

#include <stdlib.h>
#include <stdio.h>
#include <time.h>-+

#include "plansza.h"


komorka** tworz(int x, int y, int p)
{
    komorka** grid = (komorka**)malloc((y)*sizeof(komorka*));
    for(int i = 0; i < y; i++)
        grid[i] = (komorka*)malloc((x)*sizeof(komorka));

    for(int i = 0; i < y; i++)
        for(int j = 0; j < x; j++)
        {
            grid[i][j].kolor = BIALY;
            grid[i][j].x = j;
            grid[i][j].y = i;
        }
    int black = x*y*p/100;
    int b = 0;
    komorka* k;
    srand(time(NULL));
    while(b<black)
    {
        if((k = &grid[rand()%y][rand()%x])->kolor == BIALY)
        {
            k->kolor = CZARNY;
            b++;
        }
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


void druk(komorka** p, int x, int y, mrowka m, FILE* f)
{
    for(int i = 0; i < y; i++)
    {
        for (int j = 0; j < x; j++)
        {
            switch(p[i][j].kolor)
            {
                case BIALY:
                    if(m.lokacja->x == j && m.lokacja->y == i)
                    {
                        fprintf(f, m.orientacja[0]==1 ? "▽" : m.orientacja[0]==-1 ? "△": m.orientacja[1]==1 ? "▷" : "◁");
                    }
                    else
                        fprintf(f, " ");
                    break;
                case CZARNY:
                    if(m.lokacja->x == j && m.lokacja->y == i)
                    {
                        fprintf(f, m.orientacja[0]==1 ? "▼" : m.orientacja[0]==-1 ? "▲": m.orientacja[1]==1 ? "▶" : "◀");
                    }
                    else
                        fprintf(f, "█");
                    break;

            }

        }
        fprintf(f, "\n");
    }

}
