#ifndef Mines_H
#define Mines_H
#include "Point.h"
#include <random>

class Mines
{
    Point* mines = nullptr;
    unsigned amount{};


    bool checkMine(const Point& startPoint, const int& i) const;

public:
    Mines() = default;

    Mines(const unsigned height, const unsigned width, const Point& startPoint, const unsigned minePercent);

    Mines(const Mines& right);

    ~Mines();

    Mines& operator=(const Mines& right);


    void print() const;

    const Point* getMines() const;
    unsigned getAmount() const;

};

#endif // !Mines_H