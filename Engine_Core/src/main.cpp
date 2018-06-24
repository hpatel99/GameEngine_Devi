#include "Game.h"

Game *pGame = 0;

int CALLBACK WinMain(HINSTANCE , HINSTANCE,  LPSTR , int )                  
{        

	pGame = new Game("Monkey", 800, 600);
    pGame->run();                                  
                                  
    return 0;                                       
}

// ---  End of File ---------------
