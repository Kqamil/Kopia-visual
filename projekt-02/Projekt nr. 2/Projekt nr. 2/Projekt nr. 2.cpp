/*Zadanie 20.
Napisać program do ewidencjonowania samochodów.Dla każdego samochodu należy zapamiętać :
- markę,
- rok produkcji,
- numer rejestracyjny,
- dane właściciela,
- od kiedy jest w posiadaniu przez aktualnego właściciela.
Ponadto należy zapamiętać dane poprzednich właścicieli, w tym przypadku zapamiętać także datę nabycia i datę sprzedaży auta.
Umożliwić dodawanie nowych samochodów do bazy, modyfikację i usuwanie istniejących.Powinna być także możliwość wyszukiwania według różnych kryteriów.

Projekt nr. 2.cpp : Defines the entry point for the console application.
*/

#include "stdafx.h"
#include <iostream>
#include <list>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

struct osoba
{
	string imie;
	string nazwisko;
	string data_sprzedazy;
	string data_kupna;
	void wyswietl();
	osoba(string im, string nazw, string kupna, string sprzed = "");
	osoba();
	void edyt_imie();
	void edyt_nazwisko();
	void edyt_sprzed();
	void edyt_kup();
};

osoba::osoba()
{
}

osoba::osoba(string im, string nazw, string kupna, string sprzed)
{
	imie = im;
	nazwisko = nazw;
	data_kupna = kupna;
	data_sprzedazy = sprzed;
}

void osoba::wyswietl()
{
	cout << "	Imie: " << imie << endl << "	Nazwisko: " << nazwisko << endl << "	Data kupna samochodu: " << data_kupna << endl;
	if (!data_sprzedazy.empty())
	{
		cout << "	Data sprzedaży samochodu: " << data_sprzedazy << endl;
	}
}

void osoba::edyt_imie()
{
	cout << "Podaj nowe imię: ";
	cin >> imie;
}

void osoba::edyt_nazwisko()
{
	cout << "Podaj nowe nazwisko: ";
	cin >> nazwisko;
}

void osoba::edyt_kup()
{
	cout << "Podaj nową datę zakupu: ";
	cin >> data_kupna;
}

void osoba::edyt_sprzed()
{
	cout << "Podaj nową datę sprzedaży: ";
	cin >> data_sprzedazy;
}

struct osoby
{
	osoba* dane;
	osoby* nastepna;
	osoby(osoba* os);
	~osoby();
	void wyswietl();
};

osoby::osoby(osoba* os)
{
	dane = os;
	nastepna = nullptr;
}

osoby::~osoby()
{
	delete nastepna;
	delete dane;
}

void osoby::wyswietl()
{
	int j = 1;
	osoby* temp = this;
	while (temp)
	{
		cout << "	" << j++ << "." << endl;
		temp->dane->wyswietl();
		temp = temp->nastepna;
	}
}

struct samochod
{
	string marka;
	string rok_produkcji;
	string numer_rej;
	osoby* wlasciciele;
	samochod();
	samochod(string marka, string rok_produkcji, string numer_rej, osoby* wlasciciele);
	~samochod();
	void wyswietl();
	void edyt_mark();
	void edyt_rok();
	void edyt_rej();
	void zmien_wlasciciela(osoba* wla);
	void dodaj_wlasciciela(osoba* wla);
	osoba* znajdz_osobe(int poz);
};

samochod::samochod()
{
	wlasciciele = nullptr;
}

samochod::samochod(string marka, string rok_produkcji, string numer_rej, osoby* wlasciciele)
{
	this->marka = marka;
	this->rok_produkcji = rok_produkcji;
	this->numer_rej = numer_rej;
	this->wlasciciele = wlasciciele;
}

samochod::~samochod()
{
	delete wlasciciele;
}

