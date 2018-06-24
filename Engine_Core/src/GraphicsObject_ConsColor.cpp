#include "GraphicsObject_ConsColor.h"
#include "Model.h"

#include "CameraManager.h"

//extern Camera *pCam;

GraphicsObject_ConstColor::GraphicsObject_ConstColor(Model * model, ShaderObject * pShaderObj, Vect & LightColor, Vect & LightPos, Name inName)
	:GraphicsObject(model,pShaderObj,inName)
{
	this->pLightColor = new Vect(LightColor);
	this->pLightPos = new Vect(LightPos);
}

GraphicsObject_ConstColor::~GraphicsObject_ConstColor()
{
	delete this->pLightColor;
	delete this->pLightPos;
}

void GraphicsObject_ConstColor::SetState()
{
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);
}

void GraphicsObject_ConstColor::SetDataGPU()
{
	glBindVertexArray(this->GetModel()->vao);

	// use this shader
	this->pShaderObj->SetActive();

	Matrix world = this->GetWorld();
	Matrix view = CameraManger::GetActive()->getViewMatrix();
	Matrix proj = CameraManger::GetActive()->getProjMatrix();

	glUniformMatrix4fv(this->pShaderObj->GetLocation("proj_matrix"), 1, GL_FALSE, (float *)&proj);
	glUniformMatrix4fv(this->pShaderObj->GetLocation("view_matrix"), 1, GL_FALSE, (float *)&view);
	glUniformMatrix4fv(this->pShaderObj->GetLocation("world_matrix"), 1, GL_FALSE, (float *)&world);

	Vect light = *this->pLightPos;
	Vect color = *this->pLightColor;
	glUniform3fv(this->pShaderObj->GetLocation("vLightPos"), 1, (float *)&light);
	glUniform4fv(this->pShaderObj->GetLocation("vColor"), 1, (float *)&color);

}

void GraphicsObject_ConstColor::Draw()
{
	glDrawElements(GL_TRIANGLES, 3 * this->GetModel()->numtris, GL_UNSIGNED_INT, 0);
}

void GraphicsObject_ConstColor::RestoreState()
{
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);
}
