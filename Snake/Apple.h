#pragma once
#include <iostream>
#include <windows.h>
#include "Colors.h"
#include "Board.h"

//Forward declaration
class Snake;

class Apple
{
	static constexpr char appleIcon = 'O';
	static constexpr char EMPTY_CHAR = ' ';

	static constexpr int max = ((Board::height() - 2)*(Board::width() - 2)) - 1; //Subtract the snake head at the start

	//Data Members
	int x;
	int y;
	std::string color = RED;
	int count = 0;

public:
	Apple(int X, int Y) : x(X), y(Y) {} //Constructor

	COORD getPosition() const;
	void resetPosition() { x = 0; y = 0; }
	void reposition(const Snake& snake);
	void draw(Board& board) const;
	void erase(Board& board) const;

	void changeAppleColor(const Snake& snake);

	void resetAppleCount() { count = 0; }
	void increaseAppleCount() { count++; }

	bool checkWinCon() const { return count == max-1; }

	static constexpr char getAppleIcon() { return appleIcon; }
};

