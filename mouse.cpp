#include "Mouse.h"

using std::cout;
using std::endl;
using std::string;

Mouse::Mouse()
{
    dead = false;
    mouseTile.type = MOUSE;
    foodCount = 0;
}

Mouse::~Mouse()
{

}

//Methods
void Mouse::mouseTurn( tile gameMap[20][20], Cat catName )
{
    dead = checkDead( gameMap, catName );
    if( !dead )
    {
        moveMouse( gameMap );
        foodCount++;
        checkFood();
        dead = checkDead( gameMap, catName );
    }
}

void Mouse::moveMouse( tile gameMap[20][20] )
{
    if( gameMap[x][y].type != MOUSE)
    {
        cout << "Something messed up, the mouse isn't in the right place!\n\t\t\tOH DEAR!!!" << endl;
    }

    movementKey mouseMove = movementKey(rand() % 4);

    gameMap[x][y] = previousTile;

    if( mouseMove == NORTH )
    {
        y++;
        mouseTile.y++;
    }

    else if( mouseMove == SOUTH )
    {
        y--;
        mouseTile.y--;
    }

    else if(mouseMove == EAST )
    {
        x++;
        mouseTile.x++;
    }

    else if(mouseMove == WEST )
    {
        x--;
        mouseTile.x--;
    }

    previousTile = gameMap[x][y];
    gameMap[x][y] = mouseTile;
}

void Mouse::checkFood()
{
    if( previousTile.type == FOOD )
    {
        resetFoodCount();
    }
}

bool Mouse::checkDead( tile gameMap[20][20], Cat catName )
{
    bool dead = false;

    if( x == catName.getX() && y == catName.getY() )
    {
        dead = true;
    }

    if( previousTile.type == WATER )
    {
        dead = true;
    }

    if( previousTile.type == BRIDGE )
    {
        dead = true;
    }

    if( foodCount >= 100)
    {
        dead = true;
    }

    return dead;
}

bool Mouse::checkBridge( tile gameMap[20][20] )
{
    bool ifBridge = false;

    if( gameMap[x][y].type == BRIDGE)
    {
        ifBridge = true;
    }

    return ifBridge;
}

//Getters and Setters
int Mouse::getX()
{
    return x;
}

int Mouse::getY()
{
    return y;
}

tile Mouse::getPreviousTile()
{
    return previousTile;
}

tile Mouse::getMouseTile()
{
    return mouseTile;
}

bool Mouse::getDead()
{
    return dead;
}

void Mouse::setX( int x )
{
    this -> x = x;
}

void Mouse::setY( int y )
{
    this -> y = y;
}

void Mouse::setFirstPreviousTile( tileType type, int x, int y, SDL_Texture* image )
{
    this -> previousTile.type = type;
    this -> previousTile.x = x;
    this -> previousTile.y = y;
    this -> previousTile.image = image;
}

void Mouse::setPreviousTile( tile previousTile)
{
    this -> previousTile = previousTile;
}

void Mouse::setFirstMouseTile( tile mouseTile )
{
    this -> mouseTile.type = mouseTile.type;
    this -> mouseTile.x = mouseTile.x;
    this -> mouseTile.y = mouseTile.y; cout << "moving mouse back to " << this -> mouseTile.x << ", " << this -> mouseTile.y << endl;
    this -> mouseTile.image = mouseTile.image;
    this -> x = mouseTile.x;
    this -> y = mouseTile.y;
}

void Mouse::setMouseTile( tile mouseTile )
{
    this -> mouseTile = mouseTile;
    this -> x = mouseTile.x;
    this -> y = mouseTile.y;
}

void Mouse::resetFoodCount()
{
    foodCount = 0;
}

int Mouse::getFoodCount()
{
    return foodCount;
}
