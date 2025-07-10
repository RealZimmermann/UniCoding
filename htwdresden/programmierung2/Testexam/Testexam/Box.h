#pragma once
#include <string>

using namespace std;

class Box {
private:
	int laenge;
	int breite;
	string bezeichnung;
	int flaeche;

public:
	Box(int laenge, int breite, string bezeichnung);
	
	void print();
	void setLaenge(int laenge);
	void setBreite(int breite);
	void setBezeichnung(string bezeichnung);
	void calculate();

	~Box();
};
