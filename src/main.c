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
    int x, y, t;
    char* name;
    char a;
    int fflag=0;
    int option;
    while((option = getopt(argc, argv, "m:n:i:f:"))!=-1)
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
            case '?':
                printf("Nieznany argument: -%c\n", optopt);
                break;
            case ':':
                printf("Spsob wywolania: ./mrowka -m <wymiar x> -n <wymiar y> -i <ilosc stanow> -f <nazwa pliku wynikowego>\n");
                return 1;
                break;
            default:
                break;
        }
    }

    komorka** plansza = tworz(x, y);
    mrowka m;
    m.orientacja = (int*)malloc(2*sizeof(int));
    m.orientacja[0] = -1;
    m.orientacja[1] = 0;
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
