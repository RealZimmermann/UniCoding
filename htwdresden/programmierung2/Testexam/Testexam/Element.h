#pragma once

class Element {
private:
	int wert;
public:
	Element* next;
	Element(int wert);
	void display() const;
};
