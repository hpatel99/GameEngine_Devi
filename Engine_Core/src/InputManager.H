#ifndef INPUT_MAN_H
#define INPUT_MAN_H

#include "Keyboard.h"
#include "Mouse.h"

class InputManager
{
public:
	static void Create();
	static Keyboard *GetKeyboard();
	static Mouse *GetMouse();
	~InputManager();

private:
	static InputManager *privInstance();
	static void privCreate();
	InputManager();

	// Data
	static InputManager *pInputManager;
	Keyboard		*pKeyboard;
	Mouse			*pMouse;

};
#endif