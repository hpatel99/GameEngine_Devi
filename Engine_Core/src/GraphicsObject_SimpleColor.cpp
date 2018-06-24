#include "GraphicsObject_SimpleColor.h"
#include "MathEngine.h"
#include "Model.h"
#include <assert.h>
#include "Camera.h"
#include "CameraManager.h"



GraphicsObject_SimpleColor::GraphicsObject_SimpleColor(Model * model, ShaderObject * pShaderObj,Name inName)
	:GraphicsObject(model,pShaderObj,inName)
{
	assert(model);
	assert(pShaderObj);
}



void GraphicsObject_SimpleColor::SetState()
{
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);
}

void GraphicsObject_SimpleColor::SetDataGPU()
{
	// use this shader
	this->pShaderObj->SetActive();

	// set the vao
	glBindVertexArray(this->GetModel()->vao);


	Matrix world = this->GetWorld();
	Matrix view = CameraManger::GetActive()->getViewMatrix();
	Matrix proj = CameraManger::GetActive()->getProjMatrix();

	glUniformMatrix4fv(this->pShaderObj->GetLocation("proj_matrix"), 1, GL_FALSE, (float *)&proj);
	glUniformMatrix4fv(this->pShaderObj->GetLocation("view_matrix"), 1, GL_FALSE, (float *)&view);
	glUniformMatrix4fv(this->pShaderObj->GetLocation("world_matrix"), 1, GL_FALSE, (float *)&world);
}

void GraphicsObject_SimpleColor::Draw()
{
	glDrawElements(GL_TRIANGLES,(3 * this->GetModel()->numtris),GL_UNSIGNED_INT,0);
}

void GraphicsObject_SimpleColor::RestoreState()
{
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);
}
