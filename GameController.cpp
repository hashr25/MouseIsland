#include "GameController.h"

using std::cout;
using std::cin;
using std::endl;
using std::ifstream;

/// Constructor and Destructors
GameController::GameController()
{
    initGame();
    quitGame = false;//change to true to get one refresh and delay, false for repeat until x is clicked
    mouseDrowns = 0;
    mouseEaten = 0;
    mouseEscapes = 0;
    mouseStarves = 0;
}

GameController::~GameController()
{
    closeGame();
}

/// /////////////////////////////

/// SDL Setup
bool GameController::initSDL()
{
    //Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_EVERYTHING ) < 0 )
	{
		cout << "SDL could not initialize! SDL Error: " <<  SDL_GetError() << endl;
		success = false;
	}
	else
	{
	    //Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gameWindow = SDL_CreateWindow( "Mouse Island", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gameWindow == NULL )
		{
			cout << "Window could not be created! SDL Error: " << SDL_GetError() << endl;
			success = false;
		}
		else
		{
		    //creates renderer
		    gameRenderer = SDL_CreateRenderer( gameWindow, -1, SDL_RENDERER_ACCELERATED);
		    if( gameRenderer == NULL )
            {
                cout << "Renderer could not be created. SDL Error: " << SDL_GetError();
                success = false;
            }

            else
            {
                //Sets renderer color
                SDL_SetRenderDrawColor( gameRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

                //Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					cout << "SDL_image could not initialize! SDL_mage Error: " << IMG_GetError() << endl;
					success = false;
				}
            }

			gameScreen = SDL_GetWindowSurface( gameWindow );
			SDL_UpdateWindowSurface( gameWindow );
		}
	}

    cout << "init sdl completed" << endl; // used for testing
	return success;
}

bool GameController::initGame() //Need to finish after loading media.
{
    bool success = true;

    if( !initSDL() )
    {
        cout << "Failed to initialize SDL. " << endl;
        success = false;
    }
    else
    {
        if( !loadMedia() )
        {
            cout << "failed to load media" << endl;
            success = false;
        }

        else
        {
            if( !loadInfoFile())
            {
                cout << "failed to load info file." << endl;
                success = false;
            }

            else
            {
                if( !getStretch() )
                {
                    cout << "failed to create stretch rect." << endl;
                    success = false;
                }
            }
        }
    }
    //chooseGameSpeed();
    gameSpeed = 80;

    cout << "init game completed" << endl; // used for testing
    return success;
}

void GameController::chooseGameSpeed()
{
    ///This will display 4 buttons to choose game speed.
    int chosenSpeed = rand() % 4;

    if( chosenSpeed == 0 )
    {
        gameSpeed = 500;
        cout << "Playing on slow" << endl;
    }

    else if( chosenSpeed == 1 )
    {
        gameSpeed = 250;
        cout << "Playing on medium" << endl;
    }

    else if( chosenSpeed == 2 )
    {
        gameSpeed = 75;
        cout << "Playing on fast" << endl;
    }

    else if( chosenSpeed == 3 )
    {
        gameSpeed = 0;
        cout << "Playing on instant" << endl;
    }
}

SDL_Surface* GameController::loadSurface( std::string path ) //taken from lazy foo tutorials
{
    //The final optimized image
	SDL_Surface* optimizedSurface = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = SDL_LoadBMP( path.c_str() );
	if( loadedSurface == NULL )
	{
		cout << "Unable to load image! SDL Error: " << path.c_str() << " " <<  SDL_GetError() << endl;
	}
	else
	{
		//Convert surface to screen format
		optimizedSurface = SDL_ConvertSurface( loadedSurface, gameScreen->format, NULL );
		if( optimizedSurface == NULL )
		{
			cout << "Unable to optimize image! SDL Error: " << path.c_str() << " " << SDL_GetError() << endl;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	return optimizedSurface;
}

SDL_Texture* GameController::loadTexture( std::string path ) // taken from lazy foo tutorials
{
    //The final texture
    SDL_Texture* newTexture = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == NULL )
    {
        cout << "Unable to load image! SDL_image Error: " << path.c_str() << IMG_GetError() << endl;
    }
    else
    {
        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gameRenderer, loadedSurface );
        if( newTexture == NULL )
        {
            cout << "Unable to create texture from! SDL Error: " << path.c_str() << SDL_GetError() << endl;
        }

        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }

    return newTexture;
}

