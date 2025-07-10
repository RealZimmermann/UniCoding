#include "Warteschlange.h"

Warteschlange::Warteschlange() : head(nullptr) {}

void Warteschlange::eintreten(int azahl) {
    Element* neu = new Element(azahl);
    if (!head) {
        head = neu;
    }
    else {
        Element* cur = head;
        while (cur->next) cur = cur->next;
        cur->next = neu;
    }
}

Element* Warteschlange::bedienen() {
    if (!head) return nullptr;
    Element* first = head;
    head = head->next;
    first->next = nullptr;
    return first;
}

Warteschlange::~Warteschlange() {
    while (head) {
        Element* tmp = head;
        head = head->next;
        delete tmp;
    }
}