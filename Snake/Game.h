#pragma once
#include <iostream>
#pragma comment(lib, "Winmm.lib")
#include "Snake.h"
#include "HelperFunc.h"

//Forward declarations
class Menu;
class Board;
class Apple;

class Game
{

    //Constants
    static constexpr int EASY = 2;
    static constexpr int HARD = 3;
    static constexpr bool OFF = false;
    static constexpr bool ON = true;
    
    //Data Members
    char choiceHolder = '\0';
    bool firstPrint = false;
    int difficultylevel = EASY;
    bool music = OFF;

    //References to game objects
    Menu& menu;
    Board& board;
    Snake& snake;
    Apple& apple;

    //Game State Management
    enum class GameState { Standby, Playing, Pause, GameOver, Instructions, Options, Colors, Exit, GameWon };
    GameState State = GameState::Standby;

	//Screens
    std::string instructionsScreen =
        "|==============================================================================|\n"
        "|                                                                              |\n"
        "|                                  Instructions:                               |\n"
        "|                                  ____________                                |\n"
        "|               Use 'a' or 'd to move left or right accordingly                |\n"
        "|                                                                              |\n"
        "|                  Use 'w' or 's' to move up or down accordingly               |\n"
        "|                                                                              |\n"
        "|                                                                              |\n"
        "|                     Goal: Fill the whole board with the snake                |\n"
        "|                       _________         _________                            |\n"
        "|                      /         \\       /         \\                           |\n"
        "|                     /  /~~~~~\\  \\     /  /~~~~~\\  \\                          |\n"
        "|                     |  |     |  |     |  |     |  |                          |\n"
        "|                     |  |     |  |     |  |     |  |                          |\n"
        "|                     |  |     |  |     |  |     |  |         /                |\n"
        "|                     |  |     |  |     |  |     |  |       //                 |\n"
        "|                    (o  o)    \\  \\_____/  /     \\  \\_____/ /                  |\n"
        "|                     \\__/      \\         /       \\        /                   |\n"
        "|                      |         ~~~~~~~~~         ~~~~~~~~                    |\n"
        "|                      ^                                                       |\n"
        "|                                                                              |\n"
        "|          [ESC] Back to main menu                                             |\n"
        "|                                                                              |\n"
        "|==============================================================================|";

    std::string optionsScreen =
        "|==============================================================================|\n"
        "|                                                                              |\n"
        "|                                     Options:                                 |\n"
        "|                                     _______                                  |\n"
        "|                                                                              |\n"
        "|                           [1] Colors                                         |\n"
        "|                           [2] difficulty level : Easy                        |\n"
        "|                           [3] difficulty level : Hard                        |\n"
        "|                           [4] music ->                                       |\n"
        "|                                                                              |\n"
        "|                                                                              |\n"
        "|                                                                              |\n"
        "|                                                                              |\n"
        "|                                                                              |\n"
        "|                                                                              |\n"
        "|                                                                              |\n"
        "|                                                                              |\n"
        "|                                                                              |\n"
        "|                                                                              |\n"
        "|                                                                              |\n"
        "|                                                                              |\n"
        "|          [ESC] Back to main menu                                             |\n"
        "|                                                                              |\n"
        "|                                                                              |\n"
        "|==============================================================================|";

    std::string ColorsScreen =
        "|==============================================================================|\n"
        "|                                                                              |\n"
        "|                                     Colors:                                  |\n"
        "|                                     ______                                   |\n"
        "|                    Please enter the name of the snake color:                 |\n"
        "|                                                                              |\n"
        "|                  >                                                           |\n"
        "|                                                                              |\n"
        "|                     Supported colors:                                        |\n"
        "|                     _________________                                        |\n"
        "|                     White                      Cyan                          |\n"
        "|                     Red                        Grey                          |\n"
        "|                     Green                      Pink                          |\n"
        "|                     Yellow                     Violet                        |\n"
        "|                     Blue                       Navy Blue                     |\n"
        "|                     Purple                                                   |\n"
        "|                                                                              |\n"
        "|          *Enter nothing and press <ENTER> to reset to default color          |\n"
        "|          **When you finish specifying your colors, press <ENTER>             |\n"
        "|          ***Case insensitive                                                 |\n"
        "|                                                                              |\n"
        "|          [ESC] Back to options               Current Color:                  |\n"
        "|                                                                              |\n"
        "|                                                                              |\n"
        "|==============================================================================|";

