#ifndef Siec_H
#define Siec_H

#include "Krawedz.h"
#include "Wierzcholek.h"
#include <vector>
#include <deque>

using namespace std;

class Siec
{
public:
	Siec(int);
	~Siec();
	bool sprawdzCzyWierzcholekIstnieje(Wierzcholek);
	void wypisz();
	int getIndeksWierzcholka(char w);
	Wierzcholek getUjscie();
	Wierzcholek getZrodlo();
	bool sprawdzCzyJestDrogaOdZrodlaDoUjscia();
	void algorithm();
	Wierzcholek cechowanie(Wierzcholek);
	void przeplyw(Wierzcholek);
	void minimalnyPrzekroj();
	void wyczyscKrawedzie();
	bool sprawdzCzyMaGdzieIsc(Wierzcholek);
	
	
	bool sprawdzCzyGrafDwudzielny();
	void uzupelnijGraf();

private:
	vector<Wierzcholek> wierzcholki;
	vector<Krawedz> krawedzie;
	char zrodlo;
	char ujscie;
	bool *visited;
	int **graph;
	int size;
	int *c;
};

#endif // !Siec_H