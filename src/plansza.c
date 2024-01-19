//
// Created by jakub on 12/24/23.
//

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <wchar.h>
#include <locale.h>

#include "plansza.h"


komorka** tworz(int x, int y, int p)
{
    komorka** grid = (komorka**)malloc((y)*sizeof(komorka*));
    if(grid == NULL) return NULL;
    for(int i = 0; i < y; i++)
    {
        grid[i] = (komorka*)malloc((x)*sizeof(komorka));
        if(grid[i] == NULL) return NULL;
    }


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
                        fprintf(f, "X"); //█
                    break;

            }

        }
        fprintf(f, "\n");
    }

}

calosc* zczyatj(FILE* f)
{
    int i=0,j=0;
    setlocale(LC_ALL, "C.UTF-8");
    wint_t c;
    int x=0, y=1;
    while((c=fgetwc(f))!=WEOF && (int)c != '\n')
            x++;
    y++;
    while((c=fgetwc(f))!=WEOF)
    {
        if((int)c != '\n')
            y++;
    }
    komorka** grid = malloc(y*sizeof(komorka*));
    for(int i = 0; i < y; i++)
        grid[i] = malloc(x*sizeof(komorka));
    rewind(f);
    mrowka m;
while((c=fgetwc(f))!=WEOF)
{

    wchar_t k = (wchar_t)c;
    if(wcscmp(L"█",k)==0)
    {
        grid[i][j].kolor = CZARNY;
    }
    else if(wcscmp(L" ",k)==0)
    {
        grid[i][j].kolor = BIALY;
    }//△▲▷▶▽▼◁◀
    else if(wsccmp(L"◀",k)==0)
    {
        grid[i][j].kolor = CZARNY;
        m.lokacja = &grid[i][j];
        m.orientacja = malloc(2*sizeof(int));
        m.orientacja[0] = 0;
        m.orientacja[1] = -1;
    }
    else if(wsccmp(L"◁",k)==0)
    {
        grid[i][j].kolor = BIALY;
        m.lokacja = &grid[i][j];
        m.orientacja = malloc(2*sizeof(int));
        m.orientacja[0] = 0;
        m.orientacja[1] = -1;
    }
    else if(wsccmp(L"▼",k)==0)
    {
        grid[i][j].kolor = CZARNY;
        m.lokacja = &grid[i][j];
        m.orientacja = malloc(2*sizeof(int));
        m.orientacja[0] = 1;
        m.orientacja[1] = 0;
    }
    else if(wsccmp(L"▽",k)==0)
    {
        grid[i][j].kolor = BIALY;
        m.lokacja = &grid[i][j];
        m.orientacja = malloc(2*sizeof(int));
        m.orientacja[0] = 1;
        m.orientacja[1] = 0;
    }
    else if(wsccmp(L"▶",k)==0)
    {
        grid[i][j].kolor = CZARNY;
        m.lokacja = &grid[i][j];
        m.orientacja = malloc(2*sizeof(int));
        m.orientacja[0] = 0;
        m.orientacja[1] = 1;
    }
    else if(wsccmp(L"▷",k)==0)
    {
        grid[i][j].kolor = BIALY;
        m.lokacja = &grid[i][j];
        m.orientacja = malloc(2*sizeof(int));
        m.orientacja[0] = 0;
        m.orientacja[1] = 1;
    }
    else if(wsccmp(L"▲",k)==0)
    {
        grid[i][j].kolor = CZARNY;
        m.lokacja = &grid[i][j];
        m.orientacja = malloc(2*sizeof(int));
        m.orientacja[0] = -1;
        m.orientacja[1] = 0;
    }
    else if(wsccmp(L"△",k)==0)
    {
        grid[i][j].kolor = BIALY;
        m.lokacja = &grid[i][j];
        m.orientacja = malloc(2*sizeof(int));
        m.orientacja[0] = -1;
        m.orientacja[1] = 0;
    }

    if(j==x)
    {
        i++;
        j=-1;
    }
    j++;
}
    calosc a = {grid, m};
    return calosc;
}