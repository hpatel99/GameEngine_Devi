#include <assert.h>
#include "InputManager.h"


InputManager *InputManager::pInputManager = 0;

void InputManager::Create()
{
	InputManager::privCreate();
}

InputManager::InputManager()
{
	this->pKeyboard = new Keyboard();
	assert(this->pKeyboard);
}

void InputManager::privCreate()
{
	InputManager::pInputManager = new InputManager();
	assert(pInputManager);
}

InputManager::~InputManager()
{
	delete this->pKeyboard;
}

Keyboard *InputManager::GetKeyboard()
{
	InputManager *pMan = InputManager::privInstance();
	return pMan->pKeyboard;
}

Mouse * InputManager::GetMouse()
{
	InputManager *pMan = InputManager::privInstance();
	return pMan->pMouse;
}

InputManager *InputManager::privInstance()
{
	assert(pInputManager);
	return pInputManager;
}

