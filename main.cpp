#include "gameboard.h"
#include <bits/stdc++.h>

int main() 
{
    int N=0;
    cout<<"Enter the size of the grid: ";
    cin>>N;
    GameBoard game(N);

    // Run the game loop  final run
    game.runGame();

    return 0;
}
