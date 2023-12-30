//
// Created by jakub on 12/24/23.
//
#include "plansza.h"
#include "../tigr/tigr.h"

#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char** argv)
{
    int x = argc > 1 ? atoi(argv[1]) : 200;
    int y = argc > 2 ? atoi(argv[2]) : 200;
    int t = argc > 3 ? atoi(argv[3]) : 100000;
    int s = argc > 4 ? atoi(argv[4]) : 1;
    komorka** plansza = tworz(x, y);
    mrowka m;
    m.orientacja = (int*)malloc(2*sizeof(int));
    m.orientacja[0] = -1;
    m.orientacja[1] = 0;
    m.lokacja = &plansza[y/2][x/2];

    Tigr* screen = tigrWindow(x, y, "Mrowka", 0);
    TPixel tlo = tigrRGB(148, 148, 148);
    TPixel bialy = tigrRGB(255, 255, 255);
    TPixel czarny = tigrRGB(0, 0, 0);
    int k = 0;
    tigrClear(screen, tlo);
    while (!tigrClosed(screen) && !tigrKeyDown(screen, TK_ESCAPE))
    {
        if(k<=t)
            step(plansza, &m, x, y);
        if(k%s == 0)
        {
            for(int i = 0; i <= y; i++)
            {
                for (int j = 0; j <= x; j++)
                {
                    int kolor = plansza[i][j].kolor;
                    switch(kolor)
                    {
                        case BIALY:
                            tigrFillRect(screen, j-1, i-1, 3, 3, bialy);
                            break;
                        case CZARNY:
                            tigrFillRect(screen, j-1, i-1, 3, 3, czarny);
                            break;
                    }

                }

            }
            tigrUpdate(screen);
        }

        k++;
    }
    tigrFree(screen);

    return 0;
}
