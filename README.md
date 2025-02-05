# Snake-Terminal-Game-C++

## Snake Game - C++ Project Documentation

### ⚠️ The game is made for Windows

### Group: Code Experts
1. **202401204** - Shlok Nareshkumar Ukani
2. **202401239** - Vamja Krish Pravinbhai
3. **202401243** - Virugama Meetkumar Aniruddhbhai
4. **202401226** - Thesiya Madhav Manish

## 📌 Introduction
The Snake game is a classic arcade game where the player controls a snake to collect food while avoiding collisions. This C++ implementation supports single-player and multiplayer modes with customizable difficulty settings. The game dynamically adjusts the speed based on the score.

## 🎮 Features
- Single-player and Multiplayer support
- Customizable difficulty levels (Easy, Medium, Hard)
- Dynamic difficulty mode where speed increases with score
- Custom snake symbols chosen by the player
- High score tracking using a file
- Real-time input handling using `kbhit()` and `getch()`

## 📂 File Structure
The project consists of 8 files:

| File | Description |
|------|------------|
| `main.cpp` | Entry point of the game. Initializes the game board and starts the game loop. |
| `snake.h` | Header file defining the Snake class and its functions. |
| `snake.cpp` | Implements snake movement, growth, and collision detection. |
| `food.h` | Header file defining the Food class for generating food positions. |
| `food.cpp` | Implements the logic for random food generation, ensuring it does not overlap with the snake. |
| `gameboard.h` | Defines the GameBoard class, managing the grid, snakes, food, input, and scoring. |
| `gameboard.cpp` | Implements the game logic, including user input handling, difficulty settings, and rendering. |
| `highscore.txt` | Stores the highest score achieved in the game. |

## 🛠️ Class Descriptions
### 🐍 Snake Class (`snake.h`, `snake.cpp`)
Manages the snake's body, movement, and collision detection.
#### Attributes:
- `deque<pair<int, int>> body` - Stores the coordinates of the snake’s body.
- `char direction` - Current movement direction (U, D, L, R).
- `bool isGrowing` - Flag to indicate whether the snake should grow.

#### Methods:
```cpp
Snake(int startX, int startY); // Constructor to initialize the snake at a given position
void move(); // Moves the snake in the current direction
void grow(); // Grows the snake when food is eaten
bool checkSelfCollision() const; // Checks if the snake collides with itself
void setDirection(char newDirection); // Sets a new direction for movement
void setGrowing(bool growing); // Enables growth mode after eating food
const deque<pair<int, int>>& getBody() const; // Returns the snake’s body
```

### 🍎 Food Class (`food.h`, `food.cpp`)
Handles food spawning on the grid.
#### Attributes:
- `pair<int, int> position` - Stores the current food position.
- `int gridSize` - Size of the game board.

#### Methods:
```cpp
Food(int gridSize); // Constructor that initializes food at a random position
void spawnFood(const deque<pair<int, int>>& snakeBody); // Generates food avoiding the snake’s body
pair<int, int> getPosition() const; // Returns the food’s position
```

### 🎮 GameBoard Class (`gameboard.h`, `gameboard.cpp`)
Manages the game logic, including rendering, user input, difficulty levels, and collision detection.
#### Attributes:
- `int gridSize` - Size of the game grid.
- `vector<vector<char>> grid` - 2D grid representation.
- `Snake snake1, snake2` - Snake objects for player(s).
- `Food food` - Food object.
- `int score, highScore` - Stores current and highest scores.
- `bool isPaused, isMultiplayer` - Flags for pause state and multiplayer mode.
- `int delay` - Controls snake speed.
- `string gameMode, difficultyLevel` - Stores the selected game mode and difficulty.

#### Methods:
```cpp
GameBoard(int gridSize); // Initializes the game board and settings
void loadHighScore(), void saveHighScore(); // Manages high score tracking
void selectGameMode(), void selectDifficultyLevel(); // Allows game mode and difficulty selection
void updateGrid(); // Updates the game grid with snake and food positions
void renderGrid() const; // Displays the grid on the console
bool checkCollision() const; // Checks for boundary and self-collisions
void handleInput(); // Handles user input for movement and pause
void runGame(); // The main game loop
```

## 🚀 How to Run the Game
1. Compile the project using a C++ compiler:
   ```sh
   g++ main.cpp gameboard.cpp snake.cpp food.cpp -o snake_game
   ```
2. Run the executable:
   ```sh
   snake_game.exe
   ```
3. Enter grid size when prompted.
4. Select game mode (Custom or Dynamic difficulty) using `1` or `2`.
5. Choose single-player or multiplayer mode.
6. Control the snake:
   - **Player 1:** `W` (Up), `S` (Down), `A` (Left), `D` (Right)
   - **Player 2:** `I` (Up), `K` (Down), `J` (Left), `L` (Right)
   - **P** to Pause/Resume
   - **M** to open the settings menu

## 📜 Game Rules
- The snake moves continuously in the last set direction.
- The player must eat food to grow the snake and increase the score.
- The game ends when the snake collides with the wall or itself.
- In multiplayer mode, the game ends if either snake collides with itself, the wall, or the opponent.

## 🎯 Conclusion
This C++ Snake game provides an interactive terminal-based gaming experience with multiple modes and difficulty levels with single player and multiplayer playing options.

---

