#ifndef MAPGEN_H
    #define MAPGEN_H

class mapGen
{
private:
    int **tiles;
    int mouseStartX;
    int mouseStartY;
    int catStartX;
    int catStartY;
    int mouseHoleX;
    int mouseHoleY;
    int foodX;
    int foodY;
    int bridge1X;
    int bridge1Y;
    int bridge2X;
    int bridge2Y;

public:
    bool generateMap();

};

#endif // MAPGEN_H
