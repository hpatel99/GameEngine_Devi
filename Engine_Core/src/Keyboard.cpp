#include <assert.h>

#include "sb7.h"
#include "Game.h"

#include "Keyboard.h"

extern Game *pGame;

Keyboard::Keyboard()
{

}

// Use this to read keyboard
bool Keyboard::GetKeyState(AZUL_KEY key)
{
	bool value;


	if (pGame->GetKey(key) == GLFW_PRESS)
	{
		value = true;
	}
	else
	{
		value = false;
	}

	return value;
}
