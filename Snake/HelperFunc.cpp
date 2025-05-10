#include <iostream>
#include <windows.h>
#include "HelperFunc.h"

//This function moves the cursor to a specified position in the console window
void gotoxy(int x, int y) {
    std::cout.flush();
    COORD coord; //Create a COORD structure 
    coord.X = x; //Set the X coordinate 
    coord.Y = y; //Set the Y coordinate 
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord); //Move the cursor 
}

//This function controls the visibility of the console cursor
void ShowConsoleCursor(bool showFlag) {
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; //set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}

//This function clears the screen
void clearScr() {
    system("cls");
}