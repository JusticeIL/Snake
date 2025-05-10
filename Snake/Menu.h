#pragma once
#include "Board.h"
class Menu
{

	//Constants for menu layout and options
	static constexpr char arrow = '>';

    //Struct to define menu option positions
    struct possiblePos { int x; int y; }; //Has to be positioned here to maintain the constexpr compiling

    //Positions of menu options
    static constexpr possiblePos PLAY = { 8,16 };
    static constexpr possiblePos OPTIONS = { 8,18 };
    static constexpr possiblePos INSTRUCTIONS = { 8,20 };
    static constexpr possiblePos EXIT = { 8,22 };
    static constexpr possiblePos positions[] = { PLAY, OPTIONS, INSTRUCTIONS, EXIT };

	//Data Members
    bool chosen = false;
    bool isArrow = false;
    char menuChar = '\0';

public:
	//Menu layout
    const char menu[Board::height() + 1][Board::width() + 10 + 1] = { //+1 for \0
        //01234567890123456789012345678901234567890123456789012345678901234567890123456789
         "|==============================================================================|", // 0
         "|                                                                              |", // 1
         "|                  |=====| |=\\   |=|  /====\\  |=|  |=| |======|                |", // 2
         "|                  |=|     |==\\  |=| /=|  |=\\ |=||===| |=|                     |", // 3
         "|                  |=====| |=|=\\ |=| |======| |===|    |======|                |", // 4
         "|                      |=| |=|==\\|=| |======| |=||===| |=|                     |", // 5
         "|                  |=====| |=| |===| |=|  |=| |=|  |=| |======|                |", // 6
         "|                                                                              |", // 7
         "|                                                                              |", // 8
         "|                                               ____                           |", // 9
         "|                      ________________________/ O  \\___/                      |", // 10
         "|                     <_/_\\_/_\\_/_\\_/_\\_/_\\_/_______/   \\                      |", // 11
         "|                                                                              |", // 12
         "|                                                                              |", // 13
         "|                                                                              |", // 14
         "|                                                                              |", // 15
         "|         [1] Start a new Game                                                 |", // 16
         "|                                                                              |", // 17
         "|         [2] Options                                                          |", // 18
         "|                                                                              |", // 19
         "|         [3] Instructions                                                     |", // 20
         "|                                                                              |", // 21
         "|         [ESC] Exit                                                           |", // 22
         "|                                      Use numbers and ENTER to navigate       |", // 23
         "|                                                                              |", // 24
         "|==============================================================================|", // 25
    };

    //Menu Display
    void print() const;
    char handleMenu();

    //Menu Navigation
    void MoveArrow(char numKey);
    void resetAllArrows();
    void ChangeisArrowChoice() { isArrow = true; }
    void ChangeMenuChar(char ch) { menuChar = ch; }
    void ResetMenu() { menuChar = '\0'; chosen = false; }

    //Getters
    bool GetMenuChoice() const { return chosen; }
};