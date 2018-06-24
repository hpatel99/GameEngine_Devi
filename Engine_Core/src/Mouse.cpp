#include "Mouse.h"
#include "sb7.h"
#include "Game.h"
#include <assert.h>

extern Game *pGame;
Mouse::Mouse()
{
	//Do nothing no varaibles
}

bool Mouse::GetKeyState(AZUL_MOUSE button)
{
	bool result;
	if (pGame->GetMouseButton(button) == GLFW_PRESS)
	{
		result = true;

	}
	else
	{
		result = false;
	}
	return result;
}

void Mouse::GetCursor(float & xPos, float & yPos)
{
	pGame->GetCursorPos(xPos, yPos);
}

