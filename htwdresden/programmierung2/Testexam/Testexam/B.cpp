#include "B.h"
#include <iostream>

using namespace std;

B::B(int zahl, char buchstabe) : A(zahl), zeichen(buchstabe) {

}

void B::display() const {
	A::display();
	cout << "Klasse B - char Wert: " << zeichen << endl;
}

B::~B() {

}
