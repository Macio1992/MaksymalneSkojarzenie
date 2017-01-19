#include "Siec.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

Siec::Siec(int s) {

	size = s;

	graph = new int*[size];
	for (int i = 0; i < size; i++)
		graph[i] = new int[size];

	c = new int[size];

	visited = new bool[wierzcholki.size()];
	for (int i = 0; i < wierzcholki.size(); i++) visited[i] = false;

}

Siec::~Siec() {}

bool Siec::sprawdzCzyWierzcholekIstnieje(Wierzcholek w) {

	auto it = find(wierzcholki.begin(), wierzcholki.end(), Wierzcholek(w.getName()));

	return (it != wierzcholki.end()) ? true : false;

}

int Siec::getIndeksWierzcholka(char w) {
	auto it = find(wierzcholki.begin(), wierzcholki.end(), Wierzcholek(w));

	return distance(wierzcholki.begin(), it);
}


void Siec::wypisz() {

	for (size_t i = 0; i < krawedzie.size(); i++)
		cout << krawedzie[i].toString();
	cout << endl;

}

bool Siec::sprawdzCzyJestDrogaOdZrodlaDoUjscia() {

	queue<Wierzcholek> queue;
	Wierzcholek temp = getZrodlo();
	bool *v = new bool[wierzcholki.size()];
	for (int i = 0; i < wierzcholki.size(); i++) v[i] = false;

	queue.push(temp);

	while (!queue.empty()) {
		temp = queue.front();
		queue.pop();
		v[getIndeksWierzcholka(temp.getName())] = true;
		for (int i = 0; i < krawedzie.size(); i++) {
			if (krawedzie[i].getWychodzacy().getName() == temp.getName() && !v[getIndeksWierzcholka(krawedzie[i].getWchodzacy().getName())]) {

				queue.push(krawedzie[i].getWchodzacy());
				v[getIndeksWierzcholka(krawedzie[i].getWchodzacy().getName())] = true;
			}
		}
	}

	return v[getIndeksWierzcholka(getUjscie().getName())] ? true : false;
}

Wierzcholek Siec::getUjscie() {

	return wierzcholki[wierzcholki.size()-1];
}

Wierzcholek Siec::getZrodlo() {
	return wierzcholki[0];
}

Wierzcholek Siec::cechowanie(Wierzcholek temp) {

	Wierzcholek pom;
	queue<Wierzcholek> queue;
	for (int i = 0; i < wierzcholki.size(); i++) visited[i] = false;

	queue.push(temp);

	while (!queue.empty()) {
		temp = queue.front();
		queue.pop();
		visited[getIndeksWierzcholka(temp.getName())] = true;

		for (int i = 0; i < krawedzie.size(); i++) {
			if (krawedzie[i].getWychodzacy().getName() == temp.getName() && sprawdzCzyMaGdzieIsc(temp) && !visited[getIndeksWierzcholka(krawedzie[i].getWchodzacy().getName())] && krawedzie[i].getAktualnaPrzepustowosc() != krawedzie[i].getMaksymalnaPrzepustowosc()) {
				queue.push(krawedzie[i].getWchodzacy());
				visited[getIndeksWierzcholka(krawedzie[i].getWchodzacy().getName())] = true;
				pom = krawedzie[i].getWchodzacy();
				pom.setCecha(krawedzie[i].getWychodzacy().getName());
				pom.setZnakCechy('+');
				pom.setWartoscCechy(min(krawedzie[i].getWychodzacy().getWartoscCechy(), (krawedzie[i].getMaksymalnaPrzepustowosc() - krawedzie[i].getAktualnaPrzepustowosc())));
				krawedzie[i].setWierzcholekWchodzacy(pom);
				for (int k = 0; k < krawedzie.size(); k++) {
					if (krawedzie[k].getWchodzacy().getName() == pom.getName())
						krawedzie[k].setWierzcholekWchodzacy(pom);
					if (krawedzie[k].getWychodzacy().getName() == pom.getName())
						krawedzie[k].setWierzcholekWychodzacy(pom);
				}
			}
		}

	}
	
	return pom;
}

