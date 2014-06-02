#ifndef MOVER_H
    #define MOVER_H

    #include "enumAndStructs.h"

struct tileCoordinate;

class mover
{
protected:
    tileCoordinate coord;

public:
    void moveNorth(bool);
    void moveEast(bool);
    void moveSouth(bool);
    void moveWest(bool);
    void makeMove(bool);
};

#endif // MOVER_H