void samochod::wyswietl()
{
	cout << "Marka: " << marka << endl << "Rok produkcji: " << rok_produkcji << endl << "Numer rejestracyjny: " << numer_rej << endl;
	if (wlasciciele)
	{
		cout << "Obecny właściciel: " << endl;
		wlasciciele->dane->wyswietl();
		if (wlasciciele->nastepna)
		{
			cout << "Poprzedni właściciele: " << endl;
			wlasciciele->nastepna->wyswietl();
			cout << endl;
		}
	}

	cout << endl;
}

void samochod::edyt_mark()
{
	cout << "Podaj nową markę: " << endl;
	cin >> marka;
}

void samochod::edyt_rok()
{
	cout << "Podaj nowy rok produkcji: " << endl;
	cin >> rok_produkcji;
}

void samochod::edyt_rej()
{
	cout << "Podaj nową rejestrację: " << endl;
	cin >> numer_rej;
}

void samochod::zmien_wlasciciela(osoba* wla)
{
	osoby* nowa = new osoby(wla);
	nowa->nastepna = wlasciciele;
	wlasciciele = nowa;
	if (nowa->nastepna)
	{
		nowa->nastepna->dane->data_sprzedazy = wla->data_kupna;
	}
}

void samochod::dodaj_wlasciciela(osoba* wla)
{
	osoby* nowa = new osoby(wla);
	if (wlasciciele)
	{
		auto temp = wlasciciele;
		while (temp->nastepna)
		{
			temp = temp->nastepna;
		}
		temp->nastepna = nowa;
	}
	else
	{
		wlasciciele = nowa;
	}
}

osoba* samochod::znajdz_osobe(int poz)
{
	auto wla = wlasciciele;
	int i = 1;
	while (wla && i++ != poz)
	{
		wla = wla->nastepna;
	}
	if (wla)
	{
		return wla->dane;
	}
	else
	{
		return nullptr;
	}
}

struct samochody
{
	samochod* dane;
	samochody* nastepna;
	samochody(samochod* sam);
	~samochody();
};

samochody::samochody(samochod* sam)
{
	dane = sam;
	nastepna = nullptr;
}

samochody::~samochody()
{
	delete dane;
	delete nastepna;
}

struct ewidencja
{
	samochody *glowa;
	ewidencja();
	~ewidencja();
	void poczatkowe();
	void dodaj_samochod(samochod* dane);
	void usun_samochod();
	void wyswietl();
	void dodawanie();
	void edytowanie();
	samochod* znajdz_samochod(int poz);
	void edyt_sam(samochod* sam);
	void dod_wla(samochod* sam);
	void usun_wla(samochod* sam);
	void edyt_wla(samochod* sam);
	void obsluga();
	void kryterium();
	void wyszukaj(string kryterium);
	void wczytaj();
	void zapisz();
};

ewidencja::ewidencja()
{
	glowa = nullptr;
}

ewidencja::~ewidencja()
{
	delete glowa;
}

void ewidencja::poczatkowe()
{
	dodaj_samochod(new samochod("seat", "2015", "SB7131N", new osoby(new osoba("Kamil", "Marek", "17.02.2016"))));
	auto sam = new samochod("Volvo", "2010", "SB53424", new osoby(new osoba("Cezariusz", "Marek", "11.10.2010")));
	sam->zmien_wlasciciela(new osoba("Stefan", "Nowak", "12.10.2017"));
	dodaj_samochod(sam);
	dodaj_samochod(new samochod("Lancia", "2009", "SB87142", new osoby(new osoba("Olga", "Łozińska", "10.03.2013"))));
	dodaj_samochod(new samochod("Ford", "2017", "SB888nn", nullptr));
}

void ewidencja::dodaj_samochod(samochod* dane)
{
	samochody* sam = new samochody(dane);
	if (glowa == nullptr)
	{
		glowa = sam;
	}
	else
	{
		auto temp = glowa;
		while (temp->nastepna)
		{
			temp = temp->nastepna;
		}
		temp->nastepna = sam;
	}
}

