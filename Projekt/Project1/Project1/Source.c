/*
Program do ewidencji samochodów. Dla ka¿dego samochodu program zapamiêtuje:
- markê,
- rok produkcji,
- numer rejestracyjny,
- dane w³aœciciela,
- od kiedy jest w posiadaniu przez aktualnego w³aœciciela,
- dane poprzednich w³aœcicieli, w tym datê nabycia i sprzeda¿y auta.
Mo¿liwoœci:
- dodawanie nowych samochodów,
- edytowanie aktualnych,
- usuwanie aktualnych,
- wyszukiwanie wed³ug ró¿nych kryteriów.*/

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
