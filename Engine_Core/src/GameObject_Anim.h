#ifndef GAMEOBJECT_ANIM_H
#define GAMEOBJECT_ANIM_H
#include "MathEngine.h"
#include "Model.h"
#include "GraphicsObject.h"
#include "Time.h"
#include "GameObject.h"
class Skeleton;
//#include "Skeleton.h"

class GameObjectAnim : public GameObject
{
public:
	GameObjectAnim(GraphicsObject  *graphicsObject);

	// Big four
	GameObjectAnim() = delete;
	GameObjectAnim(const GameObjectAnim &) = delete;
	GameObjectAnim & operator = (const GameObjectAnim &) = delete;

	// Added virtual to allow us to have derived objects
	virtual ~GameObjectAnim();

	virtual void Update(Time currentTime) override;
	virtual void Process(Time currentTime) override;
	virtual  void draw() override;
	// Accessors

	// Moved from GameObject	

	void SetIndex(int val);
	void SetBoneOrientation(const Matrix & in_matrix);
	Matrix GetBoneOrientation(void) const;
	void SubmitWorld();

public:
	// Moved from GameObject	

	Matrix		* pLocal;
	Matrix		*pBoneOrientation;
	int         indexBoneArray;			//index of bone in the array.. So it can be mapped 

	Vect *pScale;
	Vect *pPos;
	Vect *pDof;
	Vect *pUp;

	Skeleton *Pskeleton;


};


#endif
