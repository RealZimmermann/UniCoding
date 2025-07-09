#pragma warning (disable: 4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Diese Funktion gibt den aktuellen Stand des Sudokus aus
void printSudoku(char sudoku[9][9]) {
    printf("+ - - - + - - - + - - - +\n");                                          // Kopfzeile
    for (int i = 0; i < 9; i++) {
        printf("|");                                                                // Zeilenanfang
        for (int j = 0; j < 9; j++) {
            printf(" %c", sudoku[i][j]);
            if ((j + 1) % 3 == 0 && j != 9 - 1) {
                printf(" |");                                                       // Trennzeichen innerhalb der Zeile
            }
        }
        printf(" |\n");
        if ((i + 1) % 3 == 0) printf("+ - - - + - - - + - - - +\n");                // Trennlinie nach jeder dritten Zeile
    }
    return 0;                                                                       // Ausgabe erfolgreich
}

// Diese Funktion ist zur �berpr�fung, ob ein Zug korrekt ist
int isValidMove(char sudoku[9][9], int row, int col, char num) {
    // �berpr�fen der Zeile
    for (int i = 0; i < 9; i++) {
        if (sudoku[row][i] == num) return 1;                                        // Zahl schon in der Zeile
    }

    // �berpr�fen der Spalte
    for (int i = 0; i < 9; i++) {
        if (sudoku[i][col] == num) return 1;                                        // Zahl schon in der Spalte
    }

    // �berpr�fen der Boxen
    int startRow = (row / 3) * 3;
    int startCol = (col / 3) * 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (sudoku[startRow + i][startCol + j] == num) return 1;                // Zahl ist bereits in der Box
        }
    }

    return 0;                                                                       // Zahl ist g�ltig
}

// Diese Funktion ist zur �berpr�fung, ob das Sudoku vollst�ndig ist
int isComplete(char sudoku[9][9]) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (sudoku[i][j] == '.') return 1;                                      // Es existieren noch leere Felder
        }
    }
    return 0;                                                                       // Alle Felder sind ausgef�llt
}

// Diese Funktion soll pr�fen, ob die Eingabe des Spielers korrekt ist. Sie verwendet daf�r die Funktion isValidMove
int isSolutionValid(char sudoku[9][9]) {
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            if (sudoku[row][col] != '.') {
                char num = sudoku[row][col];                                        // Tempor�r die aktuelle Zahl entfernen, um die Validit�t zu pr�fen
                sudoku[row][col] = '.';
                if (isValidMove(sudoku, row, col, num) == 0) {                      // Zahl ist nicht g�ltig
                    sudoku[row][col] = num;                                         // R�ckg�ngig machen
                    return 1;
                }
                sudoku[row][col] = num;
            }
        }
    }

    return 0;                                                                       // Keine Fehler gefunden
}

// Diese Funktion soll das Sudoku l�sen. Sie verwendet daf�r die Funktion isValidMove
int solve(char sudoku[9][9], int row, int col) {
    if (row == 9) return 0;                                                         // Alle Zeilen erreicht, Sudoku ist vollst�ndig gel�st

    if (sudoku[row][col] != '.') {
        
        if (col == 8) return solve(sudoku, row + 1, 0);                             // Wenn Ende einer Zeile erreicht, gehe zur n�chsten Zeile und beginne in der ersten Spalte

        else return solve(sudoku, row, col + 1);                                    // Andernfalls gehe zur n�chsten Spalte
    }

    // Versuche f�r jedes m�gliche Zahl von '1' bis '9'
    for (char num = '1'; num <= '9'; num++) {
        if (isValidMove(sudoku, row, col, num) == 0) {                              // �berpr�fe, ob Zahl an aktueller Position g�ltig ist. Falls ja, wird ins Feld geschrieben
            sudoku[row][col] = num;

            if (col == 8) {                                                         // Wenn Ende einer Zeile erreicht, gehe zur n�chsten Zeile und beginne in der ersten Spalte
                if (solve(sudoku, row + 1, 0) == 0) return 0;                       // Rekursiver Aufruf der Funktion, um Sudoku weiter zu l�sen
            }
            else {
                if (solve(sudoku, row, col + 1) == 0) return 0;                     // Rekursiver Aufruf der Funktion, um die n�chste Spalte zu pr�fen
            }

            
            sudoku[row][col] = '.';                                                 // Wenn Zahl nicht zu einer L�sung f�hrt, setze das Feld wieder auf '.'
        }
    }

    return 1;                                                                       // Sudoku konnte nicht gel�st werden
}

