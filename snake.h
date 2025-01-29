#ifndef SNAKE_H 
#define SNAKE_H

#include <bits/stdc++.h>
//#include <deque>    // For std::deque
//#include <utility>  // For std::pair

using namespace std;

class Snake 
{
private:
    deque<pair<int, int>> body; // Snake's body stored as a deque of coordinates
    char direction;     // Current direction ('U', 'D', 'L', 'R')
    bool isGrowing;      // flag to show that snake is growing     

public:
    Snake(int startX, int startY);   // Constructor
    void move();    // sap ne move kare
    void grow();    // sap ne grow kare
    bool checkSelfCollision() const;   // sap nu potani sathe collison check kare.
    const deque<pair<int, int>>& getBody() const;   // snake body
    void setDirection(char newDirection);    // direction
    void setGrowing(bool growing); // Setter for isGrowing

};

#endif
