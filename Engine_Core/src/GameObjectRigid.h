#ifndef GAME_OBJECT_RIGID_H
#define GAME_OBJECT_RIGID_H

#include "GameObject.h"
#include "MathEngine.h"
#include "Model.h"
#include "GraphicsObject.h"
#include "PCSNode.h"
#include "Time.h"

class GameObjectRigid : public GameObject
{
public:
	GameObjectRigid(GraphicsObject  *graphicsObject);	
	
	// Big Four
	GameObjectRigid() = delete;
	GameObjectRigid(GameObjectRigid &) = delete;
	GameObjectRigid & operator = (const GameObjectRigid &) = delete;
	virtual ~GameObjectRigid() override;

	virtual void Update(Time currentTime ) override;
	void setScale(const Vect &invect);
	void setPos(const Vect &pos);
	void GameObjectRigid::rotate(Rot3AxisType intype, const  float angle1, const float angle2, const  float angle3);

	Matrix &GetWorld();

public:
	Vect *pScale;
	Vect *pPos;
	float rotX ;
	float rotY ;
	float rotZ ;


};

#endif