void Siec::przeplyw(Wierzcholek temp) {

	if (temp.getName() == getUjscie().getName()) {
		int przep = temp.getWartoscCechy();
		while (temp.getName() != getZrodlo().getName()) {
			if (temp.getZnakCechy() == '+') {
				for (int i = 0; i < krawedzie.size(); i++) {
					if (krawedzie[i].getWychodzacy().getName() == temp.getCecha() && krawedzie[i].getWchodzacy().getName() == temp.getName()) {
						krawedzie[i].setAktualnaPrzepustowosc(krawedzie[i].getAktualnaPrzepustowosc() + przep);
						temp = krawedzie[i].getWychodzacy();
						krawedzie[i].setWierzcholekWychodzacy(temp);
					}
				}
			}
			else if (temp.getZnakCechy() == '-') {
				for (int i = 0; i < krawedzie.size(); i++) {
					if (krawedzie[i].getWychodzacy().getName() == temp.getName() && krawedzie[i].getWchodzacy() == temp.getCecha()) {
						temp = krawedzie[i].getWchodzacy();
						krawedzie[i].setAktualnaPrzepustowosc(krawedzie[i].getAktualnaPrzepustowosc() - przep);
						krawedzie[i].setWierzcholekWchodzacy(temp);
					}
				}
			}
		}
	}
}

void Siec::minimalnyPrzekroj() {
	cout << "Minimalny przekroj:" << endl;
	cout << "{" << endl;

	int przeplyw = 0;

	for (int i = 0; i < krawedzie.size(); i++)
		if (krawedzie[i].getWychodzacy().getZnakCechy() != ' ' && krawedzie[i].getAktualnaPrzepustowosc() == krawedzie[i].getMaksymalnaPrzepustowosc()) {
			cout << "   (" << krawedzie[i].getWychodzacy().getName() << "," << krawedzie[i].getWchodzacy().getName() << ")" << endl;
			przeplyw += krawedzie[i].getAktualnaPrzepustowosc();
		}

	cout << "}" << endl;

	cout << "Wartosc maksymalnego przeplyw: " << przeplyw << endl;
}

void Siec::wyczyscKrawedzie() {
	Wierzcholek temp;

	for (int i = 0; i < krawedzie.size(); i++) {
		if (krawedzie[i].getWychodzacy().getName() != getZrodlo().getName()) {
			temp = krawedzie[i].getWchodzacy();
			temp.setCecha(' ');
			temp.setZnakCechy(' ');
			temp.setWartoscCechy(0);
			krawedzie[i].setWierzcholekWchodzacy(temp);
			temp = krawedzie[i].getWychodzacy();
			temp.setCecha(' ');
			temp.setZnakCechy(' ');
			temp.setWartoscCechy(0);
			krawedzie[i].setWierzcholekWychodzacy(temp);
		}
		else {
			temp = krawedzie[i].getWchodzacy();
			temp.setCecha(' ');
			temp.setZnakCechy(' ');
			temp.setWartoscCechy(0);
			krawedzie[i].setWierzcholekWchodzacy(temp);
			temp = krawedzie[i].getWychodzacy();
			krawedzie[i].setWierzcholekWychodzacy(temp);
		}

	}

}

bool Siec::sprawdzCzyMaGdzieIsc(Wierzcholek temp) {
	int l = 0, l2 = 0;

	//sprawdz ile jest krawedzi z wierzcholkiem wychodzacym temp
	for (int i = 0; i < krawedzie.size(); i++)
		if (krawedzie[i].getWychodzacy().getName() == temp.getName())
			l++;

	for (int i = 0; i < krawedzie.size(); i++)
		if (krawedzie[i].getWychodzacy().getName() == temp.getName() && krawedzie[i].getAktualnaPrzepustowosc() == krawedzie[i].getMaksymalnaPrzepustowosc())
			l2++;

	return (l == l2) ? false : true;

}

bool Siec::sprawdzCzyGrafDwudzielny() {
	
	c = new int[size];
	for (int i = 0; i < size; i++) c[i] = 0;

	queue<int> queue;

	bool war = true;

	int i = 0;
	while (i < size) {

		if (c[i] != 0)
			i++;
		else {
			c[i] = 1;
			queue.push(i);
		}

		while (!queue.empty()) {
			int v = queue.front();
			queue.pop();
			for (int u = 0; u < size; u++) {
				if (graph[v][u] != 0) {
					if (c[u] == c[v])
						war = false;
					
					if (c[u] != 0)
						u++;
					else {
						c[u] = -c[v];
						queue.push(u);
					}
				}
			}
		}

	}

	

	return war;
}

