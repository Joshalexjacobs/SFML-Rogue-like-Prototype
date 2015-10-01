#include "Game.h"
#include "tileMap.h"
#include "player.h"
#include "entity.h"

#include <sstream>
#include <iostream> // cout, endl
using namespace std;

Game::Game()
{
    win.create(sf::VideoMode(512, 430), "SFML Rogue-like Prototype"); //create our SFML window

    // set the cursor's radius, pointCount, rotation, and starting position
    cursor.setRadius(5);
    cursor.setPointCount(3);
    cursor.setRotation(31);
    cursorPos = 306;
    cursor.setPosition(120, cursorPos); // set its starting position

    // set the menuBorder's size, position, outline, and color
    menuBorder.setSize(sf::Vector2f(125, 300));
    menuBorder.setPosition(sf::Vector2f(10, 300));
    menuBorder.setOutlineThickness(1.f);
    menuBorder.setFillColor(sf::Color::Black);

    // set the entities pointer array and entitiesSize
    entitiesSize = 1;
    entities = new Entity* [3]; // *THIS NEEDS TO BE SET TO THE AMOUNT OF ENTITES GENERATED OR ELSE THE GAME WILL CRASH*
    // OR IT CAN BE RESIZED AS ENTITIES ARE ADDED, BUT THIS METHOD IS EASIER
}

