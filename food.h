#ifndef FOOD_H
#define FOOD_H

#include <bits/stdc++.h>
//#include <utility>  // For std::pair
//#include <deque>    // For std::deque
#include <cstdlib>  // For rand() function use
#include <ctime>    // For srand() function use


using namespace std;

class Food 
{
private:
    pair<int, int> position; // Position of the food (x, y)        private ma aa banne karan ke change nathi karvani thati pachi 
    int gridSize;            // Size of the game board (NxN)

public:
    // Constructor
    Food(int gridSize);

    void spawnFood(const deque<pair<int, int>>& snakeBody);  // food ni random posn generate kare
    pair<int, int> getPosition() const;    // food ni random posn assign thai te return kare
};

#endif 
