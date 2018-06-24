#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "MathEngine.h"
#include "GraphicsObject.h"
#include "PCSNode.h"
#include "Time.h"


class GameObject : public PCSNode
{
public:
	enum Name
	{
		NULL_SHADER,
		SINGLECOLOR_WIREFRAME,
		Simple_Color,
		POINTLIGHT_TEXTURE,
		CONST_COLOR,
		TOON_SHADER,
		SKYBOX,
		Texture,

	};
public:
	GameObject(GraphicsObject *graphicobject);
	GameObject()=delete;
	GameObject(const GameObject&) = delete;
	GameObject &operator= (GameObject&) = delete;
	virtual ~GameObject();

	virtual void Update(Time t) ;
	virtual void draw();
	virtual void Process(Time t);

	Matrix *getWorld();
	GraphicsObject* GetGraphicsObject();
	
	void setWorld(Matrix *world);
	//void setPos(const Vect &pos);
	//void setScale(const Vect &scale);

	//void rotate(Rot3AxisType, float angle1, float angle2, float angle3);

	//public data
	float  deltaRot;
	//GameObject::Name name;
public :
	
protected:
	Matrix *pWorld;
	GraphicsObject *pGraphicsObject;
private:
	
	
	
	
};


#endif