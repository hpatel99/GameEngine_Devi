#ifndef MODEL_H
#define MODEL_H
#include <sb7.h>
#include "PCSNode.h"
#include "BoundingSphere.h"
#include "ModelFileHeader.h"
#include "File.h"
#include "Vect.h"

struct Vert_xyzuvn		//moved it here so all model can inherit
{
	float x;
	float y;
	float z;
	float u;
	float v;
	float nx;
	float ny;
	float nz;

};

struct Tri_index
{
unsigned int v0;
unsigned int v1;
unsigned int v2;
};
class Model :public PCSNode
{

public:
	//publicdata member
	enum Name
	{
		Cube,
		Pyramid,
		Null_Object,
		SKYBOX,
		Diamond,
		LOG,
		SPACE_FRIGATE,
		WARBEAR,
		BUGGY,
		ASTROBOY,
		GETHWARRIOR,
		SPHERE,
		CameraModel,
		SkinningModel,
		TEDDY_SKINNING_MODEL,
		HUMANOID_SKINNING_MODEL,
		Not_Initialzed
	};
	//Big 4
	Model();
	Model( Model &) = delete;
	Model & operator=(Model &) = delete;
	Model(Name inname = Name::Not_Initialzed);
	// Needs to be virtual --> why?
	virtual ~Model();

	//getter setter of the methods
	bool IsRenderSphere()const ;
	bool IsCWW();
	void setIsCWW(bool inbool);
	void setRenderSphere(bool inbool);

protected:
	virtual void privCreateVAO(const char * const modelFileName) = 0;

public :

	int numVerts;
	int numtris;

	GLuint vao;
	GLuint vbo[4];
	
	bool RenderSphere;		//bool stating to display the bounding sphere or not.
	bool isCCW;				// to store What kind of winding are this?
	char pad[2];
	Name name;
	//Radius and Center for sphere
	Sphere *psphere;
	
};



#endif // !MODEL_H
