#include "Cat.h"

using std::cout;
using std::endl;
using std::string;

Cat::Cat()
{

}

Cat::~Cat()
{

}

//Methods
void Cat::catTurn( tile gameMap[20][20], Mouse mouseName )
{
    moveCat( gameMap, mouseName );
}

void Cat::moveCat( tile gameMap[20][20], Mouse mouseName )
{
    //Check to see if cat is in the correct position
    if( gameMap[x][y].type != CAT)
    {
        cout << "Something messed up, the cat isn't in the right place!\n\t\t\tOH DEAR!!!" << endl;
    }

    bool goodMove = false;
    movementKey catMove;

    while( !goodMove )
    {
        catMove = movementKey(rand() % 4);
        goodMove = checkMove( gameMap, catMove, mouseName );
    }

    tile tempTile = gameMap[x][y];

    gameMap[x][y] = previousTile;

    if( catMove == NORTH )
    {
        y++;
        catTile.y++;
    }

    else if( catMove == SOUTH )
    {
        y--;
        catTile.y--;
    }

    else if(catMove == EAST )
    {
        x++;
        catTile.x++;
    }

    else if(catMove == WEST )
    {
        x--;
        catTile.x--;
    }

    previousTile = gameMap[x][y];
    gameMap[x][y] = catTile;
    //if
}

bool Cat::checkMove( tile gameMap[20][20], movementKey direction, Mouse mouseName )
{
    bool goodMove = true;
    int tempX = x;
    int tempY = y;

    ///Changing temporary coordinate to where it is moving to

    if( direction == NORTH )
    {
        tempY++;
    }

    else if( direction == SOUTH )
    {
        tempY--;
    }

    else if( direction == EAST )
    {
        tempX++;
    }

    else if( direction == WEST )
    {
        tempX--;
    }


    // starting conditionals for error checking
    if( gameMap[tempX][tempY].type == WATER )
    {
        goodMove = false;
    }

    else if( gameMap[tempX][tempY].type == MOUSE )
    {
        if( mouseName.getPreviousTile().type != MOUSE_HOLE )
        {
            goodMove = false;
        }
    }

    else if( gameMap[tempX][tempY].type == BRIDGE )
    {
        if( mouseName.getPreviousTile().type != MOUSE_HOLE )
        {
            goodMove = false;
        }
    }

    return goodMove;
}

bool Cat::checkBridge( tile gameMap[20][20] )
{
    bool ifBridge = false;

    if( gameMap[x][y].type == BRIDGE )
    {
        ifBridge = true;
    }

    return ifBridge;
}

// Getters and Setters
int Cat::getX()
{
    return x;
}

int Cat::getY()
{
    return y;
}

tile Cat::getCatTile()
{
    return catTile;
}

tile Cat::getPreviousTile()
{
    return previousTile;
}

void Cat::setX( int x )
{
    this -> x = x;
}

void Cat::setY( int y )
{
    this -> y = y;
}

void Cat::setFirstCatTile( tile catTile )
{
    this -> catTile.type = catTile.type;
    this -> catTile.x = catTile.x;
    this -> catTile.y = catTile.y;
    this -> catTile.image = catTile.image;
    this -> x = catTile.x;
    this -> y = catTile.y;
}

void Cat::setCatTile( tile catTile )
{
    this -> catTile = catTile;
    this -> x = catTile.x;
    this -> y = catTile.y;
}

void Cat::setFirstPreviousTile( tileType type, int x, int y, SDL_Texture* image )
{
    this -> previousTile.type = type;
    this -> previousTile.x = x;
    this -> previousTile.y = y;
    this -> previousTile.image = image;
}

void Cat::setPreviousTile( tile previousTile )
{
    this -> previousTile = previousTile;
}