bool GameController::loadMedia()
{
    //Loading success flag
	bool success = true;

	//Load LAND surface
	gameTextures[ LAND ] = loadTexture( "land.bmp" );
	if( gameTextures[ LAND ] == NULL )
	{
		cout <<  "Failed to load LAND image!" << endl;
		success = false;
	}

	//Load WATER surface
	gameTextures[ WATER ] = loadTexture( "water.bmp" );
	if( gameTextures[ WATER ] == NULL )
	{
		cout << "Failed to load WATER image!" << endl;
		success = false;
	}

	//Load BRIDGE surface
	gameTextures[ BRIDGE ] = loadTexture( "bridge.bmp" );
	if( gameTextures[ BRIDGE ] == NULL )
	{
		cout << "Failed to load BRIDGE image!" << endl;
		success = false;
	}

	//Load MOUSE surface
	gameTextures[ MOUSE ] = loadTexture( "mouse.bmp" );
	if( gameTextures[ MOUSE ] == NULL )
	{
		cout << "Failed to load MOUSE image!" << endl;
		success = false;
	}

	//Load CAT surface
	gameTextures[ CAT ] = loadTexture( "cat.bmp" );
	if( gameTextures[ CAT ] == NULL )
	{
		cout << "Failed to load CAT image!" << endl;
		success = false;
	}

	//Load MOUSE_HOLE surface
	gameTextures[ MOUSE_HOLE ] = loadTexture( "mouseHole.bmp" );
	if( gameTextures[ MOUSE_HOLE ] == NULL )
	{
		cout << "Failed to load MOUSE_HOLE image!" << endl;
		success = false;
	}

	//Load FOOD surface
	gameTextures[ FOOD ] = loadTexture( "food.bmp" );
	if( gameTextures[ FOOD ] == NULL )
	{
		cout << "Failed to load FOOD image!" << endl;
		success = false;
	}

	//Game Captions
	gameCaptions[ WIN ] = loadTexture( "mouseEscape.bmp" );
	if( gameCaptions[ WIN ] == NULL )
    {
        cout << "Failed to load winning caption!" << endl;
        success = false;
    }

    gameCaptions[ DROWN ] = loadTexture( "mouseDrown.bmp" );
	if( gameCaptions[ DROWN ] == NULL )
    {
        cout << "Failed to load drowning caption!" << endl;
        success = false;
    }

    gameCaptions[ EATEN ] = loadTexture( "mouseEaten.bmp" );
	if( gameCaptions[ EATEN ] == NULL )
    {
        cout << "Failed to load eaten caption!" << endl;
        success = false;
    }

    gameCaptions[ STARVE ] = loadTexture( "mouseStarve.bmp" );
	if( gameCaptions[ STARVE ] == NULL )
    {
        cout << "Failed to load winning caption!" << endl;
        success = false;
    }


	return success;
}

/// ////////////////////////////////

/// Running and Closing the game


void GameController::runGame()
{
    for( int simulation = 0; simulation < numberOfGames; simulation++ )
    {
        resetMap();
        quitGame = false;

        while( !quitGame )
        {
            //Handle events on queue
            while( SDL_PollEvent( &gameEvent ) != 0 )
            {
                //User requests quit
                if( gameEvent.type == SDL_QUIT )
                {
                    quitGame = true;
                    numberOfGames = simulation;
                }
            }

            oneRound();
            checkQuit();

            SDL_Delay( gameSpeed );
        }

        endSim();
        SDL_Delay( gameSpeed * 10 );
    }

    /*printGameMap();
    SDL_RenderPresent( gameRenderer );
    printGameMap();
    SDL_Delay( gameSpeed * 50 );*/

    closeGame();

    //printCatDied();
    //SDL_Delay(1000);
    //printGameMap();
    //SDL_Delay(1000);
    //printMouseDied();
}

void GameController::resetMap()
{
    //Remapping tiles and cat/mouse
    for( int i = 0; i < height; i++ )
    {
        for( int j = 0; j < width; j++ )
        {
            gameMap[i][j] = stockMap[i][j];
        }
    }

    gameMouse.setMouseTile( stockMouse );
    gameMouse.resetFoodCount();
    gameMouse.setFirstPreviousTile( LAND, stockMouse.x, stockMouse.y, gameTextures[ LAND ] );
    gameCat.setCatTile( stockCat );
    gameCat.setFirstPreviousTile( LAND, stockMouse.x, stockMouse.y, gameTextures[ LAND ] );
}

