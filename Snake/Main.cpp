#include <iostream>
#include "HelperFunc.h"
#include "Game.h"
#include "Menu.h"
#include "Snake.h"
#include "Apple.h"

int main() {

    ShowConsoleCursor(false); //Removing Console Cursor
    Menu menu;
    Board board;
    Snake snake;
    Apple apple(0,0);
    Game game(menu, board, snake, apple);
    game.run();
}