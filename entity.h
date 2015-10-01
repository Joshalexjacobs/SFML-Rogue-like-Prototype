#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>
#include <string>
using namespace std;

class Entity
{
public:

  Entity(){} // default constructor
  Entity(string, string, int, bool); // string constructor, names the enemy and loads the texture file

  string getName() const {return name;}
  sf::Sprite getSprite() const {return sprite;} //function to return sprite so that it may be drawn to the screen

  void setMapPosition(int x) {mapPosition = x;} // used to set the entity's map position
  int getMapPosition() const {return mapPosition;} // return's the mapPosition

  void setArrayPos(int x) {arrayPos = x;} // sets the entity's position in the entities array

  // stat and battle functions
  int getHealth() const {return health;}
  int getStrength() const {return strength;}
  int getDefense() const {return defense;}
  int getAgility() const {return agility;}
  int getExperienceOnDeath() const {return experienceOnDeath;}
  void subHealth(int);

  void setSpritePosition(int, int); // changes the player's position
  void updatePosition(int, int); // update the player's position relative to where they are now

  // combat functions
  int enemysTurn(int, int);

private:

  string name; // the name of the enemy

  int yPos; // entity's current y coordinate
  int xPos; // entity's current x coordinate

  sf::Texture texture; // texture containing the entity sprite sheet
  sf::Sprite sprite; // the entities current sprite

  int mapPosition;
  int arrayPos; // position in the entities array
  bool living; // determines whether the entity is living or not

  // Stats (if living)
  int health;
  int strength;
  int defense;
  int agility;
  int experienceOnDeath;
};

#endif

// functions

Entity::Entity(string n, string fileName, int pos, bool lifeStatus)
{
  name = n;

  texture.loadFromFile(fileName); // load fileName given

  sprite.setTexture(texture); // set the sprite's current texture

  mapPosition = pos; // set the entity's map position

  living = lifeStatus; // set living status

  if(living == true) // if the entity is living set its stats (change later)
  {
    health = 5;
    strength = 5;
    defense = 5;
    agility = 2;
    experienceOnDeath = 5;
  }
}

void Entity::subHealth(int x)
{
  health -= x; // subtract x from health

  if(health < 0) health = 0; // if health drops bellow 0 reset it to 0
}

void Entity::setSpritePosition(int x, int y)
{
  sprite.setPosition(x, y); // set the sprite's new position
  xPos = x; // update x and y coordinates
  yPos = y;
}

void Entity::updatePosition(int x, int y)
{
  xPos = xPos - x; // update x and y coordinates relative to where the player is now
  yPos = yPos - y;
  sprite.setPosition(xPos, yPos); // update sprite position as well
}

int Entity::enemysTurn(int playerAgility, int playerDefense)
{
  int result;

  srand(time(NULL)+100); // seed srand

  int dodgeChance = 0;

  // player's turn

  if(getAgility() < playerAgility) // if the enemy has higher agility then they have a chance to dodge your attack
  {
    dodgeChance = playerAgility - getAgility(); // calculate enemy dodge chance
  }

  // if dodgeChance > 0 roll dice to see if the enemy dodges your attack, if so exit function
  if(dodgeChance > 0)
  {
    if((rand() % 99) + 1 <= dodgeChance) return 0;
  }

  int damage = getStrength() - playerDefense;

  // add weapon modifier (will be a dice roll between 2 numbers depending on weapon)...
  // but for now its just 1-2:
  damage += (rand() % 2) + 1;

  result = damage;

  return result;
}
