/********************************************************************************************
*                               Mouse Island Simulation                                     *
*                                 Author: Randy Hash                                        *
*                      A cat and a mouse are on an island. The                              *
*                      mouse tries to escape and eat his cheese.                            *
*                      The cat tries to eat the mouse first.                                *
*                                      The End.                                             *
********************************************************************************************/

///Included Libraries and Headers
#include "GameConfig.h"
#include "GameController.h"

/// //////////////////////////////////////////////////////////////////////////////////
/// Game Loop

int main(int argc, char* args[])
{
    GameController mouseIsland;
    mouseIsland.runGame();
    return 0;
}

/// //////////////////////////////////////////////////////////////////////////////////
