#ifndef GAME_H
#define GAME_H

#include "Engine.h"

#include <sb7.h>
#include <math.h>

#include <vmath.h>
// ToDo get rid of the projection, move to the camera

#include "MathEngine.h"
#include "Timer.h"

class Game : public Engine
{
public:
	// constructor
	Game(const char* windowName, const int Width, const int Height);
	~Game() = default;
	Game(const Game &) = delete;
	Game &operator =(const Game&) = delete;

    void Initialize();
    virtual void LoadContent();
	virtual void Update(float currentTime);
    virtual void Draw();
    virtual void UnLoadContent();
	virtual void ClearBufferFunc();

   

public:
	Timer globalTimer;
};

#endif
