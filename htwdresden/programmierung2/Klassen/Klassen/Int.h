#pragma once

class Int {
private:
	int zahl = 0;
public:
	Int(int zahl);					// Konstruktor
	~Int();							// Destruktor
	void display() const;
	void addiere(int zahl);
	void addiere(const Int& obj);
};

