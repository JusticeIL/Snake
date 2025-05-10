#include <iostream>
#include <windows.h>
#include <conio.h>
#include "Menu.h"
#include "HelperFunc.h"

//This function prints the menu
void Menu::print() const {
    
    gotoxy(0, 0);

    for (int i = 0; i < std::size(menu) - 1 - 1; i++) {
        std::cout << menu[i] << '\n';
    }
    std::cout << menu[std::size(menu) - 1];
}

//This function handles user input in the menu, updates the selected option, and manages the menu display
char Menu::handleMenu() {
    while (true)
    {
        if (_kbhit())
        {
            char MenuInput = _getch();
            if ((play <= MenuInput && MenuInput <= instructions) || MenuInput == quit) //Available keys
            {
                resetAllArrows(); //Case: remove any current showing arrows
                MoveArrow(MenuInput); //Case: Arrow is showing on screen
                isArrow = true; //Case: Arrow is showing on screen so flag should be true now
                menuChar = MenuInput; //Menu input is entered
            }

            if ((MenuInput == '\n' || MenuInput == '\r') && isArrow) //Only after arrow is showing & player pressed ENTER
            {
                chosen = true;

                if (menuChar == ESC)
                    gotoxy(0,26);
                
                clearScr();
                return menuChar;
            }
        }
        Sleep(10); //Prevent 100% CPU Usage
    }
}

//This function receives a numeric key (as a character), updates the menu arrow position, and prints it
void Menu::MoveArrow(char numKey) {

    resetAllArrows(); //Reset all
    switch (numKey) {

    case play:
        gotoxy(PLAY.x, PLAY.y);
        break;
    case options:
        gotoxy(OPTIONS.x, OPTIONS.y);
        break;
    case instructions:
        gotoxy(INSTRUCTIONS.x, INSTRUCTIONS.y);
        break;
    case quit:
        gotoxy(EXIT.x, EXIT.y);
        break;
    }
    std::cout << arrow;
}

//This function erases all arrows in the menu
void Menu::resetAllArrows() {
    for (int i = 0; i < (sizeof(positions) / sizeof(positions[0])); i++)
    {
        gotoxy(positions[i].x, positions[i].y);
        std::cout << ' ';
    }
}