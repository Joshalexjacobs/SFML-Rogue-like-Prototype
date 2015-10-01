#include "player.h"
#include "entity.h"

Player::Player(string fileName)
{
  texture.loadFromFile(fileName); // load fileName given

  sprite.setTexture(texture); // set the sprite's current texture

  xPos = 0; // set the x and y coordinates
  yPos = 0;

  health = 20;
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

int Player::playersTurn(Entity& enemy)
{
  int result;

  srand(time(NULL)); // seed srand

  /*
  int dodgeChance = 0;

  // player's turn

  if(player.getAgility() < enemy.getAgility()) // if the enemy has higher agility then they have a chance to dodge your attack
  {
    dodgeChance = enemy.getAgility() - player.getAgility(); // calculate enemy dodge chance
  }

  // if dodgeChance > 0 roll dice to see if the enemy dodges your attack, if so exit function
  */

  int damage = getStrength() - enemy.getDefense();

  // add weapon modifier (will be a dice roll between 2 numbers depending on weapon)...
  // but for now its just 1-5:
  damage += (rand() % 5) + 1;

  result = damage;

  return result;
}


