#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ewidencja.h"
#include "samochody.h"
#include "wlasciciele.h"
#include "pomocnicze.h"

#define NAZWA_PLIKU "ewidencja.dat"

char kryteria_nazwy[][20] = {
	"mark�",
	"rok produkcji",
	"numer rejestracyjny",
	"imi�",
	"nazwisko",
	"dat� kupna"
};

int wczytaj(samochod_ptr *glowa)
{
	FILE *in;
	if (fopen_s(&in, NAZWA_PLIKU, "rb"))
	{
		printf("Nie mo�na otworzy� pliku!\n");
		return 0;
	}
	int liczba_samochodow = 0;
	while (!feof(in))
	{
		char koniec;
		int liczba_wla;
		samochod tmp_sam;
		fread_s(tmp_sam.marka, MARKA_DL, MARKA_DL, 1, in);
		fread_s(&tmp_sam.rok_produkcji, sizeof(tmp_sam.rok_produkcji), sizeof(tmp_sam.rok_produkcji), 1, in);
		if (!fread_s(tmp_sam.numer_rej, NUM_REJ_DL, NUM_REJ_DL, 1, in))
		{
			fclose(in);
			return liczba_samochodow;
		}
		samochod_ptr nowy_sam = dodaj_nowy_samochod(glowa, tmp_sam.marka, tmp_sam.rok_produkcji, tmp_sam.numer_rej);
		liczba_samochodow++;
		fread_s(&liczba_wla, sizeof(liczba_wla), sizeof(liczba_wla), 1, in);
		for (int i = 0; i < liczba_wla; i++)
		{
			wlasciciel nowy_wla;
			fread_s(nowy_wla.imie, IMIE_DL, IMIE_DL, 1, in);
			fread_s(nowy_wla.nazwisko, NAZW_DL, NAZW_DL, 1, in);
			fread_s(nowy_wla.data_kupna, DATA_DL, DATA_DL, 1, in);
			fread_s(nowy_wla.data_sprzedazy, DATA_DL, DATA_DL, 1, in);
			dodaj_wlasciciela(&nowy_sam->wlasciciele, nowy_wla.imie, nowy_wla.nazwisko, nowy_wla.data_sprzedazy, nowy_wla.data_kupna);
		}
		fread_s(&koniec, sizeof(koniec), sizeof(koniec), 1, in);		
	}
	fclose(in);
	return 1;
}

void zapisz(samochod_ptr glowa)
{
	FILE *out;
	int err = fopen_s(&out, NAZWA_PLIKU, "wb");
	if (err)
	{
		printf("Nie mo�na otworzy� pliku do zapisu! Kod %d\n", err);
		return;
	}
	samochod_ptr sam = glowa;
	while (sam)
	{
		fwrite(sam->marka, MARKA_DL, 1, out);
		fwrite(&(sam->rok_produkcji), sizeof(sam->rok_produkcji), 1, out);
		fwrite(sam->numer_rej, NUM_REJ_DL, 1, out);
		int liczba_wla = zlicz_wlascicieli(sam->wlasciciele);
		fwrite(&liczba_wla, sizeof(liczba_wla), 1, out);
		wlasciciel_ptr wla = sam->wlasciciele;
		while (wla)
		{
			fwrite(wla->imie, IMIE_DL, 1, out);
			fwrite(wla->nazwisko, NAZW_DL, 1, out);
			fwrite(wla->data_kupna, DATA_DL, 1, out);
			fwrite(wla->data_sprzedazy, DATA_DL, 1, out);
			wla = wla->nastepny;
		}
		fwrite("\n", 1, 1, out);
		sam = sam->nastepny;
	}
	fclose(out);
}