// Diese Funktion kann den aktuell Spielstand in der Datei zwischenstand.txt abspeichern
int save(char sudoku[9][9]) {
    const char* filename = "zwischenstand.txt";
    FILE* fp = fopen(filename, "wt");
    if (fp == NULL) {                                                               // Test, ob Datei existiert
        printf("Fehler beim �ffnen der Datei zum Speichern.\n");
        return 1;  
    }

    fprintf(fp, "+ - - - + - - - + - - - +\n");                                     // Kopfzeile
    for (int i = 0; i < 9; i++) {
        fprintf(fp, "|");                                                           // Zeilenanfang
        for (int j = 0; j < 9; j++) {
            fprintf(fp, " %c", sudoku[i][j]);
            if ((j + 1) % 3 == 0 && j != 9 - 1) fprintf(fp, " |");                  // Trennzeichen innerhalb der Zeile
        }
        fprintf(fp, " |\n");

        if ((i + 1) % 3 == 0) fprintf(fp, "+ - - - + - - - + - - - +\n");           // Trennlinie nach jeder dritten Zeile
    }

    fclose(fp);
    printf("Sudoku wurde erfolgreich gespeichert!\n");
    return 0;                                                                       // Sudoko wurde erfolgreich gespeichert
}

// Diese Funktion soll die L�sung ausgeben. Daf�r verwendet sie die Funktion solve und dann printSudoku
void printSolution(char sudoku[9][9]) {
    char tempSudoku[9][9];                                                          // Tempor�res Sudoku-Array wird erstellt, um Original-Sudoku nicht zu ver�ndern und Original Sudoku wird kopiert
    memcpy(tempSudoku, sudoku, sizeof(tempSudoku));

    if (solve(tempSudoku, 0, 0) == 0) {                                             // Sudoku wird mit Funktion solve gel�sst
        printf("Loesung des Sudokus:\n");
        printSudoku(tempSudoku);                                                    // Gel�stes Sudoko wird ausgegeben
        return 0;
    }
    else printf("Keine Loesung fuer dieses Sudoku gefunden.\n");                    // Falls keine L�sung gefunden wird, wird mit return 1 Funktion beendet
    return 1;
}