void GameController::printGameMap()
{
    //SDL_Delay(1000);
    //Clearing Renderer
    SDL_RenderClear( gameRenderer );

    /// Printing the map
    for(int i = 0; i < height; i++)
    {
        tileStretch.y = i * tileSize;

        for(int j = 0; j < width; j++)
        {
            tileStretch.x = j * tileSize;

            SDL_RenderCopy( gameRenderer, gameMap[i][j].image, NULL, &tileStretch );
        }
    }
}

void GameController::printEnding( gameEnding outcome )
{
    SDL_Rect displayEnding;
    displayEnding.h = 150;
    displayEnding.w = 460;
    displayEnding.x = 85;
    displayEnding.y = 220;

    //Coping dead cat image to renderer
    SDL_RenderCopy( gameRenderer, gameCaptions[ outcome ], NULL, &displayEnding );

    //Refresh Renderer
    SDL_RenderPresent( gameRenderer );
}

void GameController::oneRound()
{
    gameCat.catTurn( gameMap, gameMouse );
    gameMouse.mouseTurn( gameMap, gameCat );
    recordMove();

    if( gameSpeed != 0 )
    {
        printGameMap();
        SDL_RenderPresent( gameRenderer );
    }

}

void GameController::recordMove()
{
    mousePositions[gameMouse.getX()][gameMouse.getY()] = mousePositions[gameMouse.getX()][gameMouse.getY()] + 1;
}

void GameController::checkQuit()
{
    if( gameMouse.getDead() )
    {
        quitGame = true;
        cout << "mouse found dead at " << gameMouse.getX() << ", " << gameMouse.getY() << endl;
    }
}

void GameController::endSim()
{
    if( gameMouse.getFoodCount() >= 100 )
    {
        mouseStarves++;
        printEnding( STARVE );
    }

    else if( gameMouse.getFoodCount() < 100 || gameMouse.getDead() )
    {
        if( gameMouse.getX() == gameCat.getX() && gameMouse.getY() == gameCat.getY() )
        {
            mouseEaten++;
            printEnding( EATEN );
        }

        else if( gameMouse.getPreviousTile().type == WATER )
        {
            mouseDrowns++;
            printEnding( DROWN );
        }

        else if( gameMouse.getPreviousTile().type == BRIDGE )
        {
            mouseEscapes++;
            printEnding( WIN );
        }
    }


    //SDL_RenderPresent( gameRenderer );
    //SDL_Dely(2000);
}

void GameController::closeGame()
{
    //Deallocate surfaces
	for( int i = 0; i < TILE_TOTAL; i++ )
	{
		SDL_DestroyTexture( gameTextures[ i ] );
		gameTextures[ i ] = NULL;
	}

	for( int i = 0; i < TOTAL_ENDINGS; i++ )
    {
        SDL_DestroyTexture( gameCaptions[ i ] );
        gameCaptions[ i ] = NULL;
    }cout << "deleted textures" << endl;

	//Destroy window
	SDL_DestroyWindow( gameWindow );
	gameWindow = NULL; cout << "deleted window" << endl;

    //Destroy game surface
	SDL_FreeSurface( gameScreen );
	gameScreen = NULL; cout << "deleted game surface" << endl;

	//Destroy renderer
	SDL_RenderClear(gameRenderer);
	gameRenderer = NULL; cout << "deleted renderer" << endl;


	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit(); cout << "closed SDL successfully" << endl;

	outputResultFile();
}

/// ///////////////////////////////

