#include "CVektor50.h"
#include <iostream>
#include <algorithm>

using namespace std;

CVektor50::CVektor50() {
    for (int i = 0; i < 50; ++i) {
        elemente[i] = 0;
    }

    cout << "Standardkonstruktor aufgerufen. Vektor mit 50 Nullen initialisiert." << std::endl;
}

CVektor50::CVektor50(int anz) {
    if (anz < 0 || anz > 50) {
        cerr << "Fehler: Anzahl der Elemente muss zwischen 0 und 50 liegen. Setze auf Standardgroesse (0)." << endl;
        anz = 0;
        
        return;
    }

    anzahlElemente = anz;

    for (int i = 0; i < anzahlElemente; i++) {
        elemente[i] = rand() % 101; // Zufallszahlen zwischen 0 und 100
    }

    cout << "Konstruktor mit Parameter aufgerufen. Die ersten " << anzahlElemente << " Elemente mit Zufallszahlen initialisiert." << endl;
}

CVektor50::~CVektor50() {
    
}

void CVektor50::sortiere() {
    sort(elemente, elemente + anzahlElemente);
    cout << "Vektor sortiert." << endl;
}

void CVektor50::add(int position, int wert) {
    if (anzahlElemente >= 50) {
        cerr << "Fehler: Vektor ist bereits voll. Einfuegen nicht moeglich." << endl;
        
        return;
    }

    if (position < 0 || position > anzahlElemente) {
        cerr << "Fehler: Ungueltige Position zum Einfuegen." << endl;
        
        return;
    }

    for (int i = anzahlElemente; i > position; i--) {
        elemente[i] = elemente[i - 1];
    }

    elemente[position] = wert;
    anzahlElemente++;
    cout << "Element " << wert << " an Position " << position << " eingefuegt." << endl;
}

void CVektor50::remove(int position) {
    if (anzahlElemente <= 0) {
        cerr << "Fehler: Vektor ist leer. Loeschen nicht moeglich." << endl;
        
        return;
    }
    
    if (position < 0 || position >= anzahlElemente) {
        cerr << "Fehler: Ungueltige Position zum Loeschen." << endl;
        
        return;
    }

    for (int i = position; i < anzahlElemente - 1; ++i) {
        elemente[i] = elemente[i + 1];
    }

    anzahlElemente--;
    cout << "Element an Position " << position << " geloescht." << endl;
}

void CVektor50::display() const {
    if (anzahlElemente == 0) {
        cout << "Vektor ist leer." << endl;
        
        return;
    }

    std::cout << "Vektorinhalt (" << anzahlElemente << " Elemente): [";
    for (int i = 0; i < anzahlElemente; i++) {
        std::cout << elemente[i];
        if (i < anzahlElemente - 1) cout << ", ";
    }

    cout << "]" << endl;
}

int CVektor50::getAnzahlElemente() const {
    return anzahlElemente;
}