    std::string gameOverScreen =
        "|==============================================================================|\n"
        "|                                                                              |\n"
        "|           GGGGG  AAAAA  M     M  EEEEE    OOO   V   V  EEEEE  RRRR           |\n"
        "|          G       A   A  MM   MM  E       O   O  V   V  E      R   R          |\n"
        "|          G  GG   AAAAA  M M M M  EEEE    O   O  V   V  EEEE   RRRR           |\n"
        "|          G   G   A   A  M  M  M  E       O   O   V V   E      R  R           |\n"
        "|           GGGG   A   A  M     M  EEEEE    OOO     V    EEEEE  R   R          |\n"
        "|                                                                              |\n"
        "|==============================================================================|\n"
        "                                                                               \n"
        "                                                                               \n"
        "                                                                               \n"
        "                                                                               \n"
        "                                                                               \n"
        "                                                                               \n"
        "                                                                               \n"
        "                                                                               \n"
        "                                                                               \n"
        "                                                                               \n"
        "                                   Game Over!                                  \n"
        "                              Returning To main menu                           ";


    std::string pauseScreen =
        "|==============================================================================|\n"
        "|                                                                              |\n"
        "|                   PPPPP   AAAAA  U   U  SSSSS  EEEEE  DDDD                   |\n"
        "|                   P   P  A     A U   U  S      E      D   D                  |\n"
        "|                   PPPPP  AAAAAAA U   U  SSSSS  EEEE   D   D                  |\n"
        "|                   P      A     A U   U      S  E      D   D                  |\n"
        "|                   P      A     A UUUUU  SSSSS  EEEEE  DDDD                   |\n"
        "|                                                                              |\n"
        "|                                                                              |\n"
        "|                                                                              |\n"
        "|                                                                              |\n"
        "|                                                                              |\n"
        "|                                                                              |\n"
        "|                                                                              |\n"
        "|                                                                              |\n"
        "|                                 _________                                    |\n"
        "|                                 |       |                                    |\n"
        "|                                 |  ESC  |                                    |\n"
        "|                                 |       |                                    |\n"
        "|                                 |_______|                                    |\n"
        "|                                                                              |\n"
        "|                       Press ESC to return to the game                        |\n"
        "|                                                                              |\n"
        "|                                                                              |\n"
        "|==============================================================================|";

    std::string gameWonScreen =
        "|==============================================================================|\n"
        "|                                                                              |\n"
        "|        Y   Y   OOOOO  U   U       !!!      WWW     WWW   OOOOO   N   N       |\n"
        "|         Y Y    O   O  U   U       !!!       W       W    O   O   NN  N       |\n"
        "|          Y     O   O  U   U       !!!       W   W   W    O   O   N N N       |\n"
        "|          Y     O   O  U   U                 W  W W  W    O   O   N  NN       |\n"
        "|          Y     OOOOO   UUU        !!!        W     W     OOOOO   N   N       |\n"
        "|                                                                              |\n"
        "|==============================================================================|\n"
        "                                                                               \n"
        "                                                                               \n"
        "                                                                               \n"
        "                                                                               \n"
        "                                                                               \n"
        "                                                                               \n"
        "                                                                               \n"
        "                                                                               \n"
        "                                                                               \n"
        "                                                                               \n"
        "                                Congratulations!                               \n"
        "                                YOU WON THE GAME!                                ";

    public:
        Game(Menu& M, Board& B, Snake& S, Apple& A) : menu(M), board(B), snake(S), apple(A)   //Constructor
        { std::srand(static_cast<unsigned int>(std::time(nullptr))); snake.resetSnakePos(); } //Initialize the game randomizer each time you enter the game

        //Game Flow & State Management
        void run();
        void playGame();
        void printScreens();
        void handleState();
        void handleColors();
        void gameOverLogic();
        void gameWonLogic();
        void gameReset();
        void terminatePause() { clearScr(); firstPrint = true; }
        void printPauseScreen() const { std::cout << pauseScreen; }

        //Color Input Handling
        void clearInputArea() const;
        void printColorPreview(std::string colorName) const;
        bool isValidColor(const std::string& color) const;
        void printOKInGreen(int x, int y) const;

        //Audio FX
        void playExitSound() const;
        void playLoseSound() const;
        void playWinSound() const;
        void playBackgroundMusic() const { PlaySound(TEXT("background_music.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP); }
        void stopBackgroundMusic() const { PlaySound(NULL, 0, 0); }
};