void dodawanie_samochodu(samochod_ptr *glowa)
{
	samochod nowy;
	printf("Podaj mark�: ");
	wczytaj_napis(nowy.marka, MARKA_DL);
	printf("Podaj rok produkcji (RRRR): ");
	wczytaj_liczbe(&nowy.rok_produkcji, ROK_PROD_DL);
	printf("Podaj numer rejestracyjny: ");
	wczytaj_napis(nowy.numer_rej, NUM_REJ_DL);
	dodaj_nowy_samochod(glowa, nowy.marka, nowy.rok_produkcji, nowy.numer_rej);
}

void dodawanie_wlasciciela(wlasciciel_ptr *glowa)
{
	wlasciciel nowy;
	printf("Podaj imi�: ");
	wczytaj_napis(nowy.imie, IMIE_DL);
	printf("Podaj nazwisko: ");
	wczytaj_napis(nowy.nazwisko, NAZW_DL);
	printf("Podaj dat� kupna samochodu (dd.mm.rrrr): ");
	wczytaj_napis(nowy.data_kupna, DATA_DL);
	zmien_wlasciciela(glowa, stworz_wlasciciela(nowy.imie, nowy.nazwisko, "", nowy.data_kupna));
}

void usuwanie_samochodu(samochod_ptr *glowa)
{
	int pozycja, ilosc;
	ilosc = wyswietl_liste_samochodow(*glowa);
	if (ilosc == 0)
	{
		printf("Brak samochod�w do usuni�cia.\n");
		return;
	}
	printf("Wybierz samoch�d do usuni�cia: ");
	wczytaj_liczbe(&pozycja, 2);
	if (pozycja == 0 || pozycja > ilosc)
	{
		printf("Podano z�y samoch�d!\n");
		return;
	}
	usuwanie_samochodu_z_listy(glowa, pozycja);
}

void usuwanie_wlasciciela(wlasciciel_ptr *glowa)
{
	int pozycja, ilosc;
	ilosc = wyswietl_liste_osob(*glowa);
	if (ilosc == 0)
	{
		return;
	}
	printf("Wybierz w�a�ciciela do usuni�cia: ");
	wczytaj_liczbe(&pozycja, 2);
	if (pozycja == 0 || pozycja > ilosc)
	{
		printf("Podano z�y numer w�a�ciciela\n");
		return;
	}
	usuwanie_wlasciciela_z_listy(glowa, pozycja);
}

void edytowanie_marki(samochod_ptr sam)
{
	printf("Podaj now� mark�:\n");
	wczytaj_napis(sam->marka, MARKA_DL);
}

void edytowanie_roku(samochod_ptr sam)
{
	printf("Podaj nowy rok produkcji:\n");
	wczytaj_liczbe(&sam->rok_produkcji, ROK_PROD_DL);
}

void edytowanie_rejestracji(samochod_ptr sam)
{
	printf("Podaj nowy numer rejestracyjny:\n");
	wczytaj_napis(sam->numer_rej, NUM_REJ_DL);
}

void edytowanie_danych_samochodu(samochod_ptr sam)
{
	while (1)
	{
		printf("Jak chcesz edytowa� samochod:\n");
		printf("0. Cofnij\n");
		printf("1. Zmie� mark�\n");
		printf("2. Zmie� rok produkcji\n");
		printf("3. Zmie� rejestracj�\n");
		char wyb[10];
		wczytaj_napis(wyb, 10);
		switch (wyb[0])
		{
		case '1':
			edytowanie_marki(sam);
			break;
		case '2':
			edytowanie_roku(sam);
			break;
		case '3':
			edytowanie_rejestracji(sam);
			break;
		case '0':
			return;
		default:
			printf("Klikni�to z�y klawisz, prosze klikn�� poprawny\n");
			break;
		}
	}
}

void edytowanie_imienia(wlasciciel_ptr sam)
{
	printf("Podaj nowe imi�:\n");
	wczytaj_napis(sam->imie, IMIE_DL);
}

void edytowanie_nazwiska(wlasciciel_ptr sam)
{
	printf("Podaj nowe nazwisko:\n");
	wczytaj_napis(sam->nazwisko, NAZW_DL);
}

