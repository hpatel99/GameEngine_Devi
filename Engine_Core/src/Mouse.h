#ifndef  MOUSE_H
#define MOUSE_H
enum AZUL_MOUSE
{
	BUTTON_LEFT = 0,
	BUTTON_RIGHT = 1,
	BUTTON_MIDDLE = 2
};

class Mouse
{
public:
	Mouse();
	~Mouse();

	bool GetKeyState(AZUL_MOUSE button);
	
	void GetCursor(float &xPos, float &yPos);


private:

};


#endif // ! MOUSE_H