void Game::gameLoop()
{

  win.setFramerateLimit(40); // set the frame rate limit to 40
  win.setKeyRepeatEnabled(false);

  // create the level (8x16 squares, 128 squares total)
  const int level[]=
  {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 2, 2, 2, 2, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
    0, 2, 2, 2, 2, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
    0, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
    0, 2, 2, 2, 2, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
    0, 2, 2, 2, 2, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
    0, 2, 2, 2, 2, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  };

  // create the TileMap
  TileMap map;
  map.load("sheet.png", sf::Vector2u(32, 32), level, 16, 8);

  // create the Player
  Player player("knight.png");

  int playerMapPos = 17; // the player's position on the level array

  player.setSpritePosition(32, 32); // set player's starting position

  // create gameFont
  sf::Font gameFont;
  gameFont.loadFromFile("AtariSmall.ttf"); // load AtariSmall into gameFont

  // create text that will constantly be displayed across the bottom
  sf::Text text;
  text.setFont(gameFont); // set it to the gameFont
  text.setCharacterSize(22); // set the size to 22px
  text.setString("Welcome to the world"); // set the text to be displayed
  text.setPosition(10,250); // set the text's position

  // create player health text
  sf::Text playerHealth;
  playerHealth.setFont(gameFont); // set it to the gameFont
  playerHealth.setCharacterSize(22); // set the size to 22px
  playerHealth.setString("HP: " + intToString(player.getHealth())); // set the text to be displayed
  playerHealth.setPosition(400,250); // set the text's position

  // create first slime
  Entity slime("Slime", "slime.png", 58, true);
  slime.setSpritePosition(320, 96);

  // create second enemy
  Entity slimeTwo("Slime", "slime.png", 60, true);
  slimeTwo.setSpritePosition(384, 96);
  entitiesSize++; // increase array size

  // create npc
  Entity tom("Tom", "npc.png", 20, true);
  tom.setSpritePosition(128, 32);
  entitiesSize++; // increase array size

  // dynamic entity pointer array
  Entity* temp = &slime; // creating a temp and set it to first slime
  entities[0] = temp; // set the first pointer to look at our first enemy, slime
  temp = &slimeTwo; // set temp to second slime
  entities[1] = temp; // set the second pointer to look at second slime

  temp = &tom; // set temp to npc tom
  entities[2] = temp; // set the second pointer to look at tom

  bool pause = false; // game starts unpaused

  /*GAME LOOP*/

  while (win.isOpen())
  {
    bool turn = false; // determines if a turn has passed (activated whenever the player moves)
    sf::Event event;

    /*EVENT LOOP*/

    while (win.pollEvent(event)) // while there is an event
    {
      // EXIT GAME
      if (event.type == sf::Event::Closed) // if the user decides to quit
      {
        win.close(); // close the window
      }

      /*MOVEMENT*/

      // MOVE LEFT
      if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && pause == false)
      {
        turn = true; // if the player intended to move set turn to true
        if(player.getDirection() != 'l') player.setDirection('l'); // set the player's direction

        if(checkCollisions(playerMapPos - 1, level)) // if the player is not trying to move into a wall (handles collision)
        {
          player.updatePosition(32, 0); // update player's position
          playerMapPos -= 1; // update player's position on tilemap

          wait(.1);
        }
      }

      // MOVE RIGHT
      if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && pause == false)
      {
        turn = true;
        if(player.getDirection() != 'r') player.setDirection('r');

        if(checkCollisions(playerMapPos + 1, level))
        {
          player.updatePosition(-32, 0);
          playerMapPos += 1;

          wait(.1);
        }
      }

      // MOVE UP
      if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && pause == false)
      {
        turn = true;
        if(player.getDirection() != 'u') player.setDirection('u');

        if(checkCollisions(playerMapPos - 16, level))
        {
          player.updatePosition(0, 32);
          playerMapPos -= 16;

          wait(.1);
        }
      }

      // MOVE DOWN
      if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && pause == false)
      {
        turn = true;
        if(player.getDirection() != 'd') player.setDirection('d');

        if(checkCollisions(playerMapPos + 16, level))
        {
          player.updatePosition(0, -32);
          playerMapPos += 16;

          wait(.1);
        }
      }

      /*MENU EVENTS*/

      // PAUSE
      if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && pause == false)
      {
        pause = true; // if space is hit enter the menu and pause all turns

        text.setString("Game Paused\n- - - - - -\nTalk\nAttack\nInventory\nStats\nBack"); // output that the game is paused

        wait(.5); // wait for half a second
      }

      // SELECT
      if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && pause == true)
      {
        //TALK  - 1

        //ATTACK - 2
        if(cursorClick() == 2)
        {
          int arrayPos = checkCombat(player.getDirection(), playerMapPos);

          if(arrayPos > -1)
          {
            bool combat = true;

            text.setString("You have engaged a " + entities[arrayPos]->getName() + "!");

            wait(0.5);

            // create enemy health text
            sf::Text enemyHealth;
            enemyHealth.setFont(gameFont); // set it to the gameFont
            enemyHealth.setCharacterSize(22); // set the size to 22px
            enemyHealth.setString(entities[arrayPos]->getName() + ": " + intToString(entities[arrayPos]->getHealth())); // set the text to be displayed
            enemyHealth.setPosition(400,280); // set the text's position

            while(combat == true)
            {
              sf::Event combatEvents;

                while (win.pollEvent(combatEvents))
                {
                  if(combatEvents.type == sf::Event::Closed) // if the user decides to quit
                  {
                    win.close(); // close the window
                    combat = false; // end combat loop
                  }

                  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
                  {
                    int playerDMG = player.playersTurn(entities[arrayPos]->getAgility(), entities[arrayPos]->getDefense()); // player attacks first
                    int enemyDMG = entities[arrayPos]->enemysTurn(player.getAgility(), player.getDefense()); // enemy attacks

                    size_t lineCount = std::count(text.getString().begin(), text.getString().end(), '\n');

                    if(lineCount >= 5)
                    {
                      text.setString("");
                      text.setPosition(10,227); // set the text's position
                    }

                    text.setString(text.getString() + "\n" + intToString(playerDMG) + " damage dealt!"); // output damage

                    if(battle(playerDMG, enemyDMG, player, arrayPos))
                    {

                      if(entities[arrayPos]->getHealth() <= 0) // if the enemy dies
                      {
                        text.setString("The " + entities[arrayPos]->getName() + " is dead!");
                        combat = false; // end combat
                      }

                      else  // if you die
                      {
                        text.setString(entities[arrayPos]->getName() + " attacked you for " + intToString(enemyDMG) + " damage!\nYOU ARE DEAD");
                        combat = false;
                        // return to last checkpoint
                      }
                    }

                    else text.setString(text.getString() + '\n' + entities[arrayPos]->getName() + " attacked you for " + intToString(enemyDMG) + " damage!"); // output damage

                    // update player and enemy health to be displayed
                    enemyHealth.setString(entities[arrayPos]->getName() + ": " + intToString(entities[arrayPos]->getHealth()));
                    playerHealth.setString("HP: " + intToString(player.getHealth()));

                    wait(.5); // wait half a second
                  }

                }

              drawEverything(map);

              win.draw(player.getSprite()); // draw the player sprite to the screen
              win.draw(text); // draw the current text to the screen
              win.draw(playerHealth); // draw player's HP text
              win.draw(enemyHealth);
              win.display(); // display our current frame
            }

            if(player.getHealth() >= 0)
            {
              deleteEntity(arrayPos); // if the player is still alive, delete the enemy entity
            }

            else text.setString(text.getString() + "\nGAME OVER"); // else GAME OVER... until i program a checkpoint system

            text.setPosition(10,250); // reset the text's position
            pause = false;

          }

          else
          {
            pause = false;

            text.setString("There is nothing to attack");

            cursor.setPosition(120, 306); // reset cursor position
            cursorPos = 306;

            wait(.2); // wait for .2 second
          }
        }

        //INVENTORY - 3
        if(cursorClick() == 3)
        {
          text.setString("Inventory Screen 123456789"); // set the text to be displayed
          text.setPosition(5,400); // set the text's position

          bool invScreen = true;

          while(invScreen == true)
          {
            sf::Event invEvents;

            while (win.pollEvent(invEvents))
            {
              if(invEvents.type == sf::Event::Closed) // if the user decides to quit
              {
                win.close(); // close the window
                invScreen = false; // end combat loop
              }
            }

            drawEverything(map);

            // draw squares for inventory slots
            win.draw(player.getSprite()); // draw the player sprite to the screen
            win.draw(text); // draw the current text to the screen
            win.display();
          }
        }

        //STATS - 4

        //BACK - 5
        if(cursorClick() == 5)
        {
          pause = false; // set pause to false

          cursor.setPosition(120, 306); // reset cursor position
          cursorPos = 306;

          text.setString(""); // empty text

          wait(.2); // wait for .2 second
        }
      }

      // MENU DOWN
      if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && pause == true)
      {
        moveCursor(true); // call move cursor function
      }

      // MENU UP
      if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && pause == true)
      {
        moveCursor(false); // call move cursor function
      }

      // EXIT MENU
      if(sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace) && pause == true) // BackSpace
      {
        pause = false; // if backspace is pressed, exit the menu

        cursor.setPosition(120, 306); // reset cursor position
        cursorPos = 306;

        text.setString("");

        wait(.1); // wait for .1 second
      }

    }

    //if(turn == true)
      // move the ai

    /*WINDOW EVENTS*/

    drawEverything(map);

    // if pause is true draw menu border
    if(pause == true)
    {
      win.draw(menuBorder);
      win.draw(cursor);
    }

    win.draw(player.getSprite()); // draw the player sprite to the screen
    win.draw(text); // draw the current text to the screen
    win.draw(playerHealth); // draw player's HP text

    win.display(); // display our current frame

  }

}

