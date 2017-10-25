#include <iostream>
#include <cstddef>
#include <string>
#include <vector>
#include <stdlib.h>
#include <time.h>

const short BLACK = 1;
const short WHITE = 2;
const short SPACE = 0;

struct Position {
    short x;
    short y;

    Position(short inX, short inY);
};

struct Decision {
    short x;
    short y;
    int rate;
    bool isReal;

    Decision(short inX = 0, short inY = 0, int inRate = 0);
    void update(short inX, short inY, int inRate);
};

class Board {
private:
    short matrix[8][8];
    // 1 - играем за черных, 2 - играем за белых
    short color;

    bool ableToPlaceColorByDirection(short x, short y, short xPlus, short yPlus, short placeColor);
    bool ableToPlaceColor(short x, short y, short placeColor);
    bool colorMayGo(short inColor);
    void placeColorByDirection(short x, short y, short xPlus, short yPlus, short placeColor);
    short opponentColor();
    short otherColor(short inColor);
    int decisionRate(short x, short y);
    size_t colorNumber();
    size_t opponentColorNumber();
    int boardRate();
    bool region1(short x, short y);
    bool region2(short x, short y);
    bool region3(short x, short y);
    bool region4(short x, short y);
    bool region5(short x, short y);

    std::vector<Position> getPositionsForColor(short inColor);
    int randomGame(Position position);                          // Выиграна рандомная игра или нет
    int randomRate(Position position, size_t number = 200);  // Количество выигранны рандомных игр из number
    void setInMatrix(short i, short j, short value);

public:
    // Конструктор доски. true - играем черными, false - играем белыми
    Board(bool isBlack);
    // Меняет доску в зависимости от хода противника. (x, y) - координаты в которые сходил противник
    void makeDecision();
    void showMatrix();
    void placeColor(short x, short y, short placeColor);
};

bool Board::region5(short x, short y) {
    return (((x == 0) || (x == 7)) && ((y == 0) || (y == 7)));
}

bool Board::region1(short x, short y) {
    return (x >= 2) && (x <= 5) && (y >= 2) && (y <= 5);
}

bool Board::region4(short x, short y) {
    return ((x == 1) || (x == 6)) && ((y == 0) || (y == 1) || (y == 6) || (y == 7)) || (((x == 0) || (x == 7)) && ((y == 0) || (y == 7)));
}

bool Board::region3(short x, short y) {
    return ((x == 0) || (x == 7) || (y == 0) || (y == 7)) && !region4(x, y) && !region5(x, y);
}

bool Board::region2(short x, short y) {
    return ((x == 1) || (x == 6) || (y == 1) || (y == 6)) && !region4(x, y);
}


std::vector<Position> Board::getPositionsForColor(short inColor) {
    std::vector<Position> result;
    for (short x = 0; x < 8; ++x) {
        for (short y = 0; y < 8; ++y) {
            if (ableToPlaceColor(x, y, inColor)) {
                result.push_back(Position(x, y));
            }
        }
    }
    return result;
}

void Board::setInMatrix(short i, short j, short value) {
    matrix[i][j] = value;
}

int Board::randomGame(Position position) {
    Board tempBoard(color == BLACK);
    for (short i = 0; i < 8; ++i) {
        for (short j = 0; j < 8; ++j) {
            tempBoard.setInMatrix(i, j, matrix[i][j]);
        }
    }
    tempBoard.placeColor(position.x, position.y, color);
    short movingColor = opponentColor();
    while (true) {
        if (tempBoard.colorMayGo(movingColor)) {
            //std::vector<Position> positions = tempBoard.getPositionsForColor(movingColor);

            std::vector<Position> positions;
            for (short x = 0; x < 8; ++x) {
                for (short y = 0; y < 8; ++y) {
                    if (tempBoard.ableToPlaceColor(x, y, movingColor)) {
                        positions.push_back(Position(x, y));
                    }
                }
            }

            size_t position = rand() % positions.size();
            tempBoard.placeColor(positions[position].x, positions[position].y, movingColor);
            movingColor = otherColor(movingColor);
        } else if (tempBoard.colorMayGo(otherColor(movingColor))) {
            //std::vector<Position> positions = tempBoard.getPositionsForColor(otherColor(movingColor));

            std::vector<Position> positions;
            for (short x = 0; x < 8; ++x) {
                for (short y = 0; y < 8; ++y) {
                    if (tempBoard.ableToPlaceColor(x, y, otherColor(movingColor))) {
                        positions.push_back(Position(x, y));
                    }
                }
            }

            size_t position = rand() % positions.size();
            tempBoard.placeColor(positions[position].x, positions[position].y, otherColor(movingColor));
        } else {
            break;
        }
    }
    return tempBoard.boardRate();
}

int Board::randomRate(Position position, size_t number){
    int randomGamesRate = 0;
    for (size_t i = 0; i < number; ++i) {
         randomGamesRate += randomGame(position);
    }
    return randomGamesRate;
}

Position::Position(short inX, short inY) : x(inX), y(inY) {}

Decision::Decision(short inX, short inY, int inRate) : x(inX), y(inY), rate(inRate), isReal(false) {}

void Decision::update(short inX, short inY, int inRate) {
    if (!isReal) {
        x = inX;
        y = inY;
        rate = inRate;
    } else if (inRate > rate) {
        x = inX;
        y = inY;
        rate = inRate;
    }
    isReal = true;
}

int Board::decisionRate(short x, short y) {
    int rank = randomRate(Position(x, y));
    if (region5(x, y)) {
        rank += 50;
    } else if (region4(x, y)) {
        rank -= 50;
    } else if (region3(x, y)) {
        rank += 20;
    } else if (region2(x, y)) {
        rank -= 20;
    }
    return rank;
}

