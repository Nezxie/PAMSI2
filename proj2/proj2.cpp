// proj2.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include "pch.h"
#include <iostream>
#include <fstream>

class Graf
{
public:
	int ile_krawedzie;
	int ile_wierzcholki;
	int wierzcholek_start;
};

class Graf_T
		:public Graf
{
public:
	int **T;
	void Utwórz_M()
	{
		T = new int *[ile_wierzcholki];
			for (int i = 0; i < ile_wierzcholki; i++)
			{
				T[i] = new int[ile_wierzcholki];
			}
			for (int i = 0; i < ile_wierzcholki; i++)
			{
				for (int j = 0; j < ile_wierzcholki; j++)
				{
					T[i][j] = 0;
				}
			}
	}
	void Dodaj_krawedz(int poczatek, int koniec, int waga)
	{
		T[poczatek][koniec] = waga;
	}
	void Wyswietl(ile_wierzcholki)
	{
		for (int i = 0; i < ile_wierzcholki; i++)
		{
			for (int j = 0; j < ile_wierzcholki; j++)
			{
				cout<<T[i][j]<<endl;
			}
		}
	}
	void Zapisz(ofstream &wynik) //o do zapisu
	{
		wynik.open("graf.txt", iso::out | iso::app); //zapisywanie|dopisywanie do nastepnej lini (bez kasowania)
		for (int i = 0; i < ile_wierzcholki; i++)
		{
			for (int j = 0; j < ile_wierzcholki; j++)
			{
				wynik<<T[i][j] << endl;;
			}
		}
		wynik << endl << endl;
		wynik.close();
	}
};

class Graf_L
	:public Graf
{
	struct lista //struktura listy
	{
		lista *next; //wskaznik na nastepny element
		int index;
		int waga;
	};
	lista **L;
	lista *wsk; //wskaznik pomocniczy na element z listy
	void Utworz_L()
	{
		L = new lista *[ile_wierzcholki]; //L to tablica list
		for (int i = 0; i < ile_wierzcholki; i++)
		{
			L[i] = NULL;
		}
	}
	void Dodaj_krawedz(int poczatek, int koniec, int waga)
	{
		wsk = new lista; //przypisujemy liste do wsk
		wsk->index = koniec;
		wsk->waga = waga;
		wsk->next = L[poczatek]; //przechodzenie z listy do listy (wskazywanie na nastepna liste)
		L[poczatek] = wsk;
	}
	void Wyswietl()
	{
		for (int i=0; i < ile_wierzcholki; i++)
		{
			cout << "L [" << i << "] = ";
			wsk = L[i];
			while (wsk) //bo jak nie bedzie wiecej sasiadow to bedzie null
			{
				cout << wsk->index << " waga: " << wsk->waga;
				wsk = wsk->next;
			}
			cout << endl;
		}
	}
	void Zapisz(ofstream &wynik)
	{
		wynik.open("graf.txt", iso::out | iso::app);
		for (int i = 0; i < ile_wierzcholki; i++)
		{
			wynik << "L [" << i << "] = ";
			wsk = L[i];
			while (wsk) //bo jak nie bedzie wiecej sasiadow to bedzie null
			{
				wynik << wsk->index << " waga: " << wsk->waga;
				wsk = wsk->next;
			}
			wynik << endl;
		}
		wynik << endl << endl;
		wynik.close();
	}
};

int main()
{
    std::cout << "Hello World!\n"; 
}

// Uruchomienie programu: Ctrl + F5 lub menu Debugowanie > Uruchom bez debugowania
// Debugowanie programu: F5 lub menu Debugowanie > Rozpocznij debugowanie

// Porady dotyczące rozpoczynania pracy:
//   1. Użyj okna Eksploratora rozwiązań, aby dodać pliki i zarządzać nimi
//   2. Użyj okna programu Team Explorer, aby nawiązać połączenie z kontrolą źródła
//   3. Użyj okna Dane wyjściowe, aby sprawdzić dane wyjściowe kompilacji i inne komunikaty
//   4. Użyj okna Lista błędów, aby zobaczyć błędy
//   5. Wybierz pozycję Projekt > Dodaj nowy element, aby utworzyć nowe pliki kodu, lub wybierz pozycję Projekt > Dodaj istniejący element, aby dodać istniejące pliku kodu do projektu
//   6. Aby w przyszłości ponownie otworzyć ten projekt, przejdź do pozycji Plik > Otwórz > Projekt i wybierz plik sln
