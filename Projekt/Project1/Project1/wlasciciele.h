#pragma once
#ifndef WLASCICIELE_H
#define WLASCICIELE_H

#define IMIE_DL 20
#define NAZW_DL 35
#define DATA_DL 11

struct wlasciciel
{
	char imie[IMIE_DL];
	char nazwisko[NAZW_DL];
	char data_sprzedazy[DATA_DL];
	char data_kupna[DATA_DL];
	struct wlasciciel *nastepny;
};

typedef struct wlasciciel wlasciciel;
typedef wlasciciel* wlasciciel_ptr;

wlasciciel *stworz_wlasciciela(char *imie, char *nazwisko, char *data_sprzedazy, char *data_kupna);
void dodaj_wlasciciela(wlasciciel_ptr *glowa, char *imie, char *nazwisko, char *data_sprzedazy, char *data_kupna);
void wyswietl_osobe(wlasciciel_ptr dane_osoby, int tabela);
int wyswietl_liste_osob(wlasciciel_ptr glowa);
void zmien_wlasciciela(wlasciciel_ptr *glowa, wlasciciel_ptr nowy);
wlasciciel_ptr znajdz_wlasciciela(wlasciciel_ptr glowa, int pozycja);
void usuwanie_wlascicieli(wlasciciel_ptr *glowa);
void usuwanie_wlasciciela_z_listy(wlasciciel_ptr *glowa, int pozycja);
#endif