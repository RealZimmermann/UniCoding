#include "A.h"
#include <iostream>

using namespace std;

A::A(int zahl) : wert(zahl) {

}

void A::display() const {
	cout << "Klasse A - int Wert: " << wert << endl;
}

A::~A() {

}
