#ifndef CAT_H
    #define CAT_H

#include "GameConfig.h"
class Mouse;

class Cat// : public Tile
{
public:
    Cat();
    ~Cat();

    //Methods
    void catTurn( tile[20][20], Mouse );
    void moveCat( tile[20][20], Mouse );
    bool checkMove( tile[20][20], movementKey, Mouse );
    bool checkBridge( tile[20][20] );

    //Getters and Setters
    void setX( int );
    void setY( int );
    void setFirstCatTile( tile );
    void setCatTile( tile );
    void setFirstPreviousTile( tileType, int, int, SDL_Texture* );
    void setPreviousTile( tile );
    int getX();
    int getY();
    tile getPreviousTile();
    tile getCatTile();

private:
    int x;
    int y;
    tile previousTile;
    tile catTile;
};

#endif // CAT_H
