#include "Box.h"
#include <iostream>
#include <string>

using namespace std;

Box::Box(int alaenge, int abreite, string abezeichnung) {
	if (alaenge < 0) {
		cerr << "Falscher Wert fuer Laenge";
		laenge = 1;
	}

	else laenge = alaenge;

	if (abreite < 0) {
		cerr << "Falscher Wert fuer Breite";
		breite = 1;
	}

	else breite = abreite;

	if (abezeichnung.length() <= 0) {
		cerr << "Keine korrekte Bezeichnung";
		bezeichnung = "Bezeichnung";
	}

	else bezeichnung = abezeichnung;
}

void Box::print() {
	cout << "Die Laenge betraegt " << laenge << endl;
	cout << "Die Breite betraegt " << breite << endl;
	cout << "Der Name lautet " << bezeichnung << endl;
}

void Box::setLaenge(int alaenge) {
	laenge = alaenge;
}

void Box::setBreite(int abreite) {
	breite = abreite;
}

void Box::setBezeichnung(string abezeichnung) {
	bezeichnung = abezeichnung;
}

void Box::calculate() {
	flaeche = laenge * breite;
	cout << "Die Flaeche betraegt " << flaeche << endl;
}

Box::~Box() {

}
