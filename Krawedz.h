#ifndef Krawedz_H
#define Krawedz_H

#include "Wierzcholek.h"
#include <iostream>

using namespace std;

class Krawedz
{
public:
	Krawedz();
	~Krawedz();
	void setWierzcholekWychodzacy(Wierzcholek);
	void setWierzcholekWchodzacy(Wierzcholek);
	void setMaksymalnaPrzepustowosc(int);
	void setAktualnaPrzepustowosc(int);
	Wierzcholek getWychodzacy();
	Wierzcholek getWchodzacy();
	int getMaksymalnaPrzepustowosc();
	int getAktualnaPrzepustowosc();
	string toString();


private:
	Wierzcholek wychodzacy;
	Wierzcholek wchodzacy;
	int aktualna_przepustowosc;
	int maksymalna_przepustowosc;

};


#endif // !Krawedz_H