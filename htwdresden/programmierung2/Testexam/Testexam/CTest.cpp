#include "CTest.h"
#include <iostream>
#include <string>

using namespace std;

CTest::CTest() {
	cout << "Erster Konstruktor aufgerufen" << endl;
	zahl = 0;
	zeichen = ' ';
	zeichenkette = " ";
}

CTest::CTest(int nummer, char buchstabe, string wort) {
	cout << "\nZweiter Konstruktor aufgerufen" << endl;
	zahl = nummer;
	zeichen = buchstabe;
	zeichenkette = wort;
}

void CTest::set_Value(int nummer, char buchstabe, string wort) {
	if (nummer <= -10 || nummer >= 10) {
		cerr << "Die Zahl liegt ausserhalb des erlaubten Zahlenbereiches" << endl;
		zahl = 0;
	}

	else {
		zahl = nummer;
	}

	if (int(buchstabe) <= 65 || int(buchstabe) >= 90 || int(buchstabe) == 32) {
		cerr << "Das Zeichen liegt ausserhalb des erlaubten Bereiches" << endl;
		zeichen = ' ';
	}

	else {
		zeichen = buchstabe;
	}

	if (wort.length() > 10) {
		cerr << "Die Zeichenkette hat zu viele Buchstaben" << endl;
		zeichenkette = " ";
	}

	else {
		zeichenkette = wort;
	}

}

int CTest::get_Value_Int() {
	return zahl;
}

char CTest::get_Value_Char() {
	return zeichen;
}

string CTest::get_Value_String() {
	return zeichenkette;
}