// this function is rather self explanatory, it draws every asset in the game
void Game::drawEverything(TileMap map)
{
  win.clear(); // clear the screen

  win.draw(map); // draw the map

  for(int i = 0; i < entitiesSize; i++)
  { // draw every existing entity
    win.draw(entities[i]->getSprite());
  }
}

bool Game::checkCollisions(int object, const int* level)
{
  bool result = true;

  if(level[object] == 0) result = false; // if object is about to collide with the wall

  for(int i = 0; i < entitiesSize; i++)  // for loop that runs the length of entities array
  {
    if(object == entities[i]->getMapPosition()) // checks to see if the object/player is trying to move into a position where an entity already exists
    {
      result = false; // if so return false
      break;
    }
  }

  return result;
}

int Game::checkCombat(char dir, int playerPos)
{
  int result = -1;

  if(dir == 'r')
  {
     for(int i = 0; i < entitiesSize; i++)
     {
       if(entities[i]->getMapPosition() == playerPos + 1)
       {
         result = i;
         break;
       }
     }
  }

  else if(dir == 'l')
  {
     for(int i = 0; i < entitiesSize; i++)
     {
       if(entities[i]->getMapPosition() == playerPos - 1)
       {
         result = i;
         break;
       }
     }
  }

  else if(dir == 'u')
  {
     for(int i = 0; i < entitiesSize; i++)
     {
       if(entities[i]->getMapPosition() == playerPos - 16)
       {
         result = i;
         break;
       }
     }
  }

  else if(dir == 'd')
  {
     for(int i = 0; i < entitiesSize; i++)
     {
       if(entities[i]->getMapPosition() == playerPos + 16)
       {
         result = i;
         break;
       }
     }
  }

  return result;
}