void ewidencja::usun_samochod()
{
	wyswietl();
	int pozycja;
	cout << "Samochód na której pozycji ma być usunięty: ";
	cin >> pozycja;
	if (pozycja == 1)
	{
		samochody *temp = glowa->nastepna;
		glowa->nastepna = nullptr;
		delete glowa;
		glowa = temp;
	}
	else
	{
		int i = 1;
		samochody *temp = glowa;
		while (temp)
		{
			if ((i + 1) == pozycja)
			{
				break;
			}
			temp = temp->nastepna;
			i++;
		}
		auto x = temp->nastepna;
		if (x->nastepna == nullptr)
		{
			temp->nastepna = nullptr;
		}
		else
		{
			temp->nastepna = x->nastepna;
		}
		delete x;
	}
}

void ewidencja::wyswietl()
{
	samochody* temp = glowa;
	int j = 1;
	while (temp)
	{
		cout << j++ << "." << endl;
		temp->dane->wyswietl();
		temp = temp->nastepna;
	}
}

void ewidencja::wyszukaj(string kryterium)
{
	string wed;
	cout << "Podaj " << kryterium << ": ";
	cin >> wed;
	cout << endl << "Wyniki wyszukiwania:" << endl;
	samochody* temp = glowa;
	int j = 1;
	string wartosc;
	bool znaleziono = false;
	while (temp)
	{
		wartosc = "";
		if (kryterium == "markę")
		{
			wartosc = temp->dane->marka;
		}
		else if (kryterium == "rok produkcji")
		{
			wartosc = temp->dane->rok_produkcji;
		}
		else if (kryterium == "numer rejestracyjny")
		{
			wartosc = temp->dane->numer_rej;
		}
		else if (kryterium == "imię" && temp->dane->wlasciciele)
		{
			wartosc = temp->dane->wlasciciele->dane->imie;
		}
		else if (kryterium == "nazwisko" && temp->dane->wlasciciele)
		{
			wartosc = temp->dane->wlasciciele->dane->nazwisko;
		}
		else if (kryterium == "datę kupna" && temp->dane->wlasciciele)
		{
			wartosc = temp->dane->wlasciciele->dane->data_kupna;
		}
		if (wartosc == wed)
		{
			temp->dane->wyswietl();
			znaleziono = true;
		}
		temp = temp->nastepna;
	}
	if (!znaleziono)
	{
		cout << "Nie znaleziono pasujących samochodów!" << endl;
	}
}

void ewidencja::dodawanie()
{
	auto x = new samochod;
	cout << "Podaj markę: ";
	cin >> x->marka;
	cout << "Podaj rok produkcji (RRRR): ";
	cin >> x->rok_produkcji;
	cout << "Podaj numer rejestracyjny: ";
	cin >> x->numer_rej;
	dodaj_samochod(x);
}

void ewidencja::edytowanie()
{
	int poz;
	wyswietl();
	cout << "Wybierz samochód do edytowania: ";
	cin >> poz;
	auto sam = znajdz_samochod(poz);
	if (!sam)
	{
		cout << "Nie znaleziono samochodu." << endl;
		return;
	}
	char wybor;
	while (true)
	{
		cout << "Jak chcesz edytować:" << endl;
		cout << "1. Edytuj dane samochodu" << endl;
		cout << "2. Dodaj właściciela" << endl;
		cout << "3. Usuń właściciela" << endl;
		cout << "4. Edytuj właściciela" << endl;
		cout << "0. Cofnij" << endl;
		cin >> wybor;
		switch (wybor)
		{
		case '1':
			edyt_sam(sam);
			break;
		case '2':
			dod_wla(sam);
			break;
		case '3':
			usun_wla(sam);
			break;
		case '4':
			edyt_wla(sam);
			break;
		case '0':
			return;
		default:
			cout << "Kliknięto zły klawisz, prosze kliknąć poprawny" << endl;
			break;
		}
	}
}

