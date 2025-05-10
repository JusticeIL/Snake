#include <iostream>
#include <random>
#include <chrono>
#include "Apple.h"
#include "HelperFunc.h"
#include "Snake.h"

void Apple::reposition(const Snake& snake) {

    //Random position
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distX(1, Board::width() - 2);
    std::uniform_int_distribution<> distY(1, Board::height() - 2);

    const std::vector<COORD>& snakeBody = snake.getBody();
    bool overlap = true; //Temporary

    while (overlap)
    {
        x = distX(gen);
        y = distY(gen);
        overlap = false;

        
        for (const COORD& part : snakeBody) {
            if (part.X == x && part.Y == y) { //Case: the new position of the apple falls on the snake's body
                overlap = true;
                break;
            }
        }

    }
}

COORD Apple::getPosition() const {
    COORD res;
    res.X = static_cast<SHORT>(x);
    res.Y = static_cast<SHORT>(y);
    return res;
}

void Apple::draw(Board& board) const {
    gotoxy(x, y);
    board.setChar(x, y, appleIcon);
    std::cout << color << appleIcon << RESET;
}

void Apple::erase(Board& board) const {
    gotoxy(x, y);
    board.setChar(x, y, EMPTY_CHAR);
    std::cout << EMPTY_CHAR;
}

void Apple::changeAppleColor(const Snake& snake) {

    color = (snake.getColor() == std::string(RED)) ? GREEN : RED;
}