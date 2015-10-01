#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <cstdlib> // srand
#include <ctime> // time
#include <string> // string
using namespace std;

class Player
{
public:

  Player() {} // default constructor (currently does nothing)
  Player(string); // string constructor, loads the texture file

  sf::Sprite getSprite() const {return sprite;} //function to return sprite so that it may be drawn to the screen
  void setSpritePosition(int, int); // changes the player's position
  void updatePosition(int, int); // update the player's position relative to where they are now

  void setDirection(char dir) {direction = dir;} // set's the player's direction
  char getDirection() const {return direction;} // returns the player's current direction

  // stat functions
  int getHealth() const {return health;}
  int getStrength() const {return strength;}
  int getDefense() const {return defense;}
  int getAgility() const {return agility;}
  void subHealth(int x) {health = getHealth() - x;}

  // combat functions
  int playersTurn(int, int);

  //function that handles location and which sprite is being displayed

private:

  int yPos; // player's current y coordinate
  int xPos; // player's current x coordinate
  sf::Texture texture; // texture containing the player sprite sheet
  sf::Sprite sprite; // the player's current sprite
  char direction; // determines which direction the player is facing

  // Stats
  int health;
  int experience;
  int strength;
  int defense;
  int agility;

};

#endif

// functions

Player::Player(string fileName)
{
  texture.loadFromFile(fileName); // load fileName given

  sprite.setTexture(texture); // set the sprite's current texture

  xPos = 0; // set the x and y coordinates
  yPos = 0;

  health = 30;
  experience = 0;
  strength = 5;
  defense = 5;
  agility = 5;

  direction = 'd'; // direction is defaulted to down

}

void Player::setSpritePosition(int x, int y)
{
  sprite.setPosition(x, y); // set the sprite's new position
  xPos = x; // update x and y coordinates
  yPos = y;
}

void Player::updatePosition(int x, int y)
{
  xPos = xPos - x; // update x and y coordinates relative to where the player is now
  yPos = yPos - y;
  sprite.setPosition(xPos, yPos); // update sprite position as well
}


int Player::playersTurn(int enemyAgility, int enemyDefense)
{
  int result;

  srand(time(NULL)); // seed srand

  int dodgeChance = 0;

  // player's turn

  if(getAgility() < enemyAgility) // if the enemy has higher agility then they have a chance to dodge your attack
  {
    dodgeChance = enemyAgility - getAgility(); // calculate enemy dodge chance
  }

  // if dodgeChance > 0 roll dice to see if the enemy dodges your attack, if so exit function
  if(dodgeChance > 0)
  {
    if((rand() % 99) + 1 <= dodgeChance) return 0;
  }

  int damage = getStrength() - enemyDefense;

  // add weapon modifier (will be a dice roll between 2 numbers depending on weapon)...
  // but for now its just 1-3:

  //damage += (rand() % 3) + 1;
  damage += 7;

  result = damage;

  return result;
}
