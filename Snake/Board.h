#pragma once

class Board
{
	//Constants
	static constexpr int WIDTH = 80;
	static constexpr int HEIGHT = 25;

	//Board representation and game state
	char Level[HEIGHT][WIDTH + 1] = {};
	bool paused = false;

public:
	Board() { //Constructor
		//Fill the board with spaces and add boundaries
		for (int y = 0; y < HEIGHT; y++)
		{
			for (int x = 0; x < WIDTH; x++)
			{
				if (y == 0 || y == HEIGHT - 1)
					Level[y][x] = (x == 0 || x == WIDTH - 1) ? '|' : '=';
				else
				{
					Level[y][x] = (x == 0 || x == WIDTH - 1) ? '|' : ' ';
				}
			}
			Level[y][WIDTH] = '\0'; //Add the null-terminating to make it a string
		}
	}
	//Board dimensions getters
	static constexpr int width() { return WIDTH; }
	static constexpr int height() { return HEIGHT; }

	//Pausing logic
	void pause() { paused = true; }
	void unpause() { paused = false; }

	//Drawing and Resets
	void print() const;
	void setChar(int x, int y, char ch);
	void resetBoard();
};