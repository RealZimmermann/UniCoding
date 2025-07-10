#pragma once
#include "A.h"

class B : public A {
private:
	char zeichen;

public:
	B(int zahl, char zeichen);
	
	void display() const;

	virtual ~B();
};