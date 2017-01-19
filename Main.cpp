#include <iostream>
#include <fstream>
#include "Siec.h"
#include <vector>

using namespace std;

int main() {

	Siec siec(10);
	siec.uzupelnijGraf();
	//siec.wypisz();

	siec.algorithm();


	system("PAUSE");
	return 0;
}