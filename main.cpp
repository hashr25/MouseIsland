///Included Libraries and Headers
#include "includes.h"

///Forward Declarations of main's functions
bool initSDL();
SDL_Surface* loadSurface(std::string);
bool loadMedia();
bool closeSDL();


///Constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

///Initialize SDL
SDL_Window* gWindow = NULL;
SDL_Surface* gSurface = NULL;
SDL_Surface* tileSurfaces[ TILE_TOTAL ];


int main(int argc, char* args[])
{
    if( !initSDL() )
    {
        printf( "Failed to initialize SDL. " );
    }
    else
    {
        if( !loadMedia() )
        {
            printf( "Failed to load all media. " );
        }
        else
        {
            bool quit = false;


        }
    }

    return 0;
}


bool initSDL()
{
    //Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Create window
		gWindow = SDL_CreateWindow( "Mouse Island", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Get window surface
			gSurface = SDL_GetWindowSurface( gWindow );
		}
	}

	return success;
}

SDL_Surface* loadSurface(std::string path)
{
    //Load image at specified path
	SDL_Surface* loadedSurface = SDL_LoadBMP( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
	}

	return loadedSurface;
}

bool loadMedia()
{
    //Loading success flag
	bool success = true;

	//Load LAND surface
	tileSurfaces[ LAND ] = loadSurface( "land.bmp" );
	if( tileSurfaces[ LAND ] == NULL )
	{
		printf( "Failed to load LAND image!\n" );
		success = false;
	}

	//Load WATER surface
	tileSurfaces[ WATER ] = loadSurface( "water.bmp" );
	if( tileSurfaces[ WATER ] == NULL )
	{
		printf( "Failed to load WATER image!\n" );
		success = false;
	}

	//Load BRIDGE surface
	tileSurfaces[ BRIDGE ] = loadSurface( "bridge.bmp" );
	if( tileSurfaces[ BRIDGE ] == NULL )
	{
		printf( "Failed to load BRIDGE image!\n" );
		success = false;
	}

	//Load MOUSE surface
	tileSurfaces[ MOUSE ] = loadSurface( "mouse.bmp" );
	if( tileSurfaces[ MOUSE ] == NULL )
	{
		printf( "Failed to load MOUSE image!\n" );
		success = false;
	}

	//Load CAT surface
	tileSurfaces[ CAT ] = loadSurface( "cat.bmp" );
	if( tileSurfaces[ CAT ] == NULL )
	{
		printf( "Failed to load CAT image!\n" );
		success = false;
	}

	//Load MOUSE_HOLE surface
	tileSurfaces[ MOUSE_HOLE ] = loadSurface( "mouseHole.bmp" );
	if( tileSurfaces[ MOUSE_HOLE ] == NULL )
	{
		printf( "Failed to load MOUSE_HOLE image!\n" );
		success = false;
	}

	//Load FOOD surface
	tileSurfaces[ FOOD ] = loadSurface( "food.bmp" );
	if( tileSurfaces[ FOOD ] == NULL )
	{
		printf( "Failed to load FOOD image!\n" );
		success = false;
	}

	return success;
}

bool closeSDL()
{
    //Deallocate surfaces
	for( int i = 0; i < TILE_TOTAL; ++i )
	{
		SDL_FreeSurface( tileSurfaces[ i ] );
		tileSurfaces[ i ] = NULL;
	}
    SDL_FreeSurface( gSurface );
    gSurface = NULL;

	//Destroy window
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}
