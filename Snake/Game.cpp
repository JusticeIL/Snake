#pragma comment(lib, "Winmm.lib")
#include <conio.h>
#include <map>
#include "Game.h"
#include "Menu.h"
#include "Board.h"
#include "Snake.h"
#include "Apple.h"
#include "HelperFunc.h"

//This function manages the main game loop, handles transitions between different game states, and coordinates user inputs and game actions
void Game::run() {

	menu.print();
	char pressedKey = '\0';

	while (State != GameState::Exit) //Game loop runs as long as ESC key wasn't pressed
	{ 
		if (State == GameState::Standby)
		{
			choiceHolder = menu.handleMenu();
			switch (choiceHolder) {
			case play: //Start game
				State = GameState::Playing;
				choiceHolder = '\0';
				menu.ResetMenu();
				menu.resetAllArrows();
				if (music)
					playBackgroundMusic();
				firstPrint = true;
				break;
			case instructions: //Instructions
				State = GameState::Instructions;
				choiceHolder = '\0';
				menu.ResetMenu();
				menu.resetAllArrows();
				firstPrint = true;
				break;
			case options: //Options
				State = GameState::Options;
				choiceHolder = '\0';
				menu.ResetMenu();
				menu.resetAllArrows();
				firstPrint = true;
				break;
			case quit: //Exit
				clearScr();
				State = GameState::Exit;
				playExitSound();
				break;
			}
		}

		if (State == GameState::Playing)
			playGame();
		else if (State == GameState::Pause)
		{
			printPauseScreen();
			board.pause();
			if (_kbhit())
			{
				pressedKey = _getch();
				if (pressedKey == ESC) { //Unpause only after ESC
					terminatePause();
					State = GameState::Playing;
				}
			}
		}
		else if (State == GameState::Colors)
		{
			choiceHolder = '\0';
			menu.ResetMenu();
			menu.resetAllArrows();
			firstPrint = true;
			gotoxy(0, 0);
			std::cout << ColorsScreen;
			handleColors();
		}
			
		else if (State == GameState::GameOver)
			gameOverLogic();
		
		else if (State == GameState::GameWon)
			gameWonLogic();

		if (State != GameState::Playing && State != GameState::Standby) //Case: menu screens
		{
			printScreens();
			handleState();
		}
		
	}
}

//This function displays the appropriate screen (instructions, options, colors) based on the current game state
void Game::printScreens() {

	switch (State)
	{
		case GameState::Instructions:
		case GameState::Options:
		case GameState::Colors:
		{
			menu.ChangeMenuChar('\0');
			break;
		}
	}

	if (firstPrint)
	{
		clearScr(); //Clear the console
		gotoxy(0, 0);

		switch (State)
		{
			case GameState::Instructions:
				std::cout << instructionsScreen;
				break;

			case GameState::Options:
				std::cout << optionsScreen;

				//Difficulty printing
				if (difficultylevel == EASY)
					gotoxy(56,6);
				else //Case: difficultylevel == HARD
					gotoxy(56,7);
				std::cout << "<--";

				//Music state printing
				gotoxy(41, 8);
				if (music == OFF)
					std::cout << "Off";
				else //Case: music == ON
					std::cout << "On";

				break;

			case GameState::Colors:
				std::cout << ColorsScreen;
				break;
		}
		firstPrint = false;
	}
}

