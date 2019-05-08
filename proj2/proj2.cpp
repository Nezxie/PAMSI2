// proj2.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include <ctime>
using namespace std;
class Graf
{
public:
	const int MAX = 2147483647; //nieskonczonosc
	int ile_krawedzie;
	int ile_wierzcholki;
	int wierzcholek_start;
	int *tab_kosztow;
	int *tab_poprzednikow;
	int *stos;
	int indeks_stosu;
	bool *tab_odwiedzone;
	int tmp; //do algorytmu dikstry zmienna tymczasowa
	
	
};

class Graf_T
		:public Graf
{
public:
	int **T;
	void Utworz()
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
	void Wyswietl(int ile_wierzcholki)
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
		wynik.open("graf.txt", ios::out | ios::app); //zapisywanie|dopisywanie do nastepnej lini (bez kasowania)
		for (int i = 0; i < ile_wierzcholki; i++)
		{
			for (int j = 0; j < ile_wierzcholki; j++)
			{
				wynik<<T[i][j] << " ";
			}
			wynik << endl;
		}
		wynik << endl << endl;
		wynik.close();
	}

	void Dikstra(ofstream &wynik)
	{
		tab_kosztow = new int[ile_wierzcholki];
		tab_poprzednikow = new int[ile_wierzcholki];
		tab_odwiedzone = new bool[ile_wierzcholki];
		stos = new int[ile_wierzcholki]; //implementacja stosu na tablicy
		indeks_stosu = 0;

		for (int i = 0; i < ile_wierzcholki; i++)
		{
			tab_kosztow[i] = MAX;
			tab_poprzednikow[i] = -1; //liczba ktora na pewno nie jest indeksem wierzcholka
			tab_odwiedzone[i] = false;
		}
		tab_kosztow[wierzcholek_start] = 0; //wierzcholek od ktorego zaczynamy nie ma kosztu
		for (int i = 0; i < ile_wierzcholki; i++)
		{
			int j = 0;
			for (tmp = j++; j < ile_wierzcholki; j++)
			{
				if (!tab_odwiedzone[j] && (tab_kosztow[j] < tab_kosztow[tmp])) //nie bylismy w tym wierzcholku i koszt wczesniej mniejszy niz pozniej
				{
					tmp = j; //zapamietujemy indeks - wierzcholek o najnizszym koszcie
				}
			}
			tab_odwiedzone[tmp] = true; //tu juz bylismy

			for (int ii=0;ii<ile_wierzcholki;ii++)
			{
				if (!tab_odwiedzone[ii] && T[tmp][ii]!=0 && tab_kosztow[ii] > tab_kosztow[tmp] + T[tmp][ii]) //czy sasiad byl odwiedzony i czy jego koszt wiekszy od sprawdzanego
				{
					tab_kosztow[ii] = tab_kosztow[tmp]+T[tmp][ii]; //zamieniamy na znaleziony mniejszy koszt
					tab_poprzednikow[ii] = tmp; //zamieniamy na lepszego znalezionego poprzednika ktory jest po drodze o tanszym koszcie
				}
			}
		}
		Dikstra_zapis(wynik, stos, indeks_stosu, tab_kosztow, tab_poprzednikow);
	}
	void Dikstra_zapis(ofstream &wynik, int stos[], int indeks_stosu, int tab_kosztow[], int tab_poprzednikow[])
	{
		wynik.open("rozwiazanie.txt", ios::out | ios::app);
			for (int i = 0; i < ile_wierzcholki; i++)
			{
				wynik << "Wierzcholek nr " << i << ":   ";
				for (int j = i; j > -1; j = tab_poprzednikow[j]) //sprawdza na ktorym elemencie jestesmy i wyrzuca jak na pierwszym
				{
					stos[indeks_stosu++] = j; //zapisuje sciezke od tylu
				}
				while (indeks_stosu) //az stos bedzie pusty
				{
					wynik << stos[--indeks_stosu] << "  "; //po koleji zdejmujemy ze stosu

				}
				wynik << "koszt sciezki: " << tab_kosztow[i] << endl;
			}
		wynik << endl << endl;
		wynik.close();
	}
	
};


