#pragma once
#ifndef EWIDENCJA_H
#define EWIDENCJA_H

#include "samochody.h"

enum kryteria {
	kryt_marka,
	kryt_rok_prod,
	kryt_nr_rej,
	kryt_imie,
	kryt_nazwisko,
	kryt_data_kupna
};

int wczytaj(samochod_ptr *glowa);
void zapisz(samochod_ptr glowa);
void dodawanie_samochodu(samochod_ptr *glowa);
void dodawanie_wlasciciela(wlasciciel_ptr *glowa);
void usuwanie_samochodu(samochod_ptr *glowa);
void edytowanie_marki(samochod_ptr sam);
void edytowanie_roku(samochod_ptr sam);
void edytowanie_rejestracji(samochod_ptr sam);
void edytowanie_danych_samochodu(samochod_ptr sam);
void edytowanie_imienia(wlasciciel_ptr sam);
void edytowanie_nazwiska(wlasciciel_ptr sam);
void edytowanie_daty_kupna(wlasciciel_ptr sam);
void edytowanie_daty_sprzedazy(wlasciciel_ptr sam);
void edytowanie_danych_wlasciciela(wlasciciel_ptr glowa);
void wyszukaj(samochod_ptr glowa, int kryterium);
void wyszukiwanie(samochod_ptr glowa);
void ewidencja_edytowanie_samochodu(samochod_ptr glowa);
void ewidencja_obsluga();
#endif