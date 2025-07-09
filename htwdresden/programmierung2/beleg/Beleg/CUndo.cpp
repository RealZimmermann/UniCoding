#include "CUndo.h"

void CUndo::push(Move m) {
    history.push_back(m);
}

bool CUndo::pop(Move& m) {
    if (history.empty()) return false;
    m = history.back();
    history.pop_back();
    return true;
}

bool CUndo::isEmpty() const {
    return history.empty();
}