void Siec::algorithm() {

	if (sprawdzCzyGrafDwudzielny()) {

		Wierzcholek temp;
		temp.setName('s');
		temp.setZnakCechy('-');
		temp.setCecha('s');
		temp.setWartoscCechy(100000);
		wierzcholki.push_back(temp);

		//Uzupelnianie wierzcholkow
		for (int i = 0; i < size; i++) {
			if (c[i] == 1) {
				
				temp.setName((char)(i + '0'));
				temp.setZnakCechy(' ');
				temp.setCecha(' ');
				temp.setWartoscCechy(0);
				wierzcholki.push_back(temp);
			}
		}

		for (int i = 0; i < size; i++) {
			if (c[i] == -1) {
				temp.setName((char)(i + '0'));
				temp.setZnakCechy(' ');
				temp.setCecha(' ');
				temp.setWartoscCechy(0);
				wierzcholki.push_back(temp);
			}
		}

		Krawedz k;
		k.setWierzcholekWychodzacy(wierzcholki[0]);
		//Uzupelnianie krawedzi ze zrodla
		for (int i = 0; i < size; i++) {
			if (c[i] == 1) {
				k.setWierzcholekWchodzacy(wierzcholki[getIndeksWierzcholka((char)(i + '0'))]);
				k.setAktualnaPrzepustowosc(0);
				k.setMaksymalnaPrzepustowosc(1);
				krawedzie.push_back(k);
			}
		}

		//uzupelnienie krawedzi srodkowych
		for (int i = 0; i < size; i++) {
			if (c[i] == 1) {
				k.setWierzcholekWychodzacy(wierzcholki[getIndeksWierzcholka((char)(i + '0'))]);
				for (int j = 0; j < size; j++) {
					if (graph[i][j] != 0) {
						k.setWierzcholekWchodzacy(wierzcholki[getIndeksWierzcholka((char)(j + '0'))]);
						krawedzie.push_back(k);
					}
				}
			}
		}

		//uzupelnianie krawedzi do ujscia
		temp.setName('t');
		temp.setZnakCechy(' ');
		temp.setCecha(' ');
		temp.setWartoscCechy(0);
		wierzcholki.push_back(temp);
		k.setWierzcholekWchodzacy(wierzcholki[wierzcholki.size() - 1]);
		for (int i = 0; i < size; i++) {
			if (c[i] == -1) {
				k.setWierzcholekWychodzacy(wierzcholki[getIndeksWierzcholka((char)(i + '0'))]);
				k.setAktualnaPrzepustowosc(0);
				k.setMaksymalnaPrzepustowosc(1);
				krawedzie.push_back(k);
			}
		}

		Wierzcholek beg = getZrodlo();

		beg.setWartoscCechy(1000);

		do {
			temp = cechowanie(beg);
			przeplyw(temp);
			if (visited[getIndeksWierzcholka(getUjscie().getName())]) {
				wypisz();
				wyczyscKrawedzie();
			}
				
		} while (visited[getIndeksWierzcholka(getUjscie().getName())]);

		cout << "Maksymalne skojarzenie: " << endl;
		for (int i = 0; i < krawedzie.size(); i++) {
			if (krawedzie[i].getAktualnaPrzepustowosc() == 1 && krawedzie[i].getWychodzacy().getName() != getZrodlo().getName() && krawedzie[i].getWchodzacy().getName() != getUjscie().getName()) {
				cout << "{" << krawedzie[i].getWychodzacy().getName() << "," << krawedzie[i].getWchodzacy().getName() << "}"<< endl;
			}
		}

	} 
	else cout << "Nie jest dwudzielny" << endl;

}

void Siec::uzupelnijGraf() {

	ifstream plik("graf.txt");

	if (!plik) {
		cout << "Blad podczas otwierania pliku graf.txt" << endl;
		exit(0);
	}

	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			graph[i][j] = 0;

	int a, b;
	while (plik >> a >> b) {
		graph[a][b] = 1;
		graph[b][a] = 1;
	}

}