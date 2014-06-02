#ifndef ENUMANDSTRUCTS_H
    #define ENUMANDSTRUCTS_H

#include <string>

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
    BRIDGE,
    MOUSE,
    CAT,
    MOUSE_HOLE,
    FOOD,
    TILE_TOTAL
};

struct tile
{
    tileType type;
    int tileX;
    int tileY;
};

struct tileCoordinate
{
    int x;
    int y;
};

struct inputFile
{
    string fileName;
    int numberOfGames;
    int height;
    int width;

};

#endif // ENUMANDSTRUCTS_H
