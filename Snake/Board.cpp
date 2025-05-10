#include <iostream>
#include <algorithm>
#include "Board.h"
#include "Snake.h"
#include "Apple.h"

void Board::print() const {
	for (int y = 0; y < HEIGHT-1; y++)
		std::cout << Level[y] << std::endl;

	std::cout << Level[HEIGHT-1];
}

void Board::setChar(int x, int y, char ch) {

	if (y > 0 && y < HEIGHT - 1 && x > 0 && x < WIDTH - 1) {
		Level[y][x] = ch;
	}
}

void Board::resetBoard() {
	std::replace(&Level[0][0], &Level[0][0] + HEIGHT * (WIDTH + 1), Apple::getAppleIcon(), ' ');
	std::replace(&Level[0][0], &Level[0][0] + HEIGHT * (WIDTH + 1), Snake::getSnakeIcon(), ' ');
}