samochod* ewidencja::znajdz_samochod(int poz)
{
	auto sam = glowa;
	int i = 1;
	while (sam && i++ != poz)
	{
		sam = sam->nastepna;
	}
	if (sam)
	{
		return sam->dane;
	}
	else
	{
		return nullptr;
	}
}

void ewidencja::edyt_sam(samochod* sam)
{
	char wybor;
	while (true)
	{
		cout << "Jak chcesz edytować samochod:" << endl;
		cout << "1. Zmień markę" << endl;
		cout << "2. Zmień rok produkcji" << endl;
		cout << "3. Zmień rejestrację" << endl;
		cout << "0. Cofnij" << endl;
		cin >> wybor;
		switch (wybor)
		{
		case '1':
			sam->edyt_mark();
			break;
		case '2':
			sam->edyt_rok();
			break;
		case '3':
			sam->edyt_rej();
			break;
		case '0':
			return;
		default:
			cout << "Kliknięto zły klawisz, prosze kliknąć poprawny" << endl;
			break;
		}
	}
}

void ewidencja::dod_wla(samochod* sam)
{
	char wyb;
	osoba* wla = new osoba;
	cout << "Podaj imię: ";
	cin >> wla->imie;
	cout << "Podaj nazwisko: ";
	cin >> wla->nazwisko;
	cout << "Podaj datę kupna samochodu (dd.mm.rrrr): ";
	cin >> wla->data_kupna;
	cout << "Czy chcesz wprowadzić datę sprzedaży (t/n)?";
	cin >> wyb;
	if (wyb == 't')
	{
		cout << "Podaj datę sprzedaży samochodu: ";
		cin >> wla->data_sprzedazy;
	}
	sam->zmien_wlasciciela(wla);
}

void ewidencja::usun_wla(samochod* sam)
{
	int poz;
	sam->wlasciciele->wyswietl();
	cout << "Którego właściciela usunąć: ";
	cin >> poz;
	if (poz == 1)
	{
		osoby *temp = sam->wlasciciele->nastepna;
		sam->wlasciciele->nastepna = nullptr;
		delete sam->wlasciciele;
		sam->wlasciciele = temp;
	}
	else
	{
		int i = 1;
		osoby *temp = sam->wlasciciele;
		while (temp)
		{
			if ((i + 1) == poz)
			{
				break;
			}
			temp = temp->nastepna;
			i++;
		}
		auto x = temp->nastepna;
		if (x->nastepna == nullptr)
		{
			temp->nastepna = nullptr;
		}
		else
		{
			temp->nastepna = x->nastepna;
		}
		delete x;
	}
}

void ewidencja::edyt_wla(samochod* sam)
{
	int poz;
	sam->wlasciciele->wyswietl();
	cout << "Którego właściciela edytować: ";
	cin >> poz;
	auto osoba = sam->znajdz_osobe(poz);
	if (!osoba)
	{
		cout << "Nie znaleziono osoby" << endl;
		return;
	}
	char wybor;
	while (true)
	{
		cout << "Jak chcesz edytować właściciela:" << endl;
		cout << "1. Zmień imię" << endl;
		cout << "2. Zmień nazwisko" << endl;
		cout << "3. Zmień datę sprzedaży" << endl;
		cout << "4. Zmień datę kupna" << endl;
		cout << "0. Cofnij" << endl;
		cin >> wybor;
		switch (wybor)
		{
		case '1':
			osoba->edyt_imie();
			break;
		case '2':
			osoba->edyt_nazwisko();
			break;
		case '3':
			osoba->edyt_sprzed();
			break;
		case '4':
			osoba->edyt_kup();
			break;
		case '0':
			return;
		default:
			cout << "Kliknięto zły klawisz, prosze kliknąć poprawny" << endl;
			break;
		}
	}

}

