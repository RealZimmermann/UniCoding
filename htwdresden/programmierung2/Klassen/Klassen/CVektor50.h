#pragma once

class CVektor50 {
private:
	int elemente[50];
	int anzahlElemente;

public:
	CVektor50();
	CVektor50(int anz);
	~CVektor50();
	void sortiere();
	void add(int position, int wert);
	void remove(int position);
	void display() const;
	int getAnzahlElemente() const;

};