///File Input
bool GameController::loadInfoFile() // need to turn on user input to get file name
{
    bool success = true;
    bool goodInput = false;

    /*while(!goodInput)
    {
        cout << "Enter the input file name: ";
        cin >> fileName;

        if(cin.fail())
        {
            goodInput = false;
            cin.clear();
            cin.ignore(10000, '\n');
        }
        else
        {
            goodInput = true;
        }
    }*/

    //Input file
    std::ifstream inputFile;
    cout << "loading input file" << endl; // testing purposes
    //inputFile.open(fileName.c_str());
    inputFile.open("input/doubleFullMap.txt");
    cout << "loaded input file" << endl; // testing purposes

    //Temp variables
    std::string tempLine = "";
    std::string singleLines[24];

    //Failure to load file
    if(inputFile.fail())
    {
        cout << "Error! Could not load input file." << endl;
        success = false;
    }


    else
    {
        //Gets each line of file and puts into an array.
        int counter = 0; cout << "starting to load data from input file." << endl;
        while(std::getline(inputFile, tempLine))
        {
            singleLines[counter] = tempLine;
            counter++;
        }

        //Converting strings to map information
        mapName = singleLines[0];
        numberOfGames = atoi(singleLines[1].c_str());
        height = atoi(singleLines[2].c_str()); cout << "height: " << height << endl;
        width = atoi(singleLines[3].c_str()); cout << "width: " << width << endl;

        randomSeed = time(NULL);
        //randomSeed = 1406053565; // insert random seed here to replicate simulation
                                // be sure to use same map file
        srand( randomSeed );

        // Make the current time for naming output file.
        time_t rawtime;
        struct tm * timeinfo;
        time ( &rawtime );
        timeinfo = localtime ( &rawtime );
        currentTime = asctime( timeinfo );
        delete timeinfo;
        currentTime[13] = '-';
        currentTime[16] = '-';
        currentTime.erase(24,2);

        //currentTime = std::string(timerThing);
        cout << "current time: " << currentTime << endl;

        //Mapping the tiles
        cout << "starting to map tiles" << endl;
        for(int i = 0; i < height; i++) //loop for each line
        {
            std::string tempToNumber = "";
            int tempNumber = 0;
            tileType tempTileType;
            counter = 0;


            for(int j = 0; j < singleLines[i+4].size(); j++) //loop to go through the string
            {
                // This is to account for double spaces in the input file
                if(singleLines[i+4].substr(j,2) == "  ")
                {
                    j++;
                }

                if(j == 0 && singleLines[i+4].at(j) == ' ')
                {
                    j++;
                }


                //Add to tile array
                if(singleLines[i+4].at(j) == ' ' || j == singleLines[i+4].size()-1)
                {
                    tempNumber = atoi( tempToNumber.c_str() );
                    tempTileType = intToTileType( tempNumber, counter, i, width-1, height-1 );

                    /// Using Class ///
                    //gameMap[j][i].setType(tempTileType);
                    //gameMap[j][i].setX(j);
                    //gameMap[j][i].setY(i);
                    //gameMap[j][i].setImage( getTileSurface( tempTileType ) );

                    /// Using Struct ///
                    stockMap[i][counter].type = tempTileType;
                    stockMap[i][counter].x = counter;
                    stockMap[i][counter].y = i;
                    stockMap[i][counter].image = gameTextures[ tempTileType ];

                    //error checking for image import
                    if(stockMap[i][counter].image == NULL)
                    {
                        cout << "game map[" << i << "][" << counter << "] did not map an image" << endl;
                    }

                    //Syncing location of objects with map
                    if( tempTileType == CAT )
                    {
                        stockCat.type = CAT;
                        stockCat.x = i;
                        stockCat.y = counter;
                        stockCat.image = gameTextures[ CAT ];cout << "stockCat at " << stockCat.x << ", " << stockCat.y << endl;

                        gameCat.setX(counter);
                        gameCat.setY(i);
                        gameCat.setCatTile( gameMap[i][counter] );
                        //gameCat.setImage( gameTextures[ CAT ]);
                    }

                    else if( tempTileType == MOUSE )
                    {
                        stockMouse.type = MOUSE;
                        stockMouse.x = i;
                        stockMouse.y = counter;
                        stockMouse.image = gameTextures[ MOUSE ];cout << "stockMouse at " << stockMouse.x << ", " << stockMouse.y << endl;

                        gameMouse.setX(counter);
                        gameMouse.setY(i);
                        gameMouse.setMouseTile( gameMap[i][counter] );
                        //gameMouse.setImage( gameTextures[ MOUSE ]);
                    }

                    if( stockMap[i][counter].image == NULL )
                    {
                    cout << "error mapping the image to tile" << endl;
                    }

                    tempToNumber = "";
                    counter++;
                }



                tempToNumber.append(singleLines[i+4].substr(j));
            }// end of inner for loop
            counter = 0;
        }// end of outer for loop
    }

    if(stockMap[0][0].type == NULL)
    {
        cout << "did not map top line" << endl;
    }

    for( int i = 0; i < 20; i++ )
    {
        for( int j = 0; j < 20; j++ )
        {
            mousePositions[i][j] = 0;
        }
    }

    inputFile.close();

    return success;
}

