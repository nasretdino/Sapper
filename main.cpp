#include <iostream>
#include "Field.h"
#include "Mines.h"


using std::cout;
using std::cin;
using std::endl;


class Game {
    Field field;

public:
    Game() = default;

    void start() {
        field.create(selectGameType(), selectFieldSizes());
        Point startPoint;
        selectStartPoint(startPoint);
        Mines mines;
        mines = { field.getHeight(), field.getWidth(), startPoint, field.getType() };
        field.setMines(mines.getAmount(), mines.getMines());
        cout << "There are " << mines.getAmount() << " mines" << endl;
        field.openPoint(startPoint);
        waiting(); // Добавить течение времени, чтобы в конце показывалось

        field.print();
        bool winFlag = false;
        Point nextPoint;
        cin >> nextPoint; // Добавить возможность ставить флаги
        checkPoint(nextPoint);
        while (field.openPoint(nextPoint) != -1) {
            if (field.getCountSecret() == mines.getAmount()) {
                winFlag = true;
                break;
            }
            field.print();
            cin >> nextPoint;
            checkPoint(nextPoint);
        }
        if (winFlag) cout << "You win!" << endl;
        else {
            field.printAll();
            cout << "You lose!" << endl;
        }
    }

private:
    unsigned selectGameType() const {
        cout << "Input game type" << endl;
        cout << "1. Easy" << endl << "2. Normal" << endl << "3. Hard" << endl;
        unsigned a;
        cin >> a;
        checkArgument(a);
        if (a == 1) {
            cout << "You chose easy level." << endl;
        }
        else if (a == 2) {
            cout << "You chose normal level." << endl;
        }
        else {
            cout << "You chose hard level." << endl;
        }
        return a;
    }

    std::pair<unsigned, unsigned> selectFieldSizes() const {
        cout << "Select the height of the field." << endl <<
            "Max: " << field.getMaxHeight() << ", " << "min:" << field.getMinHeight() << endl;
        unsigned height;
        cin >> height;

        cout << "Select the width of the field." << endl <<
            "Max: " << field.getMaxWidth() << ", " << "min:" << field.getMinWidth() << endl;
        unsigned width;
        cin >> width;

        std::pair<unsigned, unsigned> sizes(height, width);

        checkArgument(sizes);
        return sizes;
    }

    void selectStartPoint(Point& startPoint) {
        cout << "Input start point:" << endl << "X must be in [ 0; " <<
            field.getHeight() - 1 << " ]:" << endl << "Y must be in [ 0; " <<
            field.getWidth() - 1 << " ]:" << endl;
        cin >> startPoint;

        try {
            checkPoint(startPoint);
        }
        catch (std::invalid_argument& e) {
            std::cerr << "Eror: " << e.what() << endl;
            std::exit(EXIT_FAILURE);
        }
    }

    void waiting() {
        cout << "Input w to start" << endl;
        char a;
        do {
            cin >> a;
        } while (a != 'w');
    }

    void checkPoint(const Point& point) const {
        if (point.getX() > field.getHeight() || point.getX() < 0 || point.getY() > field.getWidth() || point.getY() < 0) {
            throw std::invalid_argument("Invalid input out of field index");
        }
    }

    void checkArgument(const unsigned a) const {
        if (a != 1 && a != 2 && a != 3) { throw std::invalid_argument("Wrong game type"); }
    }

    void checkArgument(const std::pair<unsigned, unsigned>& sizes) const {
        if (sizes.first > field.getMaxHeight() || sizes.first < field.getMinHeight() ||
            sizes.second > field.getMaxWidth() || sizes.second < field.getMinWidth()) {
            throw std::invalid_argument("Wrong sizes");
        }
    }
};


int main() {
    Game game;
    game.start();
    return 0;
}
