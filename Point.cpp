#include "Point.h"

Point::Point(const unsigned x, const unsigned y) : x{ x }, y{ y } {
}

unsigned Point::getX() const { return x; }
unsigned Point::getY() const { return y; }
void Point::setX(const unsigned x) { this->x = x; }
void Point::setY(const unsigned y) { this->y = y; }


std::istream& operator>>(std::istream& is, Point& point) {
    std::cout << "Input x: ";
    if (!(is >> point.x)) { throw std::invalid_argument("Invalid input for x"); }

    std::cout << "Input y: ";
    if (!(is >> point.y)) { throw std::invalid_argument("Invalid input for y"); }

    return is;
}

std::ostream& operator<<(std::ostream& os, const Point& point) {
    os << point.x << " " << point.y;
    return os;
}

bool Point::operator==(const Point& other) const { return x == other.x && y == other.y; }