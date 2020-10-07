#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <ctype.h>

#define true 1
#define false 0


int inputHandling(int opt, int *nrOfQ, int argc, char** argv, char** fileName, char** user)
{
    switch (opt)
    {
    case 'o': //przelacznik -o dla nazwy pliku z pytaniami
        if (argv[optind] != NULL) (*fileName) = argv[optind];
        else //ochrona przed zlym plikiem
        {
            printf("Podaj docelowa nazwe pliku!\nPrzyklad: ...path>Quiz.exe -o nazwaMojegoPliku\n");
            return 0;
        }
        break;
    case 'n': //przelacznik -n dla nazwy uzytkownika
        if (argv[optind] != NULL) (*user) = argv[optind];
        else //nazwa uzytkownika moze byc dowolna dlatego nie ma tutaj ograniczen
        {
            printf("Podaj nazwe uzytkownika!\nPrzyklad: ...path>Quiz.exe -n Uzytkownik\n");
            return 0;
        }
        break;
    case 'q':
        if (argv[optind] != NULL)
        {
            long val;
            char *next;
            val = strtol (argv[optind], &next, 10); //konwersja na long pozwalajaca wykryc falsz jezeli wartosc nie jest liczba
            if ((next == argv[optind]) || (*next != '\0'))   //sprawdza puste stany lub znaki po konwersji
            {
                printf ("'%s' is not valid\n", argv[optind]);
                return 0;
            }
            else *nrOfQ = atoi(argv[optind]);
        }
        break;
    }
    return 1;
}



