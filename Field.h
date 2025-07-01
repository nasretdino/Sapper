#ifndef Field_H
#define Field_H
#include "FieldPoint.h"


class Field {
    enum gameType { easy = 10, normal = 20, hard = 30 }; // minePercent

    gameType type{};

    enum fieldSizeRestrictions {
        maxHeight = 10,
        maxWidth = 10,
        minHeight = 5,
        minWidth = 5,
    };

    unsigned height{};
    unsigned width{};
    unsigned countSecret{}; // Количество неоткрытых или незакрашенных полей

    FieldPoint* field = nullptr;

public:
    Field() = default;

    void create(const unsigned a, const std::pair<unsigned, unsigned>& sizes);

    ~Field();

    int openPoint(const Point& p);


    void setMines(const unsigned amount, const Point* mines); // можно сделать по другому (вычитанием высоты, а не умножением на высоту)


    void print() const; // Добавить очистку консоли

    void printAll() const;

    unsigned getMaxHeight() const;
    unsigned getMaxWidth() const;
    unsigned getMinHeight() const;
    unsigned getMinWidth() const;
    unsigned getHeight() const;
    unsigned getWidth() const;
    unsigned getType() const;
    unsigned getCountSecret() const;

private:
    void tryOpenEmpty(const int x, const int y); // сделать с вычитанием, а не умножением

    void openEmpty(const FieldPoint& point);
};


#endif // !Field_H
