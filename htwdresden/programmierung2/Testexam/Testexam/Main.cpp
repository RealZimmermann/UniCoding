#include "CTest.h"
#include "A.h"
#include "B.h"
#include "C.h"
#include "Box.h"
#include "Element.h"
#include "Warteschlange.h"
#include <iostream>
#include <string>

using namespace std;

int main() {
	cout << "=== Aufgabe 1 ===" << endl;
	
	CTest test1;

	int nummer = test1.get_Value_Int();
	cout << nummer << endl;

	char buchstabe = test1.get_Value_Char();
	cout << buchstabe << endl;

	string wort = test1.get_Value_String();
	cout << wort << endl << endl;
	
	CTest test2(1, 'A', "Moin");

	nummer = test2.get_Value_Int();
	cout << nummer << endl;

	buchstabe = test2.get_Value_Char();
	cout << buchstabe << endl;

	wort = test2.get_Value_String();
	cout << wort << endl << endl;

	test2.set_Value(20, 'd', "GutenMorgen");
	nummer = test2.get_Value_Int();
	cout << nummer << endl;

	buchstabe = test2.get_Value_Char();
	cout << buchstabe << endl;

	wort = test2.get_Value_String();
	cout << wort << endl << endl;

	
	cout << "\n=== Aufgabe 2 ===" << endl;
	A erster(3);
	erster.display();

	B zweiter(3, 'A');
	zweiter.display();

	C dritter(3, 3.1);
	dritter.display();

	// --- Demonstration von Polymorphie ---
	cout << "\n--- Polymorphe Aufrufe von display() mit Zeigern ---" << endl;

	A* zeiger1 = new A(100);
	A* zeiger2 = new B(200, 'Y'); // Ein A-Zeiger, der auf ein B-Objekt zeigt
	A* zeiger3 = new C(300, 2.718f); // Ein A-Zeiger, der auf ein C-Objekt zeigt

	cout << "Aufruf display() ueber A-Zeiger (zeiger1 -> A-Objekt):" << endl;
	zeiger1->display(); // Ruft A::display() auf

	cout << "\nAufruf display() ueber A-Zeiger (zeiger2 -> B-Objekt):" << endl;
	zeiger2->display(); // Ruft B::display() auf (polymorphisch)

	cout << "\nAufruf display() ueber A-Zeiger (zeiger3 -> C-Objekt):" << endl;
	zeiger3->display(); // Ruft C::display() auf (polymorphisch)

	cout << "\n=== Aufgabe 3 ===" << endl;
	Box ersteBox(3, 7, "Servus");
	ersteBox.print();
	ersteBox.setLaenge(4);
	ersteBox.print();
	ersteBox.setBreite(8);
	ersteBox.print();
	ersteBox.setBezeichnung("Moin");
	ersteBox.print();
	ersteBox.calculate();

	cout << "\n=== Aufgabe 3 ===" << endl;
	Element eins(5);
	eins.display();

	Warteschlange q;
	q.eintreten(10);
	q.eintreten(20);
	q.eintreten(30);

	for (int i = 0; i < 3; i++)	{
		Element* e = q.bedienen();
		if (e) { 
			e->display(); 
			cout << '\n'; 
			delete e; 
		}
	}
	return 0;
}