class Graf_L
	:public Graf
{
public:
	struct lista //struktura listy
	{
		lista *next; //wskaznik na nastepny element
		int index;
		int waga;
	};
	lista **L;
	lista *wsk; //wskaznik pomocniczy na element z listy
	void Utworz()
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
				cout << wsk->index << " waga: " << wsk->waga<<" ";
				wsk = wsk->next;
			}
			cout << endl;
		}
	}
	void Zapisz(ofstream &wynik)
	{
		wynik.open("graf.txt", ios::out | ios::app);
		for (int i = 0; i < ile_wierzcholki; i++)
		{
			wynik << "L [" << i << "] = ";
			wsk = L[i];
			while (wsk) //bo jak nie bedzie wiecej sasiadow to bedzie null
			{
				wynik << wsk->index << " waga: " << wsk->waga <<" ";
				wsk = wsk->next;
			}
			wynik << endl;
		}
		wynik << endl << endl;
		wynik.close();
	}
	void Dikstra(ofstream &wynik)
	{
		tab_kosztow = new int[ile_wierzcholki];
		tab_poprzednikow = new int[ile_wierzcholki];
		tab_odwiedzone = new bool[ile_wierzcholki];
		stos = new int[ile_wierzcholki]; //implementacja stosu na tablicy
		indeks_stosu = 0;

		for (int i = 0; i < ile_wierzcholki; i++)
		{
			tab_kosztow[i] = MAX;
			tab_poprzednikow[i] = -1; //liczba ktora na pewno nie jest indeksem wierzcholka
			tab_odwiedzone[i] = false;
		}
		tab_kosztow[wierzcholek_start] = 0; //wierzcholek od ktorego zaczynamy nie ma kosztu
		for (int i = 0; i < ile_wierzcholki; i++)
		{
			int j = 0;
			for (tmp = j++; j < ile_wierzcholki; j++)
			{
				if (!tab_odwiedzone[j] && (tab_kosztow[j] < tab_kosztow[tmp])) //nie bylismy w tym wierzcholku i koszt wczesniej mniejszy niz pozniej
				{
					tmp = j; //zapamietujemy indeks - wierzcholek o najnizszym koszcie
				}
			}
			tab_odwiedzone[tmp] = true; //tu juz bylismy

			for (wsk = L[tmp]; wsk; wsk = wsk->next) //wybieramy dana liste sasiadow; dopoki nie null; wskaznik na nastepnego sasiada
			{
				if (!tab_odwiedzone[wsk->index] && tab_kosztow[wsk->index] > tab_kosztow[tmp] + wsk->waga) //czy sasiad byl odwiedzony i czy jego koszt wiekszy od sprawdzanego
				{
					tab_kosztow[wsk->index] = tab_kosztow[tmp] + wsk->waga; //zamieniamy na znaleziony mniejszy koszt
					tab_poprzednikow[wsk->index] = tmp; //zamieniamy na lepszego znalezionego poprzednika ktory jest po drodze o tanszym koszcie
				}
			}
		}
		Dikstra_zapis(wynik, stos, indeks_stosu, tab_kosztow, tab_poprzednikow);
	}
	void Dikstra_zapis(ofstream &wynik, int stos[], int indeks_stosu, int tab_kosztow[], int tab_poprzednikow[])
	{
		wynik.open("rozwiazanie.txt", ios::out | ios::app);
			for (int i = 0; i < ile_wierzcholki; i++)
			{
				wynik << "Wierzcholek nr " << i << ":   ";
				for (int j = i; j > -1; j = tab_poprzednikow[j]) //sprawdza na ktorym elemencie jestesmy i wyrzuca jak na pierwszym
				{
					stos[indeks_stosu++] = j; //zapisuje sciezke od tylu
				}
				while (indeks_stosu) //az stos bedzie pusty
				{
					wynik << stos[--indeks_stosu] << "  "; //po koleji zdejmujemy ze stosu

				}
				wynik << "koszt sciezki: " << tab_kosztow[i] << endl;
			}
		wynik << endl << endl;
		wynik.close();
	}

};
void Wczytaj_z_pliku(Graf_L graf[], int i)
{
	int poczatek;
	int koniec;
	int waga;
	fstream plik;
	plik.open("tmp.txt", ios::in);
	plik >> graf[i].ile_krawedzie >> graf[i].ile_wierzcholki >> graf[i].wierzcholek_start;
	graf[i].Utworz();
	for (int j = 0; j < graf[i].ile_krawedzie; j++)
	{
		plik >> poczatek >> koniec >> waga;
		graf[i].Dodaj_krawedz(poczatek, koniec, waga);
	}
	plik.close();
	remove("tmp.txt");
}
void Wczytaj_z_pliku(Graf_T graf[], int i)
{
	int poczatek;
	int koniec;
	int waga;
	fstream plik;
	plik.open("tmp.txt", ios::in);
	plik >> graf[i].ile_krawedzie >> graf[i].ile_wierzcholki >> graf[i].wierzcholek_start;
	graf[i].Utworz();
	for (int j = 0; j < graf[i].ile_krawedzie; j++)
	{
		plik >> poczatek >> koniec >> waga;
		graf[i].Dodaj_krawedz(poczatek, koniec, waga);
	}
	plik.close();
	remove("tmp.txt");
}
bool Sprawdz(int temp, int tab[], int licznik)
{
	int i = 0;
	if (licznik <= 0)
	{
		return false;
	}
	
	do
	{
		if (tab[i] == temp)
		{
			return true;
	
		}
		i++;
	} while (i < licznik);
		return false;
}
void Stworz_plik(int krawedzie, int wierzcholki)
{
	int Wpocz; //wierzcholek poczatkowy
	int Wkon; //wierzcholek z nim polaczony kraweedzia
	int pierwszy = rand() % wierzcholki;
	int *tab = new int[krawedzie];
	int temp;
	int i = 0;
	ofstream plik("tmp.txt");
	plik << krawedzie << " " << wierzcholki << " " << pierwszy << endl;
	while (i < krawedzie)
	{
		Wpocz = rand() % wierzcholki;
		Wkon = rand() % wierzcholki;
		if (Wpocz != Wkon)
		{
			temp = Wpocz * 1000 + Wkon; //zapisanie pary jako jedna liczba, liczba wierzcholkow nie moze przekraczac 1000
			if (Sprawdz(temp, tab, i) == false)
			{
				plik << Wpocz << " " << Wkon << " " << rand() % 1000 + 1 << endl; //wpisanie do pliku i wylosowanie wagi z przedzialu 1-1000
				tab[i] = temp;
				i++;
			}
		}
	}
	
};
void korekta(ofstream &wynik, ofstream &graf) //rozwiazuje problem usuwajacej sie pierwszej linijki w plikach
{
	wynik.open("wynik.txt");
	wynik << "." << endl;
	wynik.close();
	graf.open("rozwiazanie.txt");
	graf << "." << endl;
	graf.close();
}

