#include "Mines.h"


bool Mines::checkMine(const Point& startPoint, const int& i) const {
    if (mines[i] == startPoint) { return true; }
    for (int j = 0; j < i; j++)
        if (mines[j] == mines[i]) { return true; }
    return false;
}

Mines::Mines(const unsigned height, const unsigned width, const Point& startPoint, const unsigned minePercent) {
    amount = static_cast<unsigned>(height * width * (static_cast<double>(minePercent) / 100));
    mines = new Point[amount];

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<int> dist_height(0, static_cast<int>(height - 1));
    std::uniform_int_distribution<int> dist_width(0, static_cast<int>(width - 1));

    for (int i = 0; i < amount; i++) {
        do {
            mines[i].setX(dist_height(rng));
            mines[i].setY(dist_width(rng));
        } while (checkMine(startPoint, i));
    }
}

Mines::Mines(const Mines& right) {
    mines = new Point[right.amount];
    for (int i = 0; i < right.amount; i++) {
        mines[i] = right.mines[i];
    }
    amount = right.amount;
}

Mines::~Mines() {
    delete[] mines;
}

Mines& Mines::operator=(const Mines& right) {
    if (this == &right) { return *this; }
    delete[] mines;
    mines = new Point[right.amount];
    for (int i = 0; i < right.amount; i++) {
        mines[i] = right.mines[i];
    }
    amount = right.amount;
    return *this;
}

void Mines::print() const {
    for (int i = 0; i < amount; i++) {
        std::cout << mines[i] << std::endl;
    }
}

const Point* Mines::getMines() const { return mines; }
unsigned Mines::getAmount() const { return amount; }