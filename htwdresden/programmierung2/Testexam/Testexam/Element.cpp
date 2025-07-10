#pragma once
#include "Element.h"
#include <iostream>

using namespace std;

Element::Element(int awert) : wert(awert), next(nullptr) {}

void Element::display() const {
	cout << "Das Element hat den Wert " << wert << endl;
}