#include "Int.h"
#include "CVektor50.h"

#include <iostream>

using namespace std;

void myfunc() {
    cout << "** erste Anweisung in myfunc\n";
    Int i(10);                                              // Lokales Objekt
    static Int j(11);                                       // Statisches Objekt (bleibt bis Programmende erhalten)
    cout << "** letzte Anweisung in myfunc\n";
}

Int a(0);                                                   // Globales Objekt

int main() {
    cout << "=== Aufgabe 1 ===" << endl;
    Int x(1);                                               // Lokales Objekt

    cout << "** in main: zum ersten Mal\n";
    myfunc();

    cout << "** in main: zum zweiten Mal\n";
    myfunc();

    cout << "** letzte Anweisung in main\n";

    // Test der addiere-Funktion
    Int o(5), n(10);
    o.addiere(10);                                          // einfache Addition
    o.display();

    o.addiere(n);                                           // Überladene Methode: Objekt + Objekt
    o.display();

    cout << "\n=== Aufgabe 2 ===" << endl;
    cout << "Test des Standardkonstruktors:" << endl;
    CVektor50 meinVektor1;
    meinVektor1.display();

    cout << "\nTest des Konstruktors mit Parameter:" << endl;
    CVektor50 meinVektor2(5);
    meinVektor2.display();

    cout << "\nTest der Sortiermethode:" << endl;
    meinVektor2.sortiere();
    meinVektor2.display();

    cout << "\nTest der Einfüge-Methode:" << endl;
    meinVektor2.add(2, 99);
    meinVektor2.display();
    meinVektor2.add(0, 10);
    meinVektor2.display();
    meinVektor2.add(meinVektor2.getAnzahlElemente(), 5);
    meinVektor2.display();

    cout << "\nTest der Loesch-Methode:" << endl;
    meinVektor2.remove(3);
    meinVektor2.display();
    meinVektor2.remove(0);
    meinVektor2.display();
    meinVektor2.remove(meinVektor2.getAnzahlElemente() - 1);
    meinVektor2.display();

    cout << "\nWeitere Tests:" << endl;
    CVektor50 vollerVektor(50);
    vollerVektor.display();
    vollerVektor.add(0, 1);

    CVektor50 leererVektor(0);
    leererVektor.display();
    leererVektor.remove(0);
    leererVektor.add(0, 42);
    leererVektor.display();

    cout << endl << endl;
    
    return 0;
}
