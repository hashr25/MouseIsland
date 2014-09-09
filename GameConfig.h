#ifndef GAMECONFIG_H
#define GAMECONFIG_H

// Screen Dimensions
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 640;

// Included libraries
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <time.h>

// Enumerated Types
enum movementKey
{
	NORTH,
	EAST,
	SOUTH,
	WEST
};

enum tileType
{
    WATER = -1,
    LAND,
    MOUSE,
    CAT,
    FOOD,
    MOUSE_HOLE,
    BRIDGE,
    TILE_TOTAL
};

/*enum gameSpeed ///This needs to be implemented
{
    SLOW,
    MEDIUM,
    FAST,
    INSTANT
};*/

enum gameEnding
{
    WIN,
    DROWN,
    EATEN,
    STARVE,
    TOTAL_ENDINGS
};

// Structures

struct tile
{
    tileType type;
    int x;
    int y;
    SDL_Texture* image;
};


// Included headers
#include "Mouse.h"
#include "Cat.h"

#endif // GAMECONFIG_H
