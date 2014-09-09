#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "GameConfig.h"

class GameController
{
public:
    GameController();
    ~GameController();
    void runGame();

private:
    //SDL Setup
    SDL_Window* gameWindow;
    SDL_Renderer* gameRenderer;
    SDL_Surface* gameScreen;
    SDL_Texture* gameTextures[ TILE_TOTAL ];
    SDL_Texture* gameCaptions[ TOTAL_ENDINGS ];

    //SDL Setup Methods
    bool initSDL();
    bool initGame();
    void chooseGameSpeed();
    SDL_Surface* loadSurface( std::string );
    SDL_Texture* loadTexture( std::string );
    bool loadMedia();

    //Specific Data for Running Simulation
    Cat gameCat;
    Mouse gameMouse;
    SDL_Event gameEvent;
    SDL_Rect tileStretch;
    bool quitGame;
    int gameSpeed;

    //Methods for running and closing the game
    void printGameMap();
    void resetMap();
    void printEnding( gameEnding );
    void renderTexture();
    void oneRound();
    void recordMove();
    void checkQuit();
    void endSim();
    void closeGame();

    //Specific Data for Input
    std::string mapName;
    int numberOfGames;
    int height;
    int width;
    int tileSize;
    //Tile gameMap[20][20];
    tile gameMap[20][20];
    tile stockMap[20][20];
    tile stockMouse;
    tile stockCat;

    //Input File Methods
    bool loadInfoFile();
    tileType intToTileType( int, int, int, int, int );
    void makeTileTemplates();
    bool getStretch();
    std::string toString( int );

    //Specific Data for Output
    int randomSeed;
    std::string currentTime;
    int mouseEscapes;
    int mouseEaten;
    int mouseDrowns;
    int mouseStarves;
    int mousePositions[20][20];

    //Output File Methods
    bool outputResultFile();
};

#endif // GAMECONTROLLER_H
