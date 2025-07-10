#pragma once

class A {
private:
	int wert;

public:
	A(int wert);

	virtual void display() const;

	virtual ~A();
};