#pragma once
#include <string>

using namespace std;

class CTest {
private:
	int zahl;
	char zeichen;
	string zeichenkette;

public:
	CTest();
	CTest(int zahl, char zeichen, string zeichenkette);
	void set_Value(int zahl, char zeichen, string zeichenkette);
	int get_Value_Int();
	char get_Value_Char();
	string get_Value_String();
};

