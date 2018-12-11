#pragma once
#ifndef SAMOCHODY_H
#define SAMOCHODY_H
#include "wlasciciele.h"

#define MARKA_DL 20
#define ROK_PROD_DL 4
#define NUM_REJ_DL 9

struct samochod
{
	char marka[MARKA_DL];
	int rok_produkcji;
	char numer_rej[NUM_REJ_DL];
	struct samochod *nastepny;
	struct wlasciciel *wlasciciele;
};

typedef struct samochod samochod;
typedef samochod* samochod_ptr;

samochod_ptr stworz_samochod(char *marka, int rok_produkcji, char *numer_rej);
void dodaj_samochod(samochod_ptr *glowa, samochod_ptr nowy);
samochod_ptr dodaj_nowy_samochod(samochod_ptr *glowa, char *marka, int rok_produkcji, char *numer_rej);
int zlicz_wlascicieli(wlasciciel_ptr glowa);
void wyswietl_samochod(samochod_ptr dane_samochodu, int tabela);
int wyswietl_liste_samochodow(samochod_ptr glowa);
samochod_ptr znajdz_samochod(samochod_ptr glowa, int pozycja);
void usuwanie_samochodu_z_listy(glowa, pozycja);
void destruktor_samochodow(samochod_ptr *glowa);
#endif