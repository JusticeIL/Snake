#include <iostream>
#include "Colors.h"
#include "HelperFunc.h"
#include "Snake.h"
#include "Apple.h"

constexpr char Snake::keys[];

void Snake::move() {
	if (isDead) return;

	COORD newHead = body.front();
	const Direction& dir = directions[static_cast<int>(currentDir)];
	newHead.X += dir.x;
	newHead.Y += dir.y;

	body.insert(body.begin(), newHead);

	//Check if Snake ate the apple
	if (growNextMove) //Case: Snake ate the apple so skip losing your tail
		growNextMove = false;
	else //Case: Snake didn't eat the apple
		body.pop_back();
}

void Snake::draw(Board& board) const {
	for (const auto& part : body) {
		gotoxy(part.X, part.Y);
		board.setChar(part.X, part.Y, snakeIcon);
		std::cout << color << snakeIcon << RESET;
	}
}

void Snake::erase(Board& board) const
{
	COORD tail = body.back();
	gotoxy(tail.X, tail.Y);
	board.setChar(tail.X, tail.Y, PrevCh);
	std::cout << PrevCh;
}

void Snake::resetSnake() {
	resetSnakePos();
	currentDir = Directions::RIGHT; //Inital the direction again
	isDead = false;
}

void Snake::resetSnakePos() {

	int width90 = static_cast<int>(Board::width() * 0.9);
	int height90 = static_cast<int>(Board::height() * 0.9);
	int xOffset = (Board::width() - width90) / 2;
	int yOffset = (Board::height() - height90) / 2;

	int startX = xOffset + rand() % width90;
	int startY = yOffset + rand() % height90;

	COORD start = {startX, startY};
	body.clear(); //Empties the body
	body.push_back(start);
}

bool Snake::checkAndEatApple(const Apple& apple) {
	if (body.front().X == apple.getPosition().X && body.front().Y == apple.getPosition().Y) {
		growNextMove = true;
		return true;
	}
	return false;
}

//This function returns true if the snake is in a valid state after movement or false otherwise
bool Snake::isValid() {
	const COORD& head = body.front();

	//Wall collision check
	if (head.X <= 0 || head.X >= Board::width() - 1 || head.Y <= 0 || head.Y >= Board::height() - 1) { //Case: Snake is out of bounds
		isDead = true;
		return false;
	}

	//Check collision with body
	//Self-collision check (skip head by starting from body.begin() + 1)
	for (auto it = body.begin() + 1; it != body.end(); ++it) {
		if (it->X == head.X && it->Y == head.Y) { //Case: collision with body detected
			isDead = true;
			return false;
		}
	}

	return true;
}

void Snake::setPressedKey(char key) {

	key = std::tolower(key);

	for (int i = 0; i < 4; ++i) {
		if (key == keys[i]) {
			Directions newDir = static_cast<Directions>(i);
			
			if ((static_cast<int>(newDir) + static_cast<int>(currentDir)) % 2 != 0) { //Prevent reversing direction (e.g., RIGHT to LEFT)
				currentDir = newDir;
			}
			else //Clean buffer for smoother gameplay
			{
				std::cin.clear();
				fflush(stdin);
			}
			break;
		}
	}
}

void Snake::setColor(const std::string& name) {

	//Assuming name comes in lowercase
	colorName = name;

	if (name == "red")				color = RED;
	else if (name == "green")		color = GREEN;
	else if (name == "yellow")		color = YELLOW;
	else if (name == "blue")		color = BLUE;
	else if (name == "grey")		color = GREY;
	else if (name == "pink")		color = PINK;
	else if (name == "cyan")		color = CYAN;
	else if (name == "white")		color = WHITE;
	else if (name == "purple")		color = PURPLE;
	else if (name == "violet")		color = VIOLET;
	else if (name == "navy blue")   color = NAVY_BLUE;
	else if (name == "gold")		color = GOLD;
	else							color = GREEN; //Fallback
}