int main() {
    FILE* fp;
    char sudoku[9][9];
    char initialSudoku[9][9];
    char line[50];
    int row = 0;
    char filename[20];

    while (1) {                                                                     // Schleife f�r Auswahl der Schwierigkeitsstufe
        printf("Waehlen Sie eine Schwierigkeitsstufe:\n");
        printf("1. Einfach\n");
        printf("2. Mittel\n");
        printf("3. Schwer\n");
        printf("4. Abgespeicherter Zwischenstand\n");
        printf("Ihre Auswahl: ");

        int choice;
        scanf("%d", &choice);                                                       // Eingabe der Wahl
        getchar();

        switch (choice) {                                                           // Auswahl der Datei basierend auf der Schwierigkeitsstufe
        case 1:
            strcpy(filename, "einfach.txt");
            break;
        case 2:
            strcpy(filename, "mittel.txt");
            break;
        case 3:
            strcpy(filename, "schwer.txt");
            break;
        case 4:
            strcpy(filename, "zwischenstand.txt");                                  // F�r gespeicherten Zwischenstand
            break;
        default:
            printf("Ungueltige Auswahl. Programm beendet.\n");
            return 1;                                                               // Falls falsche Zahl eingetippt wird, wird mit return 1 abgebrochen und das Programm beendet
        }

        if ((fp = fopen(filename, "rt")) == NULL) {                                 // �ffnen der Datei, die die Sudoku-Vorlage enth�lt
            printf("Die Datei %s existiert nicht\n", filename);
            return 1;                                                               // Wenn die Datei nicht existiert, wird mit return 1 beendet
        }

        while (fgets(line, sizeof(line), fp)) {                                     // Einlesen des Sudokus aus der Datei
            if (line[0] == '+') continue;                                           // �berspringen von Kopfzeilen

            int col = 0;
            for (int i = 0; line[i] != '\0'; i++) {                                 // Durchlaufen der Zeile und Spalte von Zahlen oder '.'
                if (line[i] >= '1' && line[i] <= '9') {
                    sudoku[row][col] = line[i];
                    initialSudoku[row][col] = line[i];
                    col++;
                }
                else if (line[i] == '.') {
                    sudoku[row][col] = '.';
                    initialSudoku[row][col] = '.';
                    col++;
                }
            }

            if (col == 9) row++;

            if (row >= 9) break;
        }
        fclose(fp);                                                                 // Schlie�en der Datei

        printSudoku(sudoku);                                                        // Sudoku wird ausgeben

        char history[9 * 9][3];                                                     // F�r Undu-Funktion
        int historyCount = 0;

        while (1) {                                                                 // Men�ausgabe f�r die Optionen
            printf("\nGeben Sie entweder drei Zahlen ein (1. Zahl Spalte, 2. Zahl Zeile und 3. Zahl Eingabe), u fuer Undo, p zum pruefen, l fuer Loesung, s fuer speichern oder q zum Beenden:\n");
            char input[10];
            fgets(input, sizeof(input), stdin);

            if (input[0] == 'q') {
                printf("Spiel beendet.\n");
                return 0;                                                           // Spiel erfolgreich beendet
            }

            if (input[0] == 'u') {                                                  // R�ckg�ngig machen des letzten Zuges
                if (historyCount > 0) {
                    historyCount--;                                                 // Letzten Eintrag aus der Historie entfernen
                    int lastRow = history[historyCount][0];
                    int lastCol = history[historyCount][1];
                    sudoku[lastRow][lastCol] = '.';                                 // Feld wird wieder leer gemacht
                    printf("Letzter Zug rueckgaengig gemacht.\n");
                    printSudoku(sudoku);
                }
                else printf("Keine Zuege zum Rueckgaengig machen.\n");
                continue;
            }

            if (input[0] == 'p') {                                                  // Pr�fen, ob Sudoku korrekt ausgef�llt ist
                if (isComplete(sudoku)) {
                    printf("Das Sudoku ist nicht komplett. Ueberpruefen Sie Ihre Eingaben.\n\n");
                    continue;
                }
                else {
                    if (isSolutionValid(sudoku)) printf("Das Sudoku ist nicht korrekt. Ueberpruefen Sie Ihre Eingaben.\n\n");
                    else printf("Das Sudoku ist korrekt!\n\n");
                }
                continue;
            }

            if (input[0] == 'l') {                                                  // L�sung anzeigen
                printSolution(initialSudoku);
                continue;
            }

            if (input[0] == 's') {                                                  // Sudoku speichern
                save(sudoku);
                continue;
            }

            int r, c;                                                               // Eingabe f�r eine Zahl und deren Position
            char num;
            if (sscanf(input, "%d %d %c", &r, &c, &num) != 3) {
                printf("Ungueltige Eingabe. Versuchen Sie es erneut.\n");
                continue;
            }

            r--;
            c--;

            if (r < 0 || r >= 9 || c < 0 || c >= 9 || num < '1' || num > '9') {     // �berpr�fen der G�ltigkeit der Eingabe (Position und Zahl)
                printf("Ungueltige Position oder Zahl. Versuchen Sie es erneut.\n");
                continue;
            }

            if (sudoku[r][c] != '.') {                                              // �berpr�fen, ob das Feld bereits belegt ist
                printf("Das Feld (%d,%d) ist bereits belegt.\n", r + 1, c + 1);
                continue;
            }

            sudoku[r][c] = num;                                                     // Die eingegebene Zahl in das Sudoku eintragen
            history[historyCount][0] = r;
            history[historyCount][1] = c;
            historyCount++;
            printSudoku(sudoku);
        }
    }

    return 0;                                                                       // Erfolgreiches Beenden des Programms
}
