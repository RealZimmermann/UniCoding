#include <iostream>
#include <string>
#include "CSudoku.h"
#include "CUndo.h"
#include "Move.h"
using namespace std;

// Hauptfunktion
int main() {
    CSudoku sudoku;
    CUndo undo;
    int choice;

    cout << "Waehlen Sie eine Schwierigkeitsstufe:\n1. Einfach\n2. Mittel\n3. Schwer\n4. Letzter Zwischenstand\nIhre Auswahl: ";
    cin >> choice;

    switch (choice) {
    case 1: sudoku.loadFromFile("einfach.txt"); break;
    case 2: sudoku.loadFromFile("mittel.txt"); break;
    case 3: sudoku.loadFromFile("schwer.txt"); break;
    case 4: sudoku.loadFromFile("zwischenstand.txt"); break;
    default: cout << "Ungueltige Auswahl.\n"; return 1;
    }

    sudoku.print();

    cout << "Gib deine Zuege ein (Zeile Spalte Zahl), 'undo', 'speichern' oder 'ende':";
    while (true) {
        cout << "\nEingabe: ";
        string input;
        cin >> input;

        if (input == "undo") {
            Move last;
            if (undo.pop(last)) {
                sudoku.unset(last.row, last.col);
                cout << "Letzter Zug rueckgaengig gemacht.\n";
            }
            else {
                cout << "Kein Zug zum rueckgaengig machen.\n";
            }
            sudoku.print();
            continue;
        }

        if (input == "speichern") {
            if (sudoku.saveToFile()) cout << "Zwischenstand gespeichert.\n";
            else cout << "Fehler beim Speichern.\n";
            continue;
        }

        if (input == "ende") break;

        int row = stoi(input), col, num;
        cin >> col >> num;
        if (row < 1 || row > 9 || col < 1 || col > 9 || num < 1 || num > 9) {
            cout << "Ungueltige Eingabe.\n";
            continue;
        }

        if (!sudoku.set(row - 1, col - 1, num)) {
            cout << "Ungueltiger Zug.\n";
            continue;
        }

        undo.push({ row - 1, col - 1, num });
        sudoku.print();
    }

    cout << "\nLoese Sudoku...\n";
    if (sudoku.solve()) {
        cout << "Geloestes Sudoku:\n";
        sudoku.print();
    }
    else {
        cout << "Keine Loesung gefunden.\n";
    }

    return 0;
}
