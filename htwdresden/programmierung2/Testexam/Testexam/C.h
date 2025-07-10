#pragma once
#include "A.h"
#include <iostream>

using namespace std;

class C : public A {
private:
	float flieskomma;
public:
	C(int zahl, float flieskomma);
	
	void display() const;

	virtual ~C();
};
