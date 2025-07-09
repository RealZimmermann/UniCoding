#include "CSudoku.h"
#include <iostream>
#include <fstream>
using namespace std;

// Diese Funktion lieﬂt das Sudoku der Textdatei ein
bool CSudoku::loadFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Fehler beim Oeffnen der Datei!" << endl;
        return false;
    }

    sudoku.resize(9, vector<int>(9));
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            if (!(file >> sudoku[i][j])) {
                cerr << "Ungueltiges Format in der Datei!" << endl;
                return false;
            }
        }
    }
    return true;
}

// Diese Funktion speichert den Zwischenstand in die Zwischenstandsdatei
bool CSudoku::saveToFile(const string& filename) const {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Fehler beim Schreiben der Datei!" << endl;
        return false;
    }

    for (const auto& row : sudoku) {
        for (int val : row) {
            file << val << " ";
        }
        file << "\n";
    }
    return true;
}

// Diese Funktion gibt den aktuellen Stand des Sudokus aus
void CSudoku::print() const {
    cout << "+ - - - + - - - + - - - +" << endl;                                    // Kopfzeile
    for (int i = 0; i < 9; i++) {
        cout << "| ";
        for (int j = 0; j < 9; j++) {
            if (sudoku[i][j] != 0) cout << sudoku[i][j] << " ";
            else cout << ". ";
            if ((j + 1) % 3 == 0 && j != 8) cout << "| ";                           // Trennzeichen innerhalb der Zeile
        }
        cout << "|" << endl;
        if ((i + 1) % 3 == 0) cout << "+ - - - + - - - + - - - +" << endl;          // Trennlinie nach jeder dritten Zeile
    }
}

bool CSudoku::isValidMove(int row, int col, int num) const {
    for (int x = 0; x < 9; x++) {
        if (sudoku[row][x] == num || sudoku[x][col] == num ||
            sudoku[row - row % 3 + x / 3][col - col % 3 + x % 3] == num) {
            return false;
        }
    }
    return true;
}

// Diese Funktion ist zur ‹berpr¸fung, ob ein Zug korrekt ist
bool CSudoku::solve() {
    int row = -1, col = -1;
    bool isEmpty = true;
    for (int i = 0; i < 9 && isEmpty; i++) {
        for (int j = 0; j < 9; j++) {
            if (sudoku[i][j] == 0) {
                row = i; col = j;
                isEmpty = false;
                break;
            }
        }
    }
    if (isEmpty) return true;
    for (int num = 1; num <= 9; num++) {
        if (isValidMove(row, col, num)) {
            sudoku[row][col] = num;
            if (solve()) return true;
            sudoku[row][col] = 0;
        }
    }
    return false;
}

// Diese Funktion setzt eine Zahl im Sudoku, wenn das Feld leer ist und der Zug g¸ltig ist
bool CSudoku::set(int row, int col, int num) {
    if (sudoku[row][col] == 0 && isValidMove(row, col, num)) {
        sudoku[row][col] = num;
        return true;
    }
    return false;
}

// Diese Funktion lˆscht den Wert an einer bestimmten Position, setzt ihn auf 0
void CSudoku::unset(int row, int col) {
    sudoku[row][col] = 0;
}

// Diese Funktion gibt den Wert an der angegebenen Position zur¸ck
int CSudoku::get(int row, int col) const {
    return sudoku[row][col];
}