#include <stdio.h>
#include <stdlib.h>

#include "pomocnicze.h"
#include "samochody.h"

void wczytaj_napis(char *napis, int dlugosc)
{
	int i = 0;
	int c = getchar();
	while ((c != '\n' || i == 0) && c != EOF)
	{
		if (i < dlugosc && c != '\n')
		{
			napis[i++] = c;
		}
		c = getchar();
	}
	napis[i] = 0;
}

void wczytaj_liczbe(int *liczba, int dlugosc)
{
	char *odp = malloc(dlugosc + 1);
	wczytaj_napis(odp, dlugosc);
	*liczba = atoi(odp);
	free(odp);
}

int wczytaj_wybor()
{
	int wybor;
	wczytaj_liczbe(&wybor, 1);
	return wybor;
}