//This function processes user inputs and updates the game state accordingly during non-gameplay states
void Game::handleState() {

	static DWORD messageTimestamp = 0;
	static bool messageOnScreen = false;

	if (_kbhit()) {
		char pressedKey = _getch();
		pressedKey = tolower(pressedKey);
		menu.ChangeMenuChar(pressedKey);

		switch (State)
		{
			case GameState::Instructions:
				if (pressedKey == ESC) //Case: returning to main menu
				{
					menu.ResetMenu(); //Reseting menu variables
					firstPrint = true;
					clearScr(); //Clear the screen before returning to the menu
					menu.print(); //Display menu again
					State = GameState::Standby;
					menu.resetAllArrows();
				}
				break;

			case GameState::Options:
				
				if (pressedKey == '1')
				{
					State = GameState::Colors;
					clearScr(); //Clear the screen
					firstPrint = true;
				}
				else if (pressedKey == (EASY + '0'))
				{
					gotoxy(28, 10);
					if (difficultylevel == EASY)
					{
						gotoxy(28, 10);
						std::cout << std::string(30, ' '); //Clear message
						gotoxy(28, 10);
						messageOnScreen = true;
						std::cout << YELLOW_TXT << "Difficulty already selected" << RESET_TXT;
						messageTimestamp = GetTickCount();
					}
					else
					{
						gotoxy(56, 7);
						std::cout << std::string(3, ' ');
						gotoxy(56, 6);
						std::cout << "<--";
						messageOnScreen = true;
						gotoxy(28, 10);
						std::cout << std::string(30, ' '); //Clear message
						printOKInGreen(28, 10);
						messageTimestamp = GetTickCount();
					}
					difficultylevel = EASY;
				}
				else if (pressedKey == (HARD + '0'))
				{
					gotoxy(28, 10);
					if (difficultylevel == HARD)
					{
						gotoxy(28, 10);
						std::cout << std::string(30, ' '); //Clear message
						gotoxy(28, 10);
						messageOnScreen = true;
						std::cout << YELLOW_TXT << "Difficulty already selected" << RESET_TXT;
						messageTimestamp = GetTickCount();
					}
					else
					{
						gotoxy(56, 6);
						std::cout << std::string(3, ' ');
						gotoxy(56, 7);
						std::cout << "<--";
						messageOnScreen = true;
						gotoxy(28, 10);
						std::cout << std::string(30, ' '); //Clear message
						printOKInGreen(28, 10);
						messageTimestamp = GetTickCount();
					}
					difficultylevel = HARD;
				}
				else if (pressedKey == musicKey)
				{
					music = !music;
					gotoxy(41, 8);
					std::cout << std::string(3, ' ');
					gotoxy(41, 8);
					if (music == OFF)
						std::cout << "Off";
					else
						std::cout << "On";

				}
				else if (pressedKey == ESC) //Case: returning to main menu
				{
					menu.ResetMenu(); //Reseting menu variables
					firstPrint = true;
					clearScr(); //Clear the screen before returning to the menu
					menu.print(); //Display menu again
					State = GameState::Standby;
					menu.resetAllArrows();
				}
				break;
		}
	}

	if (messageOnScreen && GetTickCount() - messageTimestamp >= 2000)
	{
		gotoxy(27, 10);
		std::cout << std::string(30, ' '); //Clear message
		messageOnScreen = false;
	}

}

//This function initiates the gameplay, manages the snake movement, collision checks, and apple interactions
void Game::playGame() {

	COORD applePos = apple.getPosition();
	if (applePos.X == 0 && applePos.Y == 0) //Case: apple position not initialized
	{
		apple.resetAppleCount();
		apple.reposition(snake);
	}

	if (firstPrint)
	{
		clearScr();
		board.unpause();
		board.print();
		snake.draw(board); //Print snake in color
		apple.changeAppleColor(snake); //Set apple color based on snake
		apple.draw(board);
		firstPrint = false;
	}

	//Handle user input
	if (_kbhit())
	{
		char key = _getch();
		if (key == ESC)
		{
			State = GameState::Pause;
			return;
		}

		snake.setPressedKey(key);
	}

	//Move the snake
	snake.erase(board);
	snake.move();

	//Check collisions
	if (!snake.isValid())
	{
		if (music)
			stopBackgroundMusic();
		State = GameState::GameOver;
		return;
	}

	//Check apple collision
	if (snake.checkAndEatApple(apple))
	{
		apple.increaseAppleCount();
		apple.erase(board);
		apple.reposition(snake);
	}

	//Check win condition
	if (apple.checkWinCon())
	{
		if (music)
			stopBackgroundMusic();
		State = GameState::GameWon;
		return;
	}

	//Redraw
	snake.draw(board);
	apple.draw(board);

	//Difficulty level, can be set from options
	Sleep(difficultylevel == HARD ? 50 : 150);
}

