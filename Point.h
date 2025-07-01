#ifndef Point_H
#define Point_H
#include <iostream>

class Point {
protected:
    unsigned x{}, y{};

public:
    Point() = default;
    Point(const unsigned x, const unsigned y);

    unsigned getX() const;
    unsigned getY() const;
    void setX(const unsigned x);
    void setY(const unsigned y);

    friend std::istream& operator>>(std::istream& is, Point& point);

    friend std::ostream& operator<<(std::ostream& os, const Point& point);

    bool operator==(const Point& other) const;
};

#endif // !Point_H