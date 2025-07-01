#ifndef FieldPoint_H
#include "Point.h"


class FieldPoint :
    public Point
{
    bool mineInside{};
    char symbol{ '#' };
    unsigned number{};
public:
    FieldPoint() = default;

    FieldPoint(const unsigned x, const unsigned y);

    FieldPoint(const unsigned x, const unsigned y, const bool mine_inside);

    void setMine();
    bool isMineInside() const;
    void setSymbol(const char symbol);
    char getSymbol() const;
    unsigned getNumber() const;
    void setNumber(const unsigned number);
    void upNumber(); // вместо этого можно сделать операцию инкремента
};

#endif // !FieldPoint_H