//This function handles the game over logic, displays the game over screen, plays the lose sound, and resets the game state for a new game session
void Game::gameOverLogic() {

	Sleep(200);

	clearScr();
	std::cout << gameOverScreen; //Print the winning screen
	playLoseSound();
	Sleep(1000); //Wait for 1 seconds

	//Reset everything needed in-game before calling the menu
	gameReset();
}

//This function handles the game won logic, displays the game won screen, plays the win sound, and resets the game state for a new game session
void Game::gameWonLogic() {

	clearScr();
	std::cout << gameWonScreen; //Print the winning screen
	playWinSound(); //Play win sound
	Sleep(1000); //Wait for 1 seconds

	//Reset everything needed in-game before calling the menu
	gameReset();
}

//This function resets all game components to their initial state, preparing the game for a new session
void Game::gameReset() {

	clearScr();
	State = GameState::Standby;
	menu.ResetMenu();
	apple.resetPosition();
	board.resetBoard();
	snake.resetLife();
	firstPrint = true;
	snake.resetSnake();
	menu.print();
	menu.resetAllArrows();
}

//This function plays a short sound effect sequence when the player exits the game using the Beep function
void Game::playExitSound() const {

	Beep(1000, 100); // E5
	Beep(800, 100);  // D5
	Beep(600, 150);  // C5
	Beep(400, 200);  // A4
}

//This function plays a short sound effect sequence when the player loses the game using the Beep function
void Game::playLoseSound() const {

	Beep(1046, 100);  // C6
	Beep(784, 100);   // G5
	Sleep(60);
	Beep(880, 100);   // A5
	Beep(698, 250);   // F5
	Beep(440, 300);   // A4
}

//This function plays a short sound effect sequence when the player wins the game using the Beep function
void Game::playWinSound() const {

	Beep(784, 200);  // G5
	Beep(880, 200);  // A5
	Beep(988, 200);  // B5
	Beep(1047, 200); // C6
	Beep(1175, 200); // D6
	Beep(1319, 400); // E6
	Beep(1047, 300); // C6
}

//This function manages the color change interface, allowing the player to update the snake's color by entering a valid color name
void Game::handleColors() {

	printColorPreview(snake.getColorName());

	std::string userInput = "";
	int blinkCounter = 0;
	bool cursorVisible = true;
	int cursorY = 6;
	int cursorX = 21;
	bool keyWasPressed = false;
	DWORD messageTimestamp = 0;
	bool messageOnScreen = false;

	while (true)
	{
		if (_kbhit())
		{
			char ch = _getch();
			keyWasPressed = true;

			if (ch == ESC) //Case: return to options screen
			{
				State = GameState::Options;
				break;
			}

			else if (ch == '\n' || ch == '\r') //Case: user pressed ENTER to submit
			{
				blinkCounter = 0;
				std::string buffer = userInput;
				for (char& c : buffer) c = std::tolower(c);
				clearInputArea();

				if (buffer.empty()) //Case: user submitted an empty string
				{
					std::string defaultColor = "green";
					snake.setColor(defaultColor);
					apple.changeAppleColor(snake);
					gotoxy(47, 19);
					std::cout << "Color reset to default";
					messageOnScreen = true;
					messageTimestamp = GetTickCount();
					printColorPreview(defaultColor);
				}
				else if (!isValidColor(buffer)) //Case: color is invalid
				{
					gotoxy(47, 19);
					std::cout << RED_TXT << "Color not found" << RESET_TXT;
					messageOnScreen = true;
					messageTimestamp = GetTickCount();
				}
				else if (buffer == snake.getColorName()) //Case: The color is already selected
				{
					gotoxy(47, 19);
					std::cout << YELLOW_TXT << "Color already selected" << RESET_TXT;
					messageOnScreen = true;
					messageTimestamp = GetTickCount();
				}
				else //Case: Color is valid
				{
					snake.setColor(buffer);
					apple.changeAppleColor(snake);
					printOKInGreen(47, 19);
					messageOnScreen = true;
					messageTimestamp = GetTickCount();
					printColorPreview(buffer);
				}

				userInput.clear();
				cursorX = 21;
				Sleep(500);
				clearInputArea();
				continue;
			}
			else if (ch == '\b' && !userInput.empty()) //Case: user wants to erase last char
			{
				userInput.pop_back();
				gotoxy(cursorX, cursorY);
				std::cout << ' '; //Clear cursor
				cursorX--;
				gotoxy(cursorX, cursorY);
				std::cout << ' '; //Clear old character
				continue;
			}
			else if (userInput.length() >= 35) //Case: user buffer is over 35 chars
				continue;
			else if (std::isprint(ch))
			{
				blinkCounter = 0;
				userInput += ch;
				gotoxy(cursorX, cursorY);
				std::cout << ch;
				cursorX++;
				gotoxy(cursorX, cursorY);
			}
		}
		else
			keyWasPressed = false;

		//Blinking cursor logic
		blinkCounter++;
		if (!keyWasPressed && blinkCounter % 15 == 0)
		{
			cursorVisible = !cursorVisible;
			gotoxy(cursorX, cursorY);
			std::cout << (cursorVisible ? '|' : ' ');
		}

		if (messageOnScreen && GetTickCount() - messageTimestamp >= 2000)
		{
			gotoxy(47, 19);
			std::cout << std::string(25, ' '); //Clear message
			messageOnScreen = false;
		}

		Sleep(50); //Needed for blinking cursor and also helps avoiding high CPU usage
	}
}