int Board::boardRate() {
    int rate = 0;
    for (short i = 0; i < 8; ++i) {
        for (short j = 0; j < 8; ++j) {
            if (matrix[i][j] == color) {
                ++rate;
            } else if (matrix[i][j] == opponentColor()) {
                --rate;
            }
        }
    }
    return rate;
}

size_t Board::colorNumber() {
    size_t counter = 0;
    for (size_t i = 0; i < 8; ++i) {
        for (size_t j = 0; j < 8; ++j) {
            if (matrix[i][j] == color) {
                ++counter;
            }
        }
    }
    return counter;
}

size_t Board::opponentColorNumber() {
    size_t counter = 0;
    for (size_t i = 0; i < 8; ++i) {
        for (size_t j = 0; j < 8; ++j) {
            if (matrix[i][j] == opponentColor()) {
                ++counter;
            }
        }
    }
    return counter;
}

void Board::showMatrix() {
    std::cout << std::endl;
    for (short i = 0; i < 8; ++i) {
        for (short j = 0; j < 8; ++j) {
            std::cout << matrix[j][i] << " ";
        }
        std::cout << std::endl;
    }
}

Board::Board(bool isBlack) {
    for (size_t i = 0; i < 8; ++i) {
        for(size_t j = 0; j < 8; ++j) {
            matrix[i][j] = SPACE;
        }
    }
    matrix[4][3] = BLACK;
    matrix[3][4] = BLACK;
    matrix[3][3] = WHITE;
    matrix[4][4] = WHITE;
    if (isBlack) {
        color = BLACK;
    } else {
        color = WHITE;
    }
}

short Board::opponentColor() {
    if (color == BLACK) {
        return WHITE;
    } else {
        return BLACK;
    }
}

short Board::otherColor(short inColor) {
    if (inColor == BLACK) {
        return WHITE;
    } else {
        return BLACK;
    }
}

void Board::makeDecision() {
    Decision maxDecision;
    for (short x = 0; x < 8; ++x) {
        for (short y = 0; y < 8; ++y) {
            if (ableToPlaceColor(x, y, color)) {
                maxDecision.update(x, y, decisionRate(x, y));
            }
        }
    }
    placeColor(maxDecision.x, maxDecision.y, color);
    std::cout << "move " << (char)('a' + maxDecision.x) << " " << maxDecision.y + 1 << std::endl;
}

bool Board::ableToPlaceColorByDirection(short x, short y, short xPlus, short yPlus, short placeColor) {
    if ((xPlus == 0) && (yPlus == 0)) {
        return false;
    }
    if (matrix[x][y] == SPACE) {
        size_t counter = 0, currentX = x + xPlus, currentY = y + yPlus;
        while ((currentY < 8) && (currentX < 8) && (currentY >= 0) && (currentX >= 0) && (matrix[currentX][currentY] == otherColor(placeColor))) {
            currentX += xPlus;
            currentY += yPlus;
            ++counter;
        }
        if ((currentY < 8) && (currentX < 8) && (currentX >= 0) && (currentY >= 0) && (matrix[currentX][currentY] == placeColor) && (counter > 0)) {
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}

bool Board::ableToPlaceColor(short x, short y, short placeColor) {
    for (int xPlus = -1; xPlus <= 1; ++xPlus) {
        for (int yPlus = -1; yPlus <= 1; ++yPlus) {
            if (!((yPlus == 0) && (xPlus == 0))) {
                if (ableToPlaceColorByDirection(x, y, xPlus, yPlus, placeColor)) {
                    return true;
                }
            }
        }
    }
    return false;
}

bool Board::colorMayGo(short inColor) {
    for (short x = 0; x < 8; ++x) {
        for (short y = 0; y < 8; ++y) {
            if (ableToPlaceColor(x, y, inColor)) {
                return true;
            }
        }
    }
    return false;
}


void Board::placeColorByDirection(short x, short y, short xPlus, short yPlus, short placeColor) {
    size_t currentX = x + xPlus, currentY = y + yPlus;
    while ((currentY < 8) && (currentX < 8) && (currentY >= 0) && (currentX >= 0) && (matrix[currentX][currentY] == otherColor(placeColor))) {
        matrix[currentX][currentY] = placeColor;
        currentX += xPlus;
        currentY += yPlus;
    }
}

void Board::placeColor(short x, short y, short placeColor) {
    for (int xPlus = -1; xPlus <= 1; ++xPlus) {
        for (int yPlus = -1; yPlus <= 1; ++yPlus) {
            if (!((yPlus == 0) && (xPlus == 0))) {
                if (ableToPlaceColorByDirection(x, y, xPlus, yPlus, placeColor)) {
                    placeColorByDirection(x, y, xPlus, yPlus, placeColor);
                }
            }
        }
    }
    matrix[x][y] = placeColor;
}

int main() {
    srand (time(NULL));
    std::string input;
    std::getline(std::cin, input);
    short opponentColor;
    if (input == "init black") {
        opponentColor = WHITE;
    } else {
        opponentColor = BLACK;
    }
    Board board(input == "init black");
    std::getline(std::cin, input);
    while ((input != "win") && (input != "lose") && (input != "draw") && (input != "bad")) {
        if (input != "") {
            if (input == "turn") {
                board.makeDecision();
            } else {
                board.placeColor(short(input[5] - 'a'), short(input[7] - '1'), opponentColor);
            }
        }
        std::getline(std::cin, input);
    }
    return 0;
}
