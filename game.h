#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>

// forward declare TileMap, Entity, and Player classes
class TileMap;
class Entity;
class Player;

class Game
{
public:

  Game(); // constructor
  ~Game() {delete [] entities;} // destructor

  // the game loop
  void gameLoop();

  // the draw loop
  void drawEverything(TileMap);

  // collision functions and checks
  bool checkCollisions(int, const int*); // checks for collision between an object, the walls, and other entities
  int checkCombat(char, int); // checks to see if there is a living entity in the direction the player is facing for combat

  // combat functions
  bool battle(int, int, Player&, int);
  void deleteEntity(int);

  // cursor functions
  void moveCursor(bool);
  int cursorClick();

  // gameClock functions
  void wait(float);

  // handy functions
  std::string intToString(int);

private:

  sf::RenderWindow win; // the window
  sf::Clock gameClock; // the game clock
  sf::RectangleShape menuBorder; // the in game menu border

  // cursor objects
  sf::CircleShape cursor;
  int cursorPos;

  // dynamic array of entity pointers and entitiesSize keeps track of the size
  Entity** entities;
  int entitiesSize;
};

#endif
