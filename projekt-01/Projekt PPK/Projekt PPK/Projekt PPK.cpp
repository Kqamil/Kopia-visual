// ProjektPPK.cpp: Definiuje punkt wejœcia dla aplikacji konsolowej.
//
/*Zadanie 26.
Napisaæ program formatuj¹cy plik tekstowy. Zasady formatowania:
- pomiêdzy wyrazami wystêpuje tylko jedna spacja (nadmiarowe spacje miêdzy wyrazami nale¿y usun¹æ),
- znaki przestankowe powinny byæ umieszczone bezpoœrednio po wyrazie (nadmiarowe spacje nale¿y usun¹æ), po znaku przestankowym powinna wyst¹piæ jedna spacja.
- ka¿dy wyraz powinien zawieraæ wy³¹cznie ma³e litery (w przypadku wyst¹pienia wielkich liter nale¿y je zamieniæ na ma³e), wyj¹tkiem jest pierwszy wyraz w zdaniu (wyraz po kropce),
którego pierwsza litera jest wielka,
- usun¹æ nadmiarowe znaki przestankowe.*/
#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
#include<string>
using namespace std;

string poprawka(string wyrazenie)
{
	unsigned int i;
	if (wyrazenie[0] >= 'a' && wyrazenie[0] <= 'z')// jeœli pierwsza litera w zdaniu jest ma³a to zostaje zamieniona na du¿¹. 
	{
		wyrazenie[0] -= 32;
	}
	for (i = 1; i < wyrazenie.size(); i++) // analiza ka¿dej litery w zdaniu. jeœli jest du¿a to jest zamieniana na ma³¹.
	{
		if (wyrazenie[i] >= 'A' && wyrazenie[i] <= 'Z')
		{
			wyrazenie[i] += 32;
		}
	}
	for (i = 1; i < wyrazenie.size(); i++)
	{
		if (wyrazenie[i - 1] >= '!' && wyrazenie[i - 1] <= '/' && wyrazenie[i] >= 'a' && wyrazenie[i] <= 'z') //jeœli przed liter¹ jest znak przestankowy to zostaje dodana miêdzy nimi spacja
		{
			wyrazenie.insert(i, " ");
		}
		if (i > 1 && wyrazenie[i - 2] == '.' && wyrazenie[i] >= 'a' && wyrazenie[i] <= 'z') // jeœli po kropce pierwsza litera jest ma³a zostaje zamieniona na du¿¹
		{
			wyrazenie[i] -= 32;
		}
		if (wyrazenie[i - 1] == ' ' && wyrazenie[i] == ' ') // wiêcej ni¿ jedna spacja jest usuwana. 
		{
			wyrazenie.erase(i - 1, 1);
			i--;
		}
		if (wyrazenie[i - 1] == ' ' && wyrazenie[i] >= '!' && wyrazenie[i] <= '/') // spacja przed znakiem przystankowym jest usuwana.
		{
			wyrazenie.erase(i - 1, 1);
			i--;
		}
		if (wyrazenie[i - 1] >= '!' && wyrazenie[i - 1] <= '/' && wyrazenie[i] >= '!' && wyrazenie[i] <= '/') // wiêcej ni¿ jeden znak przestankowy jest usuwany.
		{
			wyrazenie.erase(i, 1);
			i--;
		}
	}
	return wyrazenie;
}

int main()
{
	ifstream p_tekstowy("tekst.txt");
	string wyrazenie;
	if (!p_tekstowy)
	{
		cerr << "Plik nie istnieje lub znajduje sie w niewlasciwym miejscu.\n" <<
			"Plik powinien sie nazywac tekst, z rozszerzeniem .txt i znajdowac sie w folderze roboczym." << endl;
		return 1;
	}
	ofstream p_poprawione("poprawiony tekst.txt");
	if (!p_poprawione)
	{
		cerr << "Nie udalo sie otworzyc pliku 'poprawiony tekst.txt' do zapisu." << endl;
		return 1;
	}
	while (!p_tekstowy.eof())
	{
		getline(p_tekstowy, wyrazenie);
		p_poprawione << poprawka(wyrazenie) << endl;
	}
	cout << "Tekst zostal poprawiony i znajduje sie w pliku 'poprawiony tekst.txt'" << endl;
	return 0;
}
