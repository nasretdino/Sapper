#include "FieldPoint.h"


FieldPoint::FieldPoint(const unsigned x, const unsigned y) : Point{ x, y } {
}

FieldPoint::FieldPoint(const unsigned x, const unsigned y, const bool mine_inside) : Point(x, y), mineInside(mine_inside) {
}

void FieldPoint::setMine() { mineInside = true; }
bool FieldPoint::isMineInside() const { return mineInside; }
void FieldPoint::setSymbol(const char symbol) { this->symbol = symbol; }
char FieldPoint::getSymbol() const { return symbol; }
unsigned FieldPoint::getNumber() const { return number; }
void FieldPoint::setNumber(const unsigned number) { this->number = number; }
void FieldPoint::upNumber() { number++; }