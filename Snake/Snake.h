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

	void move();
	void draw(Board& board) const;
	void erase(Board& board) const;

	void resetLife() { isDead = false; }
	bool isSnakeDead() const { return isDead; }

	void resetSnake();
	void resetSnakePos();

	void setPressedKey(char key);

	bool checkAndEatApple(const Apple& apple);

	std::string getColor() const { return color; }
	std::string getColorName() const { return colorName; }

	void setColor(const std::string& name);

	const std::vector<COORD>& getBody() const { return body; }

	bool isValid();

	static constexpr char getSnakeIcon() { return snakeIcon; }
};