void edytowanie_daty_kupna(wlasciciel_ptr sam)
{
	printf("Podaj now� dat� kupna:\n");
	wczytaj_napis(sam->imie, IMIE_DL);
}

void edytowanie_daty_sprzedazy(wlasciciel_ptr sam)
{
	printf("Podaj now� dat� sprzeda�y:\n");
	wczytaj_napis(sam->imie, IMIE_DL);
}

void edytowanie_danych_wlasciciela(wlasciciel_ptr glowa)
{
	int pozycja;
	wyswietl_liste_osob(glowa);
	printf("Kt�rego w�a�ciciela edytowa�: ");
	wczytaj_liczbe(&pozycja, 10);
	wlasciciel_ptr sam = znajdz_wlasciciela(glowa, pozycja);
	if (!sam)
	{
		printf("Nie znaleziono wlasciciela.\n");
		return;
	}
	while (1)
	{
		printf("Jak chcesz edytowa�:\n");
		printf("0. Cofnij.\n");
		printf("1. Zmie� imi�.\n");
		printf("2. Zmie� nazwisko.\n");
		printf("3. Zmie� dat� sprzeda�y\n");
		printf("4. Zmie� dat� kupna\n");
		printf("Wybierz czynno��: ");
		switch (wczytaj_wybor())
		{
		case 0:
			return;
		case 1:
			edytowanie_imienia(sam);
			break;
		case 2:
			edytowanie_nazwiska(sam);
			break;
		case 3:
			edytowanie_daty_sprzedazy(sam);
			break;
		case 4:
			edytowanie_daty_kupna(sam);
			break;
		default:
			printf("Nieobs�ugiwana warto��, prosz� wybra� ponownie.\n");
			break;
		}
	}
}

void wyszukaj(samochod_ptr glowa, int kryterium)
{
	printf("Podaj %s do znalezienia: ", kryteria_nazwy[kryterium - 1]);
	char odp[100];
	wczytaj_napis(odp, 100);
	printf("Wyszukuj� %s %s...\n", kryteria_nazwy[kryterium - 1], odp);
	samochod_ptr temp = glowa;
	char *wartosc = NULL;
	int znaleziono = 0;
	char tmp_rok_produkcji[ROK_PROD_DL + 1];
	while (temp)
	{
		switch (kryterium - 1)
		{
		case kryt_marka:
			wartosc = temp->marka;
			break;
		case kryt_rok_prod:
			sprintf_s(tmp_rok_produkcji, ROK_PROD_DL + 1, "%d", temp->rok_produkcji);
			wartosc = tmp_rok_produkcji;
			break;
		case kryt_nr_rej:
			wartosc = temp->numer_rej;
			break;
		case kryt_imie:
			if (temp->wlasciciele)
			{
				wartosc = temp->wlasciciele->imie;
			}
			break;
		case kryt_nazwisko:
			if (temp->wlasciciele)
			{
				wartosc = temp->wlasciciele->nazwisko;
			}
			break;
		case kryt_data_kupna:
			if (temp->wlasciciele)
			{
				wartosc = temp->wlasciciele->data_kupna;
			}
			break;
		}
		if (wartosc && !strcmp(wartosc, odp))
		{
			wyswietl_samochod(temp, 0);
			znaleziono = 1;
		}
		temp = temp->nastepny;
	}
	if (!znaleziono)
	{
		printf("Nie znaleziono pasuj�cych samochod�w.\n");
	}
}

void wyszukiwanie(samochod_ptr glowa)
{
	while (1)
	{
		printf("Wed�ug jakiego kryterium chcesz wyszuka�:\n");
		printf("0. Cofnij.\n");
		printf("1. Marka.\n");
		printf("2. Rok produkcji.\n");
		printf("3. Numer rejestrayjny.\n");
		printf("4. Imi� w�a�ciciela\n");
		printf("5. Nazwisko w�a�ciciela\n");
		printf("6. Data zakupu\n");
		int kryterium = wczytaj_wybor();
		if (kryterium > 0 && kryterium < 7)
		{
			wyszukaj(glowa, kryterium);
		}
		else if (kryterium == 0)
		{
			break;
		}
		else
		{
			printf("Klikni�to z�y klawisz, prosz� klikn�� poprawny.\n");
		}
	}
}

