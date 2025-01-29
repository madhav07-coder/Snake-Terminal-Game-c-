#include "snake.h"

using namespace std;

// Constructor: Initialize the snake with one segment at the starting position
Snake::Snake(int startX, int startY) : isGrowing(false) 
{
    body.push_back({startX, startY - 2}); // Tail
    body.push_back({startX, startY - 1}); // Middle segment
    body.push_back({startX, startY});     // Head
    direction = 'R'; // Default direction
}



// Move the snake
void Snake::move() 
{
    // Get the current head position
    int headX = body.back().first;   //x
    int headY = body.back().second;   //y

    // Calculate the new head position based on the direction
    if (direction == 'U') headX--;
    else if (direction == 'D') headX++;
    else if (direction == 'L') headY--;
    else if (direction == 'R') headY++;

    // Add the new head position
    body.push_back({headX, headY});

    // Remove the tail only if the snake is not growing   karan ke jyare grow kartu hashe length vadharva mate tail ne remove nathi karvani
    if (!isGrowing) 
    {
        body.pop_front();
    } 
    else 
    {
        isGrowing = false; // Reset the growing flag
    }
}
void Snake::setGrowing(bool growing) 
{
    isGrowing = growing;
}

// Grow the snake
void Snake::grow() 
{
    // kai karvanu nahi aapde uper tail delete nathi karta etele automatic j length vadhi jashe.
    // when food is eaten.
}


// Check if the snake collides with itself
bool Snake::checkSelfCollision() const 
{
    // Get the current head position
    auto head = body.back();

    // Check if the head collides with any other part of the body
    for (size_t i = 0; i < body.size() - 1; ++i) 
    {
        if (body[i] == head) 
        {
            return true; // Collision detected
        }
    }
    return false; // No collision
}

// Get the current body of the snake
const deque<pair<int, int>>& Snake::getBody() const 
{
    return body;
}

// Set a new direction for the snake
void Snake::setDirection(char newDirection) 
{
    // direction check karo ke te pahela ni ulti direction to nathi ne.
    if ((direction == 'U' && newDirection != 'D') ||
        (direction == 'D' && newDirection != 'U') ||
        (direction == 'L' && newDirection != 'R') ||
        (direction == 'R' && newDirection != 'L')) 
        {
        direction = newDirection;
    }
}
