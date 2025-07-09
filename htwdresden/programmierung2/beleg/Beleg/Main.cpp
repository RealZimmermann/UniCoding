#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <stack>
using namespace std;

struct Move {
    int row;
    int col;
    int value;
};

// Diese Funktion ließt das Sudoku der Textdatei ein
bool readSudokuFromFile(const string& filename, vector<vector<int>>& sudoku) {
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

    file.close();
    return true;
}

bool saveSudokuToFile(const vector<vector<int>>& sudoku) {
    ofstream file("zwischenstand.txt");
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

    file.close();
    return true;
}

// Diese Funktion gibt den aktuellen Stand des Sudokus aus
void printsudoku(const vector<vector<int> >& sudoku) {                              // Function to print the sudoku
    cout << "+ - - - + - - - + - - - +" << endl;                                    // Kopfzeile
    for (int i = 0; i < 9; i++) {
        cout << "| ";
        for (int j = 0; j < 9; j++) {
            if (sudoku[i][j] != 0) {
                cout << sudoku[i][j] << " ";
            }
            else {
                cout << ". ";
            }
            
            if ((j + 1) % 3 == 0 && j != 9 - 1) {
                cout << "| ";                                                       // Trennzeichen innerhalb der Zeile
            }
        }
        cout << "|" << endl;
        if ((i + 1) % 3 == 0) {
            cout << "+ - - - + - - - + - - - +" << endl;                            // Trennlinie nach jeder dritten Zeile
        }
    }
}

// Diese Funktion ist zur Überprüfung, ob ein Zug korrekt ist
bool isValidMove(const vector<vector<int> >& sudoku, int row, int col, int num) {
    for (int x = 0; x < 9; x++) {                                                   // Überprüfe die Zeile
        if (sudoku[row][x] == num) {
            return false;
        }

        if (sudoku[x][col] == num) {                                                // Überprüft die Spalte
            return false;
        }

        if (sudoku[row - row % 3 + x / 3]                                           // Überprüft die Box
            [col - col % 3 + x % 3]
            == num) {
            return false;
        }
    }
    return true;
}

// Diese Funktion soll die Lösung ausgeben. Dafür verwendet sie die Funktion solve und dann printSudoku
bool solveSudoku(vector<vector<int> >& sudoku) {
    int row = -1;
    int col = -1;
    bool isEmpty = true;

    for (int i = 0; i < 9; i++) {                                                       // Findet ein leeres Feld im Sudoku
        for (int j = 0; j < 9; j++) {
            if (sudoku[i][j] == 0) {
                row = i;
                col = j;
                isEmpty = false;
                break;
            }
        }
        if (!isEmpty) {
            break;
        }
    }

    if (isEmpty) {
        return true;                                                                    // Es gibt keine leeren Felder mehr
    }

    for (int num = 1; num <= 9; num++) {                                                // Zahlen 1 - 9 werden getestet
        if (isValidMove(sudoku, row, col, num)) {
            sudoku[row][col] = num;
            if (solveSudoku(sudoku)) {                                                  // Wenn das Sudoku gelösst wurde, gehe erfolgreich zurück
                return true;
            }
            // Undo the placement (backtracking)
            sudoku[row][col] = 0;
        }
    }
    return false;                                                                       // Es wurde keine Lösung gefunden
}

int main() {
    vector<vector<int>> sudoku;
    vector<Move> moveHistory;
    
    int choice;
    cout << "Waehlen Sie eine Schwierigkeitsstufe: " << endl;
    cout << "1. Einfach" << endl;
    cout << "2. Mittel" << endl;
    cout << "3. Schwer" << endl;
    cout << "4. Letzter Zwischenstand" << endl;
    cout << "Ihre Auswahl: ";
    cin >> choice;
    cout << endl;

    switch (choice) {
    case 1:
        readSudokuFromFile("einfach.txt", sudoku);
        break;
    case 2:
        readSudokuFromFile("mittel.txt", sudoku);
        break;
    case 3:
        readSudokuFromFile("schwer.txt", sudoku);
        break;
    case 4:
        readSudokuFromFile("zwischenstand.txt", sudoku);
        break;
    default:
        cout << "Ungueltige Auswahl. Programm beendet" << endl;
        break;
    }
    
    cout << "Eingelesenes Sudoku:" << endl;
    printsudoku(sudoku);
    
    cout << endl;
    cout << "Gib deine Zuege ein (Zeile Spalte Zahl), undo um einen Zug rueckgaengig zu machen, speichern um den Zwischenstand zu speichern oder ende um zu beenden:";

    while (true) {
        cout << endl;
        cout << "Eingabe: ";
        string input;
        cin >> input;

        if (input == "undo") {
            if (moveHistory.empty()) {
                cout << "Kein Zug zum zuruecknehmen vorhanden." << endl;
                cout << endl;
                continue;
            }

            Move lastMove = moveHistory.back();
            moveHistory.pop_back();
            sudoku[lastMove.row][lastMove.col] = 0;
            cout << "Letzter Zug rueckgaengig gemacht." << endl;
            cout << endl;
            printsudoku(sudoku);
            continue;
        }

        if (input == "speichern") {
            if (saveSudokuToFile(sudoku)) {
                cout << "Spielstand wurde erfolgreich in 'zwischenstand.txt' gespeichert." << endl;
            }
            else {
                cout << "Fehler beim Speichern des Spiels." << endl;
            }
            continue;
        }

        if (input == "ende") {
            cout << "Benutzereingabe beendet.\n";
            break;
        }

        int row = stoi(input);                                                                           // Wenn kein undo oder ende: dann 1. Wert war Zahl, wir lesen noch zwei weitere
        int col, num;
        cin >> col >> num;

        // Prüfen ob richtige Zahl
        if (row < 1 || row > 9 || col < 1 || col > 9 || num < 1 || num > 9) {
            cout << "Ungueltige Eingabe. Zeile, Spalte und Zahl müssen zwischen 1 und 9 liegen.\n";
            continue;
        }

        // Ist Feld schon belegt?
        if (sudoku[row - 1][col - 1] != 0) {
            cout << "Dieses Feld ist bereits belegt.\n";
            continue;
        }

        if (!isValidMove(sudoku, row - 1, col - 1, num)) {
            cout << "Ungueltiger Zug nach den Regeln." << endl;
            continue;
        }

        // gültiger Zug
        sudoku[row - 1][col - 1] = num;
        Move m = { row - 1, col - 1, num };
        moveHistory.push_back(m);
        printsudoku(sudoku);
    }
    
    // Solve the Sudoku and print the result
    if (solveSudoku(sudoku)) {                                          
        cout << endl;
        cout << "Geloesstes Sudoku: " << endl;
        printsudoku(sudoku);                                            // Falls Lösung gefunden wurde, gib diese aus
    }
    else {
        cout << "Es existiert keine Lösung" << endl;                           // Falls Lösung nicht gefunden wurde, gib Error aus
        return 1;
    }

    return 0;
}