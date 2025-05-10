#pragma once
#include <vector>
#include <windows.h>
#include "Colors.h"

//Forward declarations
class Apple;
class Board;

enum class Directions { UP, LEFT, DOWN, RIGHT };

class Snake
{
	//Constants
	static constexpr char keys[] = { 'w', 'a', 's', 'd' };
	static constexpr char snakeIcon = ' ';
	static constexpr char PrevCh = ' ';

	//Directions
	struct Direction { int x, y; };
	static constexpr Direction directions[] = { {0, -1}, {-1, 0}, {0, 1}, {1, 0} };

	//Data Memebers
	std::vector<COORD> body;
	Directions currentDir = Directions::RIGHT; //Initial Direction
	bool isDead = false;
	std::string color = GREEN;
	std::string colorName = "green";
	bool growNextMove = false;

public:

	//Movement Management
	void move();
	void draw(Board& board) const;
	void erase(Board& board) const;
	bool isValid();

	//Rest and Initialization
	void resetLife() { isDead = false; }
	void resetSnake();
	void resetSnakePos();

	//Key Handling
	void setPressedKey(char key);

	//Apple Interaction
	bool checkAndEatApple(const Apple& apple);

	//Getters
	bool isSnakeDead() const { return isDead; }
	std::string getColor() const { return color; }
	std::string getColorName() const { return colorName; }
	const std::vector<COORD>& getBody() const { return body; }
	static constexpr char getSnakeIcon() { return snakeIcon; }

	//Color Handling
	void setColor(const std::string& name);
};