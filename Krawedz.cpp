#include "Krawedz.h"
#include <iostream>
#include <sstream>

Krawedz::Krawedz()
{
	aktualna_przepustowosc = 0;
}

Krawedz::~Krawedz() {}

void Krawedz::setWierzcholekWchodzacy(Wierzcholek w) {
	wchodzacy = w;
}

void Krawedz::setWierzcholekWychodzacy(Wierzcholek w) {
	wychodzacy = w;
}

void Krawedz::setMaksymalnaPrzepustowosc(int max) {
	maksymalna_przepustowosc = max;
}

void Krawedz::setAktualnaPrzepustowosc(int a) {
	aktualna_przepustowosc = a;
}

string Krawedz::toString() {
	stringstream stm;


	stm << getWychodzacy().toString() << " > "
		<< getAktualnaPrzepustowosc() << "/" << getMaksymalnaPrzepustowosc() << " > "
		<< getWchodzacy().toString() << endl;
	return stm.str();
}

Wierzcholek Krawedz::getWchodzacy() {
	return wchodzacy;
}

Wierzcholek Krawedz::getWychodzacy() {
	return wychodzacy;
}

int Krawedz::getMaksymalnaPrzepustowosc() {
	return maksymalna_przepustowosc;
}

int Krawedz::getAktualnaPrzepustowosc() {
	return aktualna_przepustowosc;
}