tileType GameController::intToTileType( int toConvert, int xPos, int yPos, int maxX, int maxY )
{
    tileType typeToReturn;

    if(toConvert == -1)
    {
        typeToReturn = WATER;
    }
    else if(toConvert == 0)
    {
        if(xPos == 0 || yPos == 0 || xPos == maxX || yPos == maxY)
        {
            typeToReturn = BRIDGE;
        }
        else
        {
            typeToReturn = LAND;
        }
    }
    else if(toConvert == 1)
    {
        typeToReturn = MOUSE;
    }
    else if(toConvert == 2)
    {
        typeToReturn = CAT;
    }
    else if(toConvert == 3)
    {
        typeToReturn = FOOD;
    }
    else if(toConvert == 4)
    {
        typeToReturn = MOUSE_HOLE;
    }

    return typeToReturn;
}

bool GameController::getStretch()
{
    bool success = true;

    /// Setting up size for tiles.
    if( height > 10 || width > 10 )
    {
        tileSize = 32;
    }
    else
    {
        tileSize = 64;
    }

    /// Setting up stretch rect to adjust size if larger than 10 in any direction.
    tileStretch.x = 0;
    tileStretch.y = 0;
    tileStretch.w = tileSize;
    tileStretch.h = tileSize;

    if( tileStretch.w != tileStretch.h )
    {
        cout << "could not create stretch rect" << endl;
        success = false;
    }

    cout << "made stretch rect" << endl;
    return success;
}

std::string GameController::toString( int value ) // Function taken from stack overflow
{
    std::ostringstream os ;
    os << value ;
    return os.str() ;
}

/// ///////////////////////////////

///File Output
bool GameController::outputResultFile() // Remember to setup timestamp for output file
{
    bool success = true;

    std::ofstream outputFile; cout << "create output variable" << endl;
    std::string tempString = "";

    std::string fileName = "results/Results from " + currentTime + ".txt"; cout << "create filename to output to: " << fileName << endl;
    outputFile.open(fileName.c_str()); cout << "open output file" << endl;

    if(outputFile.fail())
    {
        cout << "Error! Could not load output file." << endl;
        success = false;
    }

    else
    {
        std::string outputStrings[29]; cout << "create output file lines" << endl;

        outputStrings[0] = "Map name: " + mapName; cout << "create first line " << outputStrings[0] << endl;
        outputStrings[1] = "Number of simulations: " + toString(numberOfGames); cout << "create second line " << outputStrings[1] << endl;
        outputStrings[2] = "Random seed used: " + toString(randomSeed); cout << "create third line " << outputStrings[2] << endl;
        outputStrings[3] = "Mouse Escapes: " + toString(mouseEscapes); cout << "create fourth line " << outputStrings[3] << endl;
        outputStrings[4] = "Mouse Eaten: " + toString(mouseEaten); cout << "create fifth line " << outputStrings[4] <<endl;
        outputStrings[5] = "Mouse Drowns: " + toString(mouseDrowns); cout << "create sixth line " << outputStrings[5] <<endl;
        outputStrings[6] = "Mouse Starves: " + toString(mouseStarves); cout << "create seventh line " << outputStrings[6] << endl;
        outputStrings[7] = "Tile Frequency Map: "; cout << "create eighth line " << outputStrings[7] << endl;
        outputStrings[8] = "Each number represents the number of times the mouse visited the tile."; cout << "create ninth line" << endl;

        //make frequency table in string form
        for( int i = 0; i < height-1; i++ )
        {
            cout << "line #" << i << endl;
            for( int j = 0; j < width; j++ )
            {
                if( mousePositions[i][j] < 10 )
                {
                    outputStrings[i+9].append( "   " );
                }
                else if( mousePositions[i][j] >= 10 && mousePositions[i][j] < 100)
                {
                    outputStrings[i+9].append( "  " );
                }
                else if( mousePositions[i][j] >= 100 )
                {
                    outputStrings[i+9].append( " " );
                }

                outputStrings[i+9].append( toString( mousePositions[i][j] ) );
            }
        }

        for(int i = 0; i < 29; i++)
        {
            cout << "outputting line #" << i << endl;
            outputFile << outputStrings[ i ];
            outputFile << "\n";
        }

        outputFile.close();cout << "finished output" << endl;
    }

    return success;
}

/// ///////////////////////////////
