#include "gameboard.h"

#include <bits/stdc++.h>
#include <conio.h> // For _kbhit() and _getch()         
#include <thread>  // For sleep functionality     
#include <chrono>  // For time intervals  time related badhu kaam kare aa
#include <fstream> // For file handling (high score)
//#include <string>  // For username

using namespace std;

// Constructor: Initialize the board
GameBoard::GameBoard(int gridSize)
    : gridSize(gridSize), snake1(gridSize / 2, gridSize / 2), snake2(gridSize / 2, gridSize / 2 - 5), food(gridSize), score(0), isPaused(false), delay(200), isMultiplayer(false), snake1Symbol('O'), snake2Symbol('X') 
{
    loadHighScore();    // Load the high score from file je aapne text file save kari hati
    selectPlayerMode(); //  single player ke multiplayer select karva
    selectGameMode(); //  game mode select karva custom ke dynamic
    selectSnakeSymbols(); // choose snake symbols for single player or multiplayer

    if (isMultiplayer) 
    {
        cout << "Player 1, enter your username: ";
        cin >> username1;
        cout << "Player 2, enter your username: ";
        cin >> username2;
    } 
    else 
    {
        cout << "Enter your username: ";
        cin >> username1;
    }

    updateGrid(); // Initialize the grid with the snake and food
}

// Load high score from file
void GameBoard::loadHighScore() 
{
    ifstream file("highscore.txt");  // aa text file ma khali high score as a number score thashe  //  ifstream e file ne open kare ane input le
    if (file.is_open()) 
    {
        file >> highScore;
        file.close();
    } 
    else 
    {
        highScore = 0; // Default high score if file nathi
    }
}

// Save high score to file
void GameBoard::saveHighScore() 
{
    ofstream file("highscore.txt");// ofstream no use file ma data write karva mate thay.
    if (file.is_open()) 
    {
        file << highScore;
        file.close();
    }
}

// Set initial delay based on difficulty level  jo custom game mode hoy toh difficulty level select karva
void GameBoard::setInitialDelay()   // jetlo vadhare delay etli speed ochhi.  
{
    if (difficultyLevel == "Easy") 
    {
        delay = 300; // Slower speed
    } 
    else if (difficultyLevel == "Medium")
    {
        delay = 200; // Medium speed
    } 
    else if (difficultyLevel == "Hard") 
    {
        delay = 100; // Faster speed
    }
}

// Increase difficulty dynamically  jo dynamic hoy to j 
void GameBoard::increaseDifficulty() 
{
    if (gameMode == "Dynamic") 
    {
        if (score >= 50 && score < 100)
        {
            delay = max(100, delay - 10); // Increase speed slightly
        } 
        else if (score >= 100) 
        {
            delay = max(50, delay - 5); // Increase speed further
        }
    }
}

// Allow player to select game mode
void GameBoard::selectGameMode() 
{
    cout << "Select Game Mode:"<<endl;
    cout << "1. Custom Difficulty"<<endl;
    cout << "2. Dynamic Difficulty"<<endl;
    int choice;
    cin >> choice;

    if (choice == 1) 
    {
        gameMode = "Custom";
        selectDifficultyLevel();
    } 
    else if (choice == 2) 
    {
        gameMode = "Dynamic";
        difficultyLevel = "Medium"; // Default for Dynamic mode
        setInitialDelay();
        ////////////////////////////////////////////////Madhav JOJE/////////////////////////////////////////////////////////////////////////////////
    } 
    else 
    {
        cout << "Invalid choice. Defaulting to Custom Difficulty (Medium).\n";
        gameMode = "Custom";
        difficultyLevel = "Medium";
        setInitialDelay();
    }
}