bool Game::battle(int playerDMG, int enemyDMG, Player& player, int i)
{
  bool result = false;

  entities[i]->subHealth(playerDMG); // player deals damage first

  if(entities[i]->getHealth() <= 0) return true; // if the enemy is dead return true

  player.subHealth(enemyDMG); // enemy deals damage second

  if(player.getHealth() <= 0) return true; // if the enemy is dead return true

  return result;
}

void Game::deleteEntity(int x)
{
  entitiesSize--; // resize entitiesSize
  Entity** temp = new Entity* [entitiesSize]; // create a temporary array
  //temp = new Entity* [entitiesSize];

  for(int i = 0; i < entitiesSize; i++)
  { // copy all contents into temp array
    if(i >= x) // do not copy the entity being deleted
    {
      temp[i] = entities[i + 1]; // skip to the next entity
      continue;
    }

    temp[i] = entities[i]; // else continue copying the loop
  }

  delete [] entities; // delete old array
  entities = new Entity*[entitiesSize];

  for(int i = 0; i < entitiesSize; i++)
  {
    entities[i] = temp[i];
  }

  delete [] temp; // delete temp
}

void Game::moveCursor(bool isDown)
{
  if(isDown == true)
  {
    if(cursorPos == 406)
    {
      cursor.setPosition(120, 306);
      cursorPos = 306;
    }

    else
    {
      cursor.setPosition(120, cursorPos + 25);
      cursorPos += 25;
    }
  }

  else if(isDown == false)
  {
    if(cursorPos == 306)
    {
      cursor.setPosition(120, 406);
      cursorPos = 406;
    }

    else
    {
      cursor.setPosition(120, cursorPos - 25);
      cursorPos -= 25;
    }
  }
}

// this function is currently missing the TALK and STATS option
int Game::cursorClick()
{
  if(cursorPos == 331) return 2; // ATTACK
  if(cursorPos == 356) return 3; // INVENTORY
  if(cursorPos == 406) return 5; // BACK

  return 0; // just in case none of the above conditions are met
}

void Game::wait(float seconds)
{

  sf::Time currentTime = gameClock.getElapsedTime(); // store the current clock time

  while(gameClock.getElapsedTime().asSeconds() < currentTime.asSeconds() + seconds)
  {
    // this while loop waits x second(s) before finishing
  }

}

string Game::intToString(int n)
{
  stringstream ss; // create stringstream
  ss << n; // add int to stringstream
  return ss.str();
}
