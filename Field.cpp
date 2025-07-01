#include "Field.h"


void Field::create(const unsigned a, const std::pair<unsigned, unsigned>& sizes) {
    switch (a) {
    case 1:
        type = easy;
        break;
    case 2:
        type = normal;
        break;
    case 3:
        type = hard;
        break;
    }
    height = sizes.first;
    width = sizes.second;
    countSecret = height * width;
    field = new FieldPoint[height * width];
    for (unsigned i = 0; i < height; i++) {
        for (unsigned j = 0; j < width; j++) {
            FieldPoint& point = field[i * height + j];
            point.setX(i);
            point.setY(j);
        }
    }
}


Field::~Field() { delete[] field; }


int Field::openPoint(const Point& p) {
    FieldPoint& point = field[p.getX() * height + p.getY()];
    if (point.isMineInside()) { return -1; }

    if (point.getNumber() == 0) {
        point.setSymbol(' ');
        countSecret--;
    }
    else {
        point.setSymbol(static_cast<char>('0' + point.getNumber()));
        countSecret--;
    }
    if (point.getNumber() == 0) openEmpty(point);
    return 0;
}

void Field::setMines(const unsigned amount, const Point* mines) {
    for (unsigned i = 0; i < amount; i++) {
        field[mines[i].getX() * height + mines[i].getY()].setMine();

        if (mines[i].getY() >= 1) field[mines[i].getX() * height + mines[i].getY() - 1].upNumber();
        if (mines[i].getY() + 1 < width) field[mines[i].getX() * height + mines[i].getY() + 1].upNumber();
        if (mines[i].getX() + 1 < height) field[(mines[i].getX() + 1) * height + mines[i].getY()].upNumber();
        if (mines[i].getX() >= 1) field[(mines[i].getX() - 1) * height + mines[i].getY()].upNumber();
        if (mines[i].getX() + 1 < height && mines[i].getY() >= 1) field[(mines[i].getX() + 1) * height + mines[i].getY() - 1].upNumber();
        if (mines[i].getX() + 1 < height && mines[i].getY() + 1 < width) field[(mines[i].getX() + 1) * height + mines[i].getY() + 1].upNumber();
        if (mines[i].getX() >= 1 && mines[i].getY() >= 1) field[(mines[i].getX() - 1) * height + mines[i].getY() - 1].upNumber();
        if (mines[i].getX() >= 1 && mines[i].getY() + 1 < width) field[(mines[i].getX() - 1) * height + mines[i].getY() + 1].upNumber();
    }
}

void Field::print() const {
    std::cout << "  ";
    for (unsigned i = 0; i < width; i++) { std::cout << i << " "; }
    std::cout << "y";
    std::cout << std::endl << "0 ";
    for (unsigned i = 0; i < height; i++) {
        for (unsigned j = 0; j < width; j++) {
            std::cout << field[i * height + j].getSymbol() << " ";
        }
        (i < height - 1) ? std::cout << std::endl << i + 1 << " " : std::cout << std::endl << 'x';
    }
    std::cout << std::endl;
}

void Field::printAll() const {
    std::cout << "  ";
    for (unsigned i = 0; i < width; i++) { std::cout << i << " "; }
    std::cout << "y";
    std::cout << std::endl << "0 ";
    for (unsigned i = 0; i < height; i++) {
        for (unsigned j = 0; j < width; j++) {
            if (field[i * height + j].isMineInside()) {
                std::cout << "* ";
                continue;
            }
            std::cout << field[i * height + j].getNumber() << " ";
        }
        (i < height - 1) ? std::cout << std::endl << i + 1 << " " : std::cout << std::endl << 'x';
    }
    std::cout << std::endl;
}

unsigned Field::getMaxHeight() const { return maxHeight; }
unsigned Field::getMaxWidth() const { return maxWidth; }
unsigned Field::getMinHeight() const { return minHeight; }
unsigned Field::getMinWidth() const { return minWidth; }
unsigned Field::getHeight() const { return height; }
unsigned Field::getWidth() const { return width; }
unsigned Field::getType() const { return type; }
unsigned Field::getCountSecret() const { return countSecret; }


void Field::tryOpenEmpty(const int x, const int y) {
    if (x < 0 || x >= width || y < 0 || y >= height)
        return;

    auto& cell = field[x * height + y];

    if (cell.getSymbol() == '#' && cell.getNumber() == 0) {
        cell.setSymbol(' ');
        countSecret--;
        openEmpty(cell);
    }
    if (cell.getSymbol() == '#' && cell.getNumber() < 9 && cell.isMineInside() == 0) {
        cell.setSymbol(static_cast<char>('0' + cell.getNumber()));
        countSecret--;
    }
}


void Field::openEmpty(const FieldPoint& point) {
    int x = point.getX();
    int y = point.getY();

    tryOpenEmpty(x, y - 1);
    tryOpenEmpty(x, y + 1);
    tryOpenEmpty(x - 1, y);
    tryOpenEmpty(x + 1, y);
    tryOpenEmpty(x - 1, y - 1);
    tryOpenEmpty(x - 1, y + 1);
    tryOpenEmpty(x + 1, y - 1);
    tryOpenEmpty(x + 1, y + 1);
}