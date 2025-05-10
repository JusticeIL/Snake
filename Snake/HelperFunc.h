#pragma once
#include <iostream>
#include <windows.h>
#include <process.h>

void gotoxy(int x, int y);
void ShowConsoleCursor(bool showFlag);
void clearScr();

//Constants for menu layout and options
static constexpr char play = '1';
static constexpr char options = '2';
static constexpr char instructions = '3';
static constexpr char musicKey = '4';
static constexpr char ESC = 27;
static constexpr char quit = 27;