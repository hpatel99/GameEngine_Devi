#include "Model.h"

Model::Model()
	:numVerts(0),
	numtris(0),
	vao(0)
{
	this->vbo[0] = 0;
	this->vbo[1] = 0;
}

Model::Model(Name inname): numVerts(0),
	numtris(0),
	vao(0),
RenderSphere(false),
isCCW(false)
{
	this->name = inname;
	this->vbo[0] = 0;
	this->vbo[1] = 0;
	this->psphere = new Sphere();
}

Model::~Model()
{

}

bool Model::IsRenderSphere()const 
{
	return this->RenderSphere;
}

bool Model::IsCWW()
{
	return this->isCCW;
}

void Model::setIsCWW(bool inbool)
{
	this->isCCW = inbool;
}

void Model::setRenderSphere(bool inbool)
{
	this->RenderSphere = inbool;
}