// Allow player to select difficulty level (for Custom mode)
void GameBoard::selectDifficultyLevel() 
{
    cout << "Select Difficulty Level:" << endl;
    cout << "1. Easy " << endl;
    cout << "2. Medium " << endl;
    cout << "3. Hard " << endl;
    int choice;
    cin >> choice;

    if (choice == 1) 
    {
        difficultyLevel = "Easy";
    }
    else if (choice == 2) 
    {
        difficultyLevel = "Medium";
    } 
    else if (choice == 3) 
    {
        difficultyLevel = "Hard";
    } 
    else 
    {
        cout << "Invalid choice. Defaulting to Medium.\n";
        difficultyLevel = "Medium";
    }

    setInitialDelay();  // aanathi j originally speed nakki thay
}

// Allow player to select single-player or multiplayer mode
void GameBoard::selectPlayerMode() 
{
    cout << "Select Player Mode:" << endl;
    cout << "1. Single Player"<<endl;
    cout << "2. Multiplayer"<<endl;
    int choice;
    cin >> choice;

    if (choice == 1) 
    {
        isMultiplayer = false;
    } 
    else if (choice == 2) 
    {
        isMultiplayer = true;
    } 
    else 
    {
        cout << "Invalid choice. Defaulting to Single Player.\n";
        isMultiplayer = false;
    }
}

// Allow players to choose custom snake symbols
void GameBoard::selectSnakeSymbols() 
{
    if (isMultiplayer) 
    {
        cout << "Player 1, choose your snake symbol (one character): ";
        cin >> snake1Symbol;
        cout << "Player 2, choose your snake symbol (one character): ";
        cin >> snake2Symbol;
    } 
    else 
    {
        cout << "Choose your snake symbol (one character): ";
        cin >> snake1Symbol;
    }
}

// Display settings menu
void GameBoard::showSettingsMenu() 
{
    cout << "Settings Menu:\n";
    cout << "1. Change Difficulty\n";
    cout << "2. Change Snake Symbol\n";
    cout << "3. Back to Game\n";
    int choice;
    cin >> choice;

    switch (choice) 
    {
        case 1:
            selectDifficultyLevel();
            break;
        case 2:
            selectSnakeSymbols();
            break;
        case 3:
            break;
        default:
            cout << "Invalid choice."<<endl;
            break;
    }
}

// Updates the grid with the snake and food positions
void GameBoard::updateGrid() 
{
    // Clear the grid to intial val
    grid = vector<vector<char>>(gridSize, vector<char>(gridSize, ' '));

    // snake 
    for (const auto& segment : snake1.getBody()) 
    {
        grid[segment.first][segment.second] = snake1Symbol; // Snake 1 body
    }

    if (isMultiplayer) 
    {
        for (const auto& segment : snake2.getBody()) 
        {
            grid[segment.first][segment.second] = snake2Symbol; // Snake 2 body
        }
    }

    // Place the food
    auto foodPos = food.getPosition();
    grid[foodPos.first][foodPos.second] = '*'; // * Food che
}

// Renders kare
void GameBoard::renderGrid() const 
{
    system("cls"); // Clear the console screen
    cout << "Player 1: " << username1 << endl;
    if (isMultiplayer) 
    {
        cout << "Player 2: " << username2 << endl;
    }
    cout << "Score: " << score << " | High Score: " << highScore << endl;
    cout << "Game Mode: " << gameMode << " | Difficulty: " << difficultyLevel << endl;

    if (isPaused) 
    {
        cout << "Game Paused. Press 'P' to Resume." << endl;
    }

    for (const auto& row : grid) 
    {
        for (const auto& cell : row) 
        {
            cout << (cell == ' ' ? '.' : cell) << ' '; // Khali cell '.' che 
        }
        cout << endl;
    }
}

