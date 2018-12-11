/*
Program do ewidencji samochod�w. Dla ka�dego samochodu program zapami�tuje:
- mark�,
- rok produkcji,
- numer rejestracyjny,
- dane w�a�ciciela,
- od kiedy jest w posiadaniu przez aktualnego w�a�ciciela,
- dane poprzednich w�a�cicieli, w tym dat� nabycia i sprzeda�y auta.
Mo�liwo�ci:
- dodawanie nowych samochod�w,
- edytowanie aktualnych,
- usuwanie aktualnych,
- wyszukiwanie wed�ug r�nych kryteri�w.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <crtdbg.h>
#include <Windows.h>
#include <crtdbg.h>

#include "wlasciciele.h"
#include "samochody.h"
#include "ewidencja.h"

int main(int argc, char * argv[])
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	SetConsoleOutputCP(1250);
	SetConsoleCP(1250);
	_CrtSetDebugFillThreshold(0);
	ewidencja_obsluga();
	return 0;
}
