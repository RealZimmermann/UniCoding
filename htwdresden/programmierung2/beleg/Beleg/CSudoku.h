#pragma once
#include <vector>
#include <string>

// Die Klasse kapselt das Sudoku-Feld und stellt zugehörige Operationen zur Verfügung
class CSudoku {
private:
    std::vector<std::vector<int>> sudoku;

public:
    bool loadFromFile(const std::string& filename);
    bool saveToFile(const std::string& filename = "zwischenstand.txt") const;
    void print() const;
    bool isValidMove(int row, int col, int num) const;
    bool solve();
    bool set(int row, int col, int num);
    void unset(int row, int col);
    int get(int row, int col) const;
};