// Checks for collisions (with boundary or self)
bool GameBoard::checkCollision() const {
    // Get the head position of the snake(s)
    auto head1 = snake1.getBody().back();
    auto head2 = snake2.getBody().back();

    // Check boundary collision for snake 1
    if (head1.first < 0 || head1.first >= gridSize || head1.second < 0 || head1.second >= gridSize)  // grid ni bahar che ke nahi te check
    {
        return true;
    }

    // Check self-collision for snake 1
    if (snake1.checkSelfCollision()) 
    {
        return true;
    }

    // Check boundary collision for snake 2 
    if (isMultiplayer) // jo multiplayer hoy to j
    {
        if (head2.first < 0 || head2.first >= gridSize || head2.second < 0 || head2.second >= gridSize) 
        {
            return true;
        }

        // Check self-collision for snake 2
        if (snake2.checkSelfCollision()) 
        {
            return true;
        }

        // banne snake vacche nu collision
        for (const auto& segment : snake1.getBody()) // snak 2 ,1 ne takray
        {
            if (segment == head2) 
            {
                return true;
            }
        }

        for (const auto& segment : snake2.getBody()) // snak 1 ,2 ne takray
        {
            if (segment == head1) 
            {
                return true;
            }
        }
    }

    return false; // matlab No collision
}

// Handles user input to change the snake's direction
void GameBoard::handleInput() {
    if (_kbhit()) { // Check if a key is pressed
        char key = _getch();
        if (key == ('w'||'W') && !isPaused) snake1.setDirection('U');
        else if (key == ('s'||'S') && !isPaused) snake1.setDirection('D');
        else if (key == ('a'||'A') && !isPaused) snake1.setDirection('L');
        else if (key == ('d'||'D') && !isPaused) snake1.setDirection('R');
        else if (key == ('i'||'I') && !isPaused && isMultiplayer) snake2.setDirection('U');
        else if (key == ('k'||'K') && !isPaused && isMultiplayer) snake2.setDirection('D');
        else if (key == ('j'||'J') && !isPaused && isMultiplayer) snake2.setDirection('L');
        else if (key == ('l'||'L') && !isPaused && isMultiplayer) snake2.setDirection('R');
        else if (key == ('p'||'P')) {
            isPaused = !isPaused; // Toggle pause
            if (isPaused) {
                cout << "Game Paused. Press 'P' to Resume." << endl;
            } else {
                cout << "Game Resumed." << endl;
            }
        } else if (key == ('m'||'M')) {
            showSettingsMenu(); // Show settings menu
        }
    }
}

// determine and display the winner
void GameBoard::determineWinner() const 
{
    if (isMultiplayer) 
    {
        int snake1Length = snake1.getBody().size();
        int snake2Length = snake2.getBody().size();

        if (snake1Length > snake2Length) 
        {
            cout << username1 << " wins with a length of " << snake1Length << "!" << endl;
        } 
        else if (snake2Length > snake1Length) 
        {
            cout << username2 << " wins with a length of " << snake2Length << "!" << endl;
        } 
        else // banne ni same lengtgh
        {
            cout << "It's a tie! Both snakes have a length of " << snake1Length << "." << endl;
        }
    } 
    else  // sigle player ma only score
    {
        cout << username1 << ", your final score is " << score << "." << endl;
    }
}

// Main game 
void GameBoard::runGame() 
{
    while (true) 
    {
        handleInput(); // pause hoy to pan input

        if (!isPaused) 
        {
            // move the snake
            snake1.move();
            if (isMultiplayer) 
            {
                snake2.move();
            }

            if (checkCollision()) 
            {
                cout << "Game Over!" << endl;
                determineWinner(); // wiiner name display kare
                if (score > highScore) 
                {
                    highScore = score;
                    saveHighScore(); // Save new high score
                }
                break;
            }

            // check food eaten by nake or not?
            if (snake1.getBody().back() == food.getPosition()) 
            {
                snake1.setGrowing(true); // vadhva mate kahi do
                food.spawnFood(snake1.getBody()); // fariti generate new food
                score += 1; // Update the score by +1

                // dynamically difficulty vadhe
                increaseDifficulty();
            }

            if (isMultiplayer && snake2.getBody().back() == food.getPosition()) 
            {
                snake2.setGrowing(true); 
                food.spawnFood(snake2.getBody()); 
                score += 1; 
                increaseDifficulty();
            }

            updateGrid();
        }

        renderGrid();

        // game speed controller
        this_thread::sleep_for(chrono::milliseconds(delay)); // Use the updated delay
    }
}