int main()
{
	clock_t start;
	double czas;
	srand(time(NULL)); //zegar do losowania zalezny od godziny na komputerze ze by nie byly caly czas takie same grafy
	double wypelnienie=1; //od 0 do 1 gdzie 1 to 100%
	int wierzcholki=10;
	int krawedzie=(int)((wierzcholki*(wierzcholki-1))*wypelnienie); //nie jest /2 bo sa kierunkowe krawedzie (dwa razy wiecej)
	int pierwszy=5; //od 0 do wierzcholki-1;
	int ilosc = 2; //ile grafow generujemy
	fstream plik;
	ofstream graf("graf.txt");
	ofstream wynik("rozwiazanie.txt");
	Graf_L *Graf = new Graf_L[ilosc];  //wybor typu grafu
	//Graf_T *Graf = new Graf_T[ilosc];
	korekta(wynik, graf);
	for (int i = 0; i < ilosc; i++)
	{
		Stworz_plik(krawedzie, wierzcholki);
		Wczytaj_z_pliku(Graf, i); 
		Graf[i].Zapisz(wynik);
	}
	start = clock();
	for (int i = 0; i < ilosc; i++)
	{
		Graf[i].Dikstra(wynik);
		
	}
	czas = (clock() - start) / (double)CLOCKS_PER_SEC;
	cout << "czas dzialania:   " << czas << " s" << endl;
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
