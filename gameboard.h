#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include "snake.h"
#include "food.h"
#include <bits/stdc++.h>
#include <fstream> // For file handling (high score.txt file mate)

using namespace std;

class GameBoard 
{
private:
    int gridSize;                      // Size of the grid (NxN)
    vector<vector<char>> grid;         // The game grid (2D representation)
    Snake snake1;                      // The first snake (Player 1)
    Snake snake2;                      // The second snake (Player 2, for multiplayer)
    Food food;                         // The food
    int score;                         // Player's score
    int highScore;                     // High score
    string username1;                  // Player 1's username
    string username2;                  // Player 2's username (for multiplayer)
    bool isPaused;                     // Pause state
    int delay;                         // delay between snake movements (controls speed)
    string gameMode;                   // Current game mode (Custom or Dynamic)
    string difficultyLevel;            // Difficulty level (Easy, Medium, Hard)
    bool isMultiplayer;                // multiplayer check 
    char snake1Symbol;                 // Symbol for snake 1
    char snake2Symbol;                 // Symbol for snake 2

    void updateGrid();                 // Updates the grid with snake and food
    void renderGrid() const;           // Renders the grid to the terminal
    void loadHighScore();              // file mathi highsore load kare
    void saveHighScore();              // high score file ma save kare
    void setInitialDelay();            // Set initial delay based on difficulty level
    void increaseDifficulty();         // Increase difficulty dynamically
    void selectSnakeSymbols();         // allow players to choose customsnake symbols
    void showSettingsMenu();           // display setting
    void determineWinner() const;      // determine and display the winner

public:
    GameBoard(int gridSize);           // Constructor to initialize the board
    bool checkCollision() const;       // collision chekc kare boundry sathe ke self
    void handleInput();                // handel the input given by user
    void runGame();                    // Main game loop
    void selectGameMode();             // Allow player to select game mode custom ke dynamic
    void selectDifficultyLevel();      // Allow player to select difficulty level (for Custom mode) easy,med ke hard
    void selectPlayerMode();           // Allow player to select single-player or multiplayer mode
};
#endif 