//This function clears the user input area used for color changes
void Game::clearInputArea() const {

	gotoxy(20,6);
	std::cout << std::string(35, ' ');
}

//This function prints a color preview at a designated location on the screen if the specified color name is valid
void Game::printColorPreview(std::string colorName) const {

	std::map<std::string, const char*> colorMap = {
		{"white", WHITE_TXT}, {"red", RED_TXT}, {"green", GREEN_TXT},
		{"yellow", YELLOW_TXT}, {"blue", BLUE_TXT}, {"purple", PURPLE_TXT},
		{"cyan", CYAN_TXT}, {"grey", GREY_TXT}, {"pink", PINK_TXT},
		{"violet", VIOLET_TXT}, {"navy blue", NAVY_BLUE_TXT},
		{"gold", GOLD_TXT}
	};

	gotoxy(62, 21);
	std::cout << std::string(15, ' ');

	auto it = colorMap.find(colorName);
	if (it != colorMap.end()) //Case: Found the color
	{
		gotoxy(62, 21);
		colorName[0] = std::toupper(colorName[0]);
		std::cout << it->second << colorName << RESET_TXT;
	}
}

//This function returns true if the provided color name is valid and false otherwise
bool Game::isValidColor(const std::string& color) const {

	const std::map<std::string, const char*> validColors = {
		{"white", WHITE}, {"red", RED}, {"green", GREEN},
		{"yellow", YELLOW}, {"blue", BLUE}, {"purple", PURPLE},
		{"cyan", CYAN}, {"grey", GREY}, {"pink", PINK},
		{"violet", VIOLET}, {"navy blue", NAVY_BLUE},
		{"gold", GOLD_TXT}
	};
	return validColors.count(color) > 0;
}

//This function prints "OK!" in green at the specified screen coordinates with a blinking effect
void Game::printOKInGreen(int x, int y) const {

	gotoxy(x, y);
	std::cout << GREEN_TXT << "OK!" << RESET_TXT;
	Sleep(150);
	gotoxy(x, y);
	std::cout << GREEN << "OK!" << RESET;
	Sleep(150);
	gotoxy(x, y);
	std::cout << GREEN_TXT << "OK!" << RESET_TXT;
	Sleep(150);
	gotoxy(x, y);
	std::cout << GREEN << "OK!" << RESET;
	Sleep(150);
	gotoxy(x, y);
	std::cout << GREEN_TXT << "OK!" << RESET_TXT;
}