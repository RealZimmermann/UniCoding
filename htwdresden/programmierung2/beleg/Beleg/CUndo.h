#pragma once
#include <vector>
#include "Move.h"

// Klasse zur Speicherung der Historie
class CUndo {
private:
    std::vector<Move> history;
public:
    void push(Move m);
    bool pop(Move& m);
    bool isEmpty() const;
};