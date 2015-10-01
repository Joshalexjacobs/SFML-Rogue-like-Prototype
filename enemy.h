#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>
#include <string>
using namespace std;

class Entity
{
public:

  Entity(){} // default constructor
  Entity(string, string); // string constructor, names the enemy and loads the texture file

  string getName(){return name;}
  sf::Sprite getSprite() const {return sprite;} //function to return sprite so that it may be drawn to the screen
  void setSpritePosition(int, int); // changes the player's position
  void updatePosition(int, int); // update the player's position relative to where they are now

private:

  string name; // the name of the enemy

  int yPos; // player's current y coordinate
  int xPos; // player's current x coordinate
  sf::Texture texture; // texture containing the enemies sprite sheet
  sf::Sprite sprite; // the enemies current sprite

  // Stats
  int health;
  int strength;
  int endurance;
  int agility;

};

#endif

// functions


Entity::Enemy(string n, string fileName)
{
  name = n;

  texture.loadFromFile(fileName); // load fileName given

  sprite.setTexture(texture); // set the sprite's current texture

  health = 5;
  strength = 7;
  endurance = 7;
  agility = 5;

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
