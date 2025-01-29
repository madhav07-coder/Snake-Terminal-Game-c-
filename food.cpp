#include "food.h"

using namespace std;

// Constructor: Initialize the food object
Food::Food(int gridSize) : gridSize(gridSize) 
{
    srand(time(0)); //  random number generator
    position = {rand() % gridSize, rand() % gridSize}; // Random initial position generator
}


void Food::spawnFood(const deque<pair<int, int>>& snakeBody)   // food ni random posn generate kare
{
    bool validPosition = false;

    while (!validPosition) // jya sudhi valid position nahi male tya sudhi loop chalshe.
    {
        position.first = rand() % gridSize;  // random x co.
        position.second = rand() % gridSize;  // random y co.

        // Check if the position is not on the snake's body
        validPosition = true;
        for (const auto& segment : snakeBody) 
        {
            if (segment == position)   // check kare ke food generate thayu te saap ni body par to nathi ne.
            {
                validPosition = false;
                break;
            }
        }
    }
}

// Returns the current position of the food
pair<int, int> Food::getPosition() const 
{
    return position;
}
