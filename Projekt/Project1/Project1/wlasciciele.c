#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "wlasciciele.h"

wlasciciel_ptr stworz_wlasciciela(char *imie, char *nazwisko, char *data_sprzedazy, char *data_kupna)
{
	wlasciciel_ptr nowa_osoba = malloc(sizeof(wlasciciel));
	memset(nowa_osoba, 0, sizeof(*nowa_osoba));
	strcpy_s(nowa_osoba->imie, IMIE_DL, imie);
	strcpy_s(nowa_osoba->nazwisko, NAZW_DL, nazwisko);
	strcpy_s(nowa_osoba->data_sprzedazy, DATA_DL, data_sprzedazy);
	strcpy_s(nowa_osoba->data_kupna, DATA_DL, data_kupna);
	return nowa_osoba;
}

void dodaj_wlasciciela(wlasciciel_ptr *glowa, char *imie, char *nazwisko, char *data_sprzedazy, char *data_kupna)
{
	wlasciciel_ptr dodawana_osoba = stworz_wlasciciela(imie, nazwisko, data_sprzedazy, data_kupna);
	if (*glowa == NULL)
	{
		*glowa = dodawana_osoba;
		return;
	}
	else
	{
		wlasciciel_ptr akt_osoba = *glowa;
		while (akt_osoba->nastepny != NULL)
		{
			akt_osoba = akt_osoba->nastepny;
		}
		akt_osoba->nastepny = dodawana_osoba;
		return;
	}
}

void wyswietl_osobe(wlasciciel_ptr dane_osoby, int tabela)
{
	if (tabela)
	{
		if (dane_osoby->data_sprzedazy[0])
		{
			printf("%*s | %*s | %10s | %10s\n",
				IMIE_DL, dane_osoby->imie, NAZW_DL, dane_osoby->nazwisko, dane_osoby->data_kupna, dane_osoby->data_sprzedazy);
		}
		else
		{
			printf("%*s | %*s | %10s | Brak \n",
				IMIE_DL, dane_osoby->imie, NAZW_DL, dane_osoby->nazwisko, dane_osoby->data_kupna);
		}
	}
	else
	{
		printf("  Imiê: %s\n  Nazwisko: %s\n  Data kupna samochodu: %s\n", dane_osoby->imie, dane_osoby->nazwisko, dane_osoby->data_kupna);
		if (dane_osoby->data_sprzedazy[0])
		{
			printf("  Data sprzeda¿y samochodu: %s\n", dane_osoby->data_sprzedazy);
		}
	}
}

int wyswietl_liste_osob(wlasciciel_ptr glowa)
{
	wlasciciel_ptr temp = glowa;
	int lp = 1;
	if (temp)
	{
		printf("Lp. | %*s | %*s | Data kupna | Data sprzeda¿y \n", IMIE_DL, "Imie", NAZW_DL, "Nazwisko");
	}
	else
	{
		printf("Brak w³aœcicieli.\n");
	}
	while (temp)
	{
		printf("%2d. | ", lp++);
		wyswietl_osobe(temp, 1);
		temp = temp->nastepny;
	}
	return lp - 1;
}

void zmien_wlasciciela(wlasciciel_ptr *glowa, wlasciciel_ptr nowy)
{
	nowy->nastepny = *glowa;
	*glowa = nowy;
	if (nowy->nastepny)
	{
		strcpy_s(nowy->nastepny->data_sprzedazy, DATA_DL, (*glowa)->data_kupna);
	}
}

wlasciciel_ptr znajdz_wlasciciela(wlasciciel_ptr glowa, int pozycja)
{
	wlasciciel_ptr temp = glowa;
	int i = 1;
	while (temp && i++ != pozycja)
	{
		temp = temp->nastepny;
	}
	return temp;
}

void usuwanie_wlascicieli(wlasciciel_ptr *glowa)
{
	wlasciciel_ptr wla = *glowa;
	wlasciciel_ptr temp;
	while (wla)
	{
		temp = wla->nastepny;
		free(wla);
		wla = temp;
	}
	*glowa = NULL;
}

void usuwanie_wlasciciela_z_listy(wlasciciel_ptr *glowa, int pozycja)
{
	wlasciciel_ptr wla = *glowa;
	if (pozycja == 1)
	{
		*glowa = wla->nastepny;
		free(wla);
	}
	else
	{
		int i = 1;
		while (wla)
		{
			if ((i + 1) == pozycja)
			{
				break;
			}
			wla = wla->nastepny;
			i++;
		}
		wlasciciel_ptr do_usuniecia = wla->nastepny;
		wla->nastepny = do_usuniecia->nastepny;
		free(do_usuniecia);
	}
}