#include "C.h"
#include <iostream>

using namespace std;

C::C(int zahl, float flies) : A(zahl), flieskomma(flies) {

}

void C::display() const {
	A::display();
	cout << "Klasse C - float Wert: " << flieskomma << endl;
}

C::~C() {

}
