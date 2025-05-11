#include <iostream>
#include <random>
#include <chrono>
#include "Apple.h"
#include "HelperFunc.h"
#include "Snake.h"

//This function repositions the apple to a random location on the board that does not overlap with the snake's body
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

//This function returns the current position of the apple as a COORD structure
COORD Apple::getPosition() const {

    COORD res;
    res.X = static_cast<SHORT>(x);
    res.Y = static_cast<SHORT>(y);
    return res;
}

//This function draws the apple at its current position on the board and on screen using its assigned color
void Apple::draw(Board& board) const {

    gotoxy(x, y);
    board.setChar(x, y, appleIcon);
    std::cout << color << appleIcon << RESET;
}

//This function erases the apple from its current position on the board and on screen
void Apple::erase(Board& board) const {

    gotoxy(x, y);
    board.setChar(x, y, EMPTY_CHAR);
    std::cout << EMPTY_CHAR;
}

//This function changes the color of the apple to green if the snake is red and changes the color of the apple to red otherwise
void Apple::changeAppleColor(const Snake& snake) {

    color = (snake.getColor() == std::string(RED)) ? GREEN : RED;
}