#pragma once
#include "Element.h"

class Warteschlange {
private:
	Element* head;
public:
	Warteschlange();

	void eintreten(int zahl);
	Element* bedienen();

	~Warteschlange();
};
