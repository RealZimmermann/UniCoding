#include "Int.h"

#include <iostream>

using namespace std;

Int::Int(int value) {
	zahl = value;
	cout << "Konstruktoraufruf mit Wert " << zahl << endl;
}

Int::~Int() {
	cout << "Destruktoraufruf mit Wert " << zahl << endl;
}

void Int::display() const {
	cout << "Aktueller mit Wert " << zahl << endl;
}

void Int::addiere(int value) {
	zahl += value;
}

void Int::addiere(const Int& obj) {
	zahl += obj.zahl;
}