void ewidencja::kryterium()
{
	char wyb;
	while (true)
	{
		cout << "Dostępne kryteria wyszukiwania: " << endl;
		cout << "1. Marka" << endl;
		cout << "2. Rok produkcji" << endl;
		cout << "3. Numer rejestracyjny" << endl;
		cout << "4. Imię właściciela" << endl;
		cout << "5. Nazwisko właściciela" << endl;
		cout << "6. Data zakupu" << endl;
		cout << "O. Cofnij" << endl;
		cout << "Wybierz opcję: ";
		cin >> wyb;
		switch (wyb)
		{
		case '1':
			wyszukaj("markę");
			break;
		case '2':
			wyszukaj("rok produkcji");
			break;
		case '3':
			wyszukaj("numer rejestracyjny");
			break;
		case '4':
			wyszukaj("imię");
			break;
		case '5':
			wyszukaj("nazwisko");
			break;
		case '6':
			wyszukaj("datę kupna");
			break;
		case '0':
			return;
		default:
			cout << "Kliknięto zły klawisz, prosze kliknąć poprawny" << endl;
			break;
		}
	}
}

void ewidencja::obsluga()
{
	cout << "Baza danych samochodów i właścicieli (C) 2018 Kamil Marek" << endl << endl;
	while (true)
	{
		cout << "0. Zakończ" << endl;
		cout << "1. Wyświetl samochody" << endl;
		cout << "2. Dodaj samochód" << endl;
		cout << "3. Edytuj samochód" << endl;
		cout << "4. Usuń samochód" << endl;
		cout << "5. Wyszukaj samochód" << endl;
		cout << "Wybierz czynność: ";
		char wyb;
		cin >> wyb;
		switch (wyb)
		{
		case '0':
			zapisz();
			return;
		case '1':
			wyswietl();
			break;
		case '2':
			dodawanie();
			break;
		case '3':
			edytowanie();
			break;
		case '4':
			usun_samochod();
			break;
		case '5':
			kryterium();
			break;
		default:
			cout << "Kliknięto zły klawisz, prosze kliknąć poprawny" << endl;
			break;
		}
	}
}

void ewidencja::wczytaj()
{
	ifstream ifs("ewidencja.txt");
	if (!ifs)
	{
		poczatkowe();
		return;
	}
	for (string line; getline(ifs, line);)
	{
		unsigned int pole = 0;
		vector <string> dane;
		int pos = 0, end;
		while (true)
		{
			end = line.find('|', pos);
			if (end == string::npos)
			{
				break;
			}
			else
			{
				dane.push_back(line.substr(pos, end - pos));
				pos = end + 1;
			}
		}
		samochod* nowy = new samochod(dane[pole], dane[pole + 1], dane[pole + 2], nullptr);
		dodaj_samochod(nowy);
		pole = 3;
		while (dane.size() > pole)
		{
			osoba* nowy_osoba = new osoba(dane[pole], dane[pole + 1], dane[pole + 2], dane[pole + 3]);
			nowy->dodaj_wlasciciela(nowy_osoba);
			pole += 4;
		}
	}
}

void ewidencja::zapisz()
{
	ofstream ofs("ewidencja.txt");
	samochody* temp = glowa;
	int j = 1;
	while (temp)
	{
		ofs << temp->dane->marka << "|";
		ofs << temp->dane->rok_produkcji << "|";
		ofs << temp->dane->numer_rej << "|";
		osoby* temp_osoby = temp->dane->wlasciciele;
		while (temp_osoby)
		{
			ofs << temp_osoby->dane->imie << "|";
			ofs << temp_osoby->dane->nazwisko << "|";
			ofs << temp_osoby->dane->data_kupna << "|";
			ofs << temp_osoby->dane->data_sprzedazy << "|";
			temp_osoby = temp_osoby->nastepna;
		}
		ofs << endl;
		temp = temp->nastepna;
	}
}

int main()
{
	SetConsoleOutputCP(1250);
	ewidencja baza;
	//baza.poczatkowe();
	baza.wczytaj();
	baza.obsluga();
	return 0;
}