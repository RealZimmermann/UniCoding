#include <iostream>

using namespace std;

// Aufgabe 1: Vertauschen von Werten mit Zeigern
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Aufgabe 1: Vertauschen von Werten mit Referenzen
void swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

// Aufgabe 2a: Löschen von Vektorelementen
void loesche(int* vektor, int& anzahl, int pos) {
    if (pos < 0 || pos >= anzahl) {
        cout << "Ungueltige Position\n";
        return;
    }

    for (int i = pos; i < anzahl - 1; ++i) {
        vektor[i] = vektor[i + 1];
    }

    anzahl--;                                                               // Vektor ist jetzt um 1 Element kürzer
}

// Aufgabe 2b: Löschen von Vektorelementen in einer Strukturvariable
struct IntVektor {
    int* daten;
    int laenge;
};

// Ausgabe des Vektors
void print(const IntVektor& vektor) {
    for (int i = 0; i < vektor.laenge; ++i) {
        cout << vektor.daten[i] << " ";
    }
    cout << endl;
}

// Löschen in Struktur
void loesche(IntVektor& vektor, int pos) {
    if (pos < 0 || pos >= vektor.laenge) {
        cout << "Ungueltige Position\n";
        return;
    }

    for (int i = pos; i < vektor.laenge - 1; ++i) {
        vektor.daten[i] = vektor.daten[i + 1];
    }

    vektor.laenge--;
}

int main() {
    cout << "=== Aufgabe 1 ===" << endl;
    int a = 1;
    int b = 3;

    cout << "Vor Swap (Zeiger): a = " << a << ", b = " << b << endl;
    swap(&a, &b);                                                           // Zeiger-Version
    cout << "Nach Swap (Zeiger): a = " << a << ", b = " << b << endl;

    swap(a, b);                                                             // Referenz-Version
    cout << "Nach Swap (Referenz): a = " << a << ", b = " << b << endl;

    cout << "\n=== Aufgabe 2a ===" << endl;
    const int max = 10;
    int array[max] = { 1, 2, 3, 4, 5 };
    int anzahl = 5;

    cout << "Vor Loeschen (Array): ";
    for (int i = 0; i < anzahl; ++i) cout << array[i] << " ";
    cout << endl;

    loesche(array, anzahl, 2);                                              // Löscht das Element an Position 2 (also "3")

    cout << "Nach Loeschen (Array): ";
    for (int i = 0; i < anzahl; ++i) cout << array[i] << " ";
    cout << endl;

    cout << "\n=== Aufgabe 2b ===" << endl;
    IntVektor vec;
    vec.daten = new int[10] {9, 8, 7, 6, 5};
    vec.laenge = 5;

    cout << "Vor Loeschen (Struktur): ";
    print(vec);

    loesche(vec, 1);                                                        // Löscht das Element an Position 1 (also "8")

    cout << "Nach Loeschen (Struktur): ";
    print(vec);

    delete[] vec.daten;                                                     // Speicher wieder freigeben
    
    return 0;
}