//
// Created by jakub on 12/24/23.
//
#include "plansza.h"


#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>
#include <string.h>

int main(int argc, char** argv)
{
    int x = 50, y = 50, t = 100, p = 0;
    char* name;
    int* kierunek = (int*)calloc(2, sizeof(int));
    int fflag=0;
    int option;
    while((option = getopt(argc, argv, ":m:n:i:f:k:p:"))!=-1)
    {
        switch(option)
        {
            case 'm':
                x = atoi(optarg);
                break;
            case 'n':
                y = atoi(optarg);
                break;
            case 'i':
                t = atoi(optarg);
                break;
            case 'f':
                name = optarg;
                fflag++;
                break;
            case 'k':
                if(!strcmp(optarg, "gora"))
                    kierunek[0] = -1;
                else if(!strcmp(optarg, "dol"))
                    kierunek[0] = 1;
                else if(!strcmp(optarg, "lewo"))
                    kierunek[1] = -1;
                else if(!strcmp(optarg, "prawo"))
                    kierunek[1] = 1;
                else
                {printf("Podano zly kierunek\n"); return 1;}
                break;
            case 'p':
                p = atoi(optarg);
                if(p >= 0 && p <= 100)
                    break;
                else
                {
                    printf("Podano zla wartosc dla %c (prawidlowe: 0-100)\n", optopt);
                    return 1;
                }
            case '?':
                printf("Nieznany argument: -%c\n", optopt);
                break;
            case ':':
                printf("Opcje potrzebuja argumentow: \n-m <wymiar x> | -n <wymiar y> | -i <ilosc stanow> | -f <nazwa pliku wynikowego> | -k <kierunek mrowki(gora/dol/prawo/lewo)> | -p <procent poczatkowego zapelnienia planszy\n");
                return 1;
            default:
                break;
        }
    }

    komorka** plansza = tworz(x, y, p);
    mrowka m;
    m.orientacja = kierunek;
    m.lokacja = &plansza[y/2][x/2];

    char* filename = malloc(20*sizeof(char));
    int k = 0;
    FILE* file;
    while (k<=t)
    {
        if(fflag)
        {
            sprintf(filename, "../out/%s_%d.txt", name, k);
            file = fopen(filename, "w");
        }
        else
            file = stdout;
        if(file == NULL)
        {
            printf("%d\n", errno);
            return errno;
        }
        druk(plansza, x, y, m, file);
        if(fflag)
            fclose(file);
        step(plansza, &m, x, y);
        k++;
    }

    return 0;
}
