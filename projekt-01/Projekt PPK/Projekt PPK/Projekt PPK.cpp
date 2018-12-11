// ProjektPPK.cpp: Definiuje punkt wej�cia dla aplikacji konsolowej.
//
/*Zadanie 26.
Napisa� program formatuj�cy plik tekstowy. Zasady formatowania:
- pomi�dzy wyrazami wyst�puje tylko jedna spacja (nadmiarowe spacje mi�dzy wyrazami nale�y usun��),
- znaki przestankowe powinny by� umieszczone bezpo�rednio po wyrazie (nadmiarowe spacje nale�y usun��), po znaku przestankowym powinna wyst�pi� jedna spacja.
- ka�dy wyraz powinien zawiera� wy��cznie ma�e litery (w przypadku wyst�pienia wielkich liter nale�y je zamieni� na ma�e), wyj�tkiem jest pierwszy wyraz w zdaniu (wyraz po kropce),
kt�rego pierwsza litera jest wielka,
- usun�� nadmiarowe znaki przestankowe.*/
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
	if (wyrazenie[0] >= 'a' && wyrazenie[0] <= 'z')// je�li pierwsza litera w zdaniu jest ma�a to zostaje zamieniona na du��. 
	{
		wyrazenie[0] -= 32;
	}
	for (i = 1; i < wyrazenie.size(); i++) // analiza ka�dej litery w zdaniu. je�li jest du�a to jest zamieniana na ma��.
	{
		if (wyrazenie[i] >= 'A' && wyrazenie[i] <= 'Z')
		{
			wyrazenie[i] += 32;
		}
	}
	for (i = 1; i < wyrazenie.size(); i++)
	{
		if (wyrazenie[i - 1] >= '!' && wyrazenie[i - 1] <= '/' && wyrazenie[i] >= 'a' && wyrazenie[i] <= 'z') //je�li przed liter� jest znak przestankowy to zostaje dodana mi�dzy nimi spacja
		{
			wyrazenie.insert(i, " ");
		}
		if (i > 1 && wyrazenie[i - 2] == '.' && wyrazenie[i] >= 'a' && wyrazenie[i] <= 'z') // je�li po kropce pierwsza litera jest ma�a zostaje zamieniona na du��
		{
			wyrazenie[i] -= 32;
		}
		if (wyrazenie[i - 1] == ' ' && wyrazenie[i] == ' ') // wi�cej ni� jedna spacja jest usuwana. 
		{
			wyrazenie.erase(i - 1, 1);
			i--;
		}
		if (wyrazenie[i - 1] == ' ' && wyrazenie[i] >= '!' && wyrazenie[i] <= '/') // spacja przed znakiem przystankowym jest usuwana.
		{
			wyrazenie.erase(i - 1, 1);
			i--;
		}
		if (wyrazenie[i - 1] >= '!' && wyrazenie[i - 1] <= '/' && wyrazenie[i] >= '!' && wyrazenie[i] <= '/') // wi�cej ni� jeden znak przestankowy jest usuwany.
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
