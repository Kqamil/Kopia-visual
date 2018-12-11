#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "samochody.h"
#include "pomocnicze.h"

samochod_ptr stworz_samochod(char *marka, int rok_produkcji, char *numer_rej)
{
	samochod_ptr nowy_samochod = malloc(sizeof(samochod));
	memset(nowy_samochod, 0, sizeof(*nowy_samochod));
	strcpy_s(nowy_samochod->marka, MARKA_DL, marka);
	nowy_samochod->rok_produkcji = rok_produkcji;
	strcpy_s(nowy_samochod->numer_rej, NUM_REJ_DL, numer_rej);
	return nowy_samochod;
}

void dodaj_samochod(samochod_ptr *glowa, samochod_ptr nowy)
{
	if (*glowa == NULL)
	{
		*glowa = nowy;
	}
	else
	{
		samochod_ptr akt_samochod = *glowa;
		while (akt_samochod->nastepny != NULL)
		{
			akt_samochod = akt_samochod->nastepny;
		}
		akt_samochod->nastepny = nowy;
	}
}

samochod_ptr dodaj_nowy_samochod(samochod_ptr *glowa, char *marka, int rok_produkcji, char *numer_rej)
{
	samochod_ptr nowy = stworz_samochod(marka, rok_produkcji, numer_rej);
	dodaj_samochod(glowa, nowy);
	return nowy;
}

int zlicz_wlascicieli(wlasciciel_ptr glowa)
{
	int liczba = 0;
	while (glowa)
	{
		liczba++;
		glowa = glowa->nastepny;
	}
	return liczba;
}

void wyswietl_samochod(samochod_ptr dane_samochodu, int tabela)
{
	if (tabela)
	{
		printf("%*s | %4d | %*s | %2d\n",
			MARKA_DL - 10, dane_samochodu->marka, dane_samochodu->rok_produkcji,
			NUM_REJ_DL, dane_samochodu->numer_rej,
			zlicz_wlascicieli(dane_samochodu->wlasciciele));
	}
	else
	{
		printf("Marka: %s\nRok: %d\nNumer rejestracyjny: %s\n", dane_samochodu->marka, dane_samochodu->rok_produkcji, dane_samochodu->numer_rej);

		if (dane_samochodu->wlasciciele)
		{
			printf("Obecny w³aœciciel:\n");
			wyswietl_osobe(dane_samochodu->wlasciciele, tabela);
			if (dane_samochodu->wlasciciele->nastepny)
			{
				printf("Poprzedni w³aœciciele:\n");
				wyswietl_liste_osob(dane_samochodu->wlasciciele->nastepny);
				printf("\n");
			}
		}
	}
}

int wyswietl_liste_samochodow(samochod_ptr glowa)
{
	samochod_ptr temp = glowa;
	int lp = 1;
	if (temp)
	{
		printf("Lp. | %*s | Rok  | %*s | W³aœciciele\n", MARKA_DL - 10, "Marka", NUM_REJ_DL, "Nr rej.");
	}
	while (temp)
	{
		printf("%2d. | ", lp++);
		wyswietl_samochod(temp, 1);
		temp = temp->nastepny;
	}
	return lp - 1;
}

samochod_ptr znajdz_samochod(samochod_ptr glowa, int pozycja)
{
	samochod_ptr temp = glowa; 
	int i = 1;
	while (temp && i++ != pozycja)
	{
		temp = temp->nastepny;
	}
	return temp;
}

void usuwanie_samochodu_z_listy(samochod_ptr *glowa, int pozycja)
{
	samochod_ptr sam = *glowa;
	if (pozycja == 1)
	{
		usuwanie_wlascicieli(&(sam->wlasciciele));
		*glowa = sam->nastepny;
		free(sam);
	}
	else
	{
		int i = 1;
		while (sam)
		{
			if ((i + 1) == pozycja)
			{
				break;
			}
			sam = sam->nastepny;
			i++;
		}
		samochod_ptr do_usuniecia = sam->nastepny;
		sam->nastepny = do_usuniecia->nastepny;
		usuwanie_wlascicieli(&(do_usuniecia->wlasciciele));
		free(do_usuniecia);
	}
}

void destruktor_samochodow(samochod_ptr *glowa)
{
	samochod_ptr temp = *glowa;
	samochod_ptr temp2 = NULL;
	while (temp)
	{
		usuwanie_wlascicieli(&(temp->wlasciciele));
		temp2 = temp->nastepny;
		free(temp);
		temp = temp2;
	}
}