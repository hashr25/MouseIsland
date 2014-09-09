#ifndef MOUSE_H
    #define MOUSE_H

#include "GameConfig.h"

class Cat;

class Mouse// : public Tile
{
public:
    Mouse();
    ~Mouse();

    //Methods
    void mouseTurn( tile[20][20], Cat );
    void moveMouse( tile[20][20] );
    void checkFood();
    bool checkDead( tile[20][20], Cat );
    bool checkBridge( tile[20][20] );
    int foodCount;

    //Getters and Setters
    void setX( int );
    void setY( int );
    void setFirstPreviousTile( tileType, int, int, SDL_Texture* );
    void setPreviousTile( tile );
    void setFirstMouseTile( tile );
    void setMouseTile( tile );
    void resetFoodCount();
    int getFoodCount();
    int getX();
    int getY();
    tile getPreviousTile();
    tile getMouseTile();
    bool getDead();

private:
    bool dead;
    int x;
    int y;
    tile previousTile;
    tile mouseTile;
};

#endif // MOUSE_H
