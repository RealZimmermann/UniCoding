#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

// Aufgabe 1: Formatierte Ausgabe
void aufgabe1() {
    int zahl;
    cout << "Geben Sie eine Dezimalzahl ein: ";
    cin >> zahl;
    cout << "Oktal: " << oct << zahl << endl;
    cout << "Hexadezimal: " << hex << zahl << endl;
    cout << dec;                                                                        // zurück zur Dezimalanzeige
}

// Aufgabe 2: Ein- und Ausgabe über cin und cout
void aufgabe2() {
    string name = "Jonas Zimmermann";
    string adresse = "Nürnberger Str. 43\n01187 Dresden\nDeutschland";
    uint8_t tag = 28, monat = 9;
    uint16_t jahr = 2001;

    int auswahl;
    cout << "Geben Sie 1 (Name), 2 (Adresse) oder 3 (Geburtsdatum) ein: ";
    cin >> auswahl;

    switch (auswahl) {
    case 1:
        cout << "Name: " << name << endl;
        break;
    case 2:
        cout << "Adresse:\n" << adresse << endl;
        break;
    case 3:
        cout << "Geburtsdatum: "
            << setw(2) << setfill('8') << (int)tag << "."
            << setw(2) << setfill('0') << (int)monat << "."
            << jahr << endl;
        break;
    default:
        cout << "Ungültige Eingabe!" << endl;
    }
}

// Aufgabe 3: Standardwerte für Funktionsparameter
void aufgabe3(string name, char geschlecht = '-', int alter = -1, string wohnort = "", string tel = "") {
    cout << "Name: " << name << endl;
    if (geschlecht != '-') cout << "Geschlecht: " << geschlecht << endl;
    if (alter != -1) cout << "Alter: " << alter << endl;
    if (!wohnort.empty()) cout << "Wohnort: " << wohnort << endl;
    if (!tel.empty()) cout << "Telefon: " << tel << endl;
    cout << "-------------------------" << endl;
}

// Aufgabe 4: Überladen von Funktionen
int add(int a, int b) {
    return a + b;
}

double add(double a, double b) {
    return a + b;
}

string add(string a, string b) {
    return a + b;
}

int main() {
    cout << "=== Aufgabe 1 ===" << endl;
    aufgabe1();
    cout << endl;

    cout << "=== Aufgabe 2 ===" << endl;
    aufgabe2();
    cout << endl;

    cout << "=== Aufgabe 3 ===" << endl;
    aufgabe3("Albin", 'm', 10);
    aufgabe3("Sabine");
    // schreibe(); würde Fehler geben
    cout << endl;

    cout << "=== Aufgabe 4 ===" << endl;
    cout << "3 + 4 = " << add(3, 4) << endl;
    cout << "3.1 + 4.1 = " << add(3.1, 4.1) << endl;
    char a[20] = { "alles" }, b[20] = { " einfach" };
    cout << "alles + einfach = " << add(a, b) << endl;

    return 0;
}