void ewidencja_edytowanie_samochodu(samochod_ptr glowa)
{
	int pozycja;
	wyswietl_liste_samochodow(glowa);
	printf("Wybierz samoch�d do edytowania: ");
	wczytaj_liczbe(&pozycja, 10);
	samochod_ptr sam = znajdz_samochod(glowa, pozycja);
	if (!sam)
	{
		printf("Nie znaleziono samochodu.\n");
		return;
	}
	while (1)
	{
		printf("Jak chcesz edytowa�:\n");
		printf("0. Cofnij.\n");
		printf("1. Wy�wietl w�a�cicieli.\n");
		printf("2. Edytuj dane samochodu.\n");
		printf("3. Dodaj w�a�ciciela.\n");
		printf("4. Usu� w�a�ciciela\n");
		printf("5. Edytuj w�a�ciciela\n");
		printf("Wybierz czynno��: ");
		char wyb[10];
		wczytaj_napis(wyb, 10);
		switch (wyb[0])
		{
		case '0':
			return;
		case '1':
			wyswietl_liste_osob(sam->wlasciciele);
			break;
		case '2':
			edytowanie_danych_samochodu(sam);
			break;
		case '3':
			dodawanie_wlasciciela(&sam->wlasciciele);
			break;
		case '4':
			usuwanie_wlasciciela(&sam->wlasciciele);
			break;
		case '5':
			edytowanie_danych_wlasciciela(sam->wlasciciele);
			break;
		default:
			printf("Klikni�to z�y klawisz, prosz� klikn�� poprawny\n");
			break;
		}
	}
}

void ewidencja_obsluga()
{
	samochod_ptr ewidencja = NULL;
	int wczytano = wczytaj(&ewidencja);
	printf("Liczba samochod�w wczytanych z pliku: %d\n", wczytano);
	if (!wczytano)
	{
		dodaj_nowy_samochod(&ewidencja, "volvo", 2007, "sb 76542");
		dodaj_wlasciciela(&ewidencja->wlasciciele, "Kamil", "Marek", "10.10.2010", "12.10.2010");
		dodaj_wlasciciela(&ewidencja->wlasciciele, "Adam", "Nowak", "10.10.2009", "10.10.2010");
		dodaj_nowy_samochod(&ewidencja, "Seat", 2015, "SK 54321");
		dodaj_wlasciciela(&ewidencja->nastepny->wlasciciele, "Kamil", "Marek", "10.10.2010", "12.10.2010");
	}
	printf("Baza danych samochod�w i w�a�cicieli (C) 2018 Kamil Marek\n\n");
	while (1)
	{
		printf("0. Zako�cz\n");
		printf("1. Wy�wietl samochody\n");
		printf("2. Dodaj samoch�d\n");
		printf("3. Edytuj samoch�d\n");
		printf("4. Usu� samoch�d\n");
		printf("5. Wyszukaj samoch�d\n");
		printf("Wybierz czynno��: ");
		char wyb[10];
		wczytaj_napis(wyb, 10);
		switch (wyb[0])
		{
		case '0':
			zapisz(ewidencja);
			destruktor_samochodow(&ewidencja);
			return;
		case '1':
			wyswietl_liste_samochodow(ewidencja);
			break;
		case '2':
			dodawanie_samochodu(&ewidencja);
			break;
		case '3':
			ewidencja_edytowanie_samochodu(ewidencja);
			break;
		case '4':
			usuwanie_samochodu(&ewidencja);
			break;
		case '5':
			wyszukiwanie(ewidencja);
			break;
		default:
			printf("Klikni�to z�y klawisz, prosz� klikn�� poprawny\n");
			break;
		}
	}
}