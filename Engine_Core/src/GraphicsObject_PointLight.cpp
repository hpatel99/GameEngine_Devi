#include "GraphicsObject_PointLight.h"
#include "Model.h"
#include "Camera.h"
#include "CameraManager.h"



GraphicsObject_PointLight::GraphicsObject_PointLight(Model * model, ShaderObject * pShaderObj, Texture::Name name, Vect & LightColor, Vect & LightPos, Name inname)
	:GraphicsObject(model,pShaderObj,inname),textName(name)
{
	this->pLightColor = new Vect(LightColor);
	this->pLightPos = new Vect(LightPos);

}

GraphicsObject_PointLight::~GraphicsObject_PointLight()
{
	delete this->pLightColor;
	delete this->pLightPos;
}

void GraphicsObject_PointLight::SetState()
{
	glActiveTexture(GL_TEXTURE0);

	// Bind the texture
	GLuint textureID = Texture::Find(this->textName);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glEnable(GL_CULL_FACE);
	if(this->pModel->isCCW)
	{
		glFrontFace(GL_CCW);
	}else
	{
		glFrontFace(GL_CW);
	}
	
}

void GraphicsObject_PointLight::SetDataGPU()
{
	// use this shader
	this->pShaderObj->SetActive();

	// set the vao
	glBindVertexArray(this->GetModel()->vao);

	Matrix world = this->GetWorld();
	Matrix view = CameraManger::GetActive()->getViewMatrix();		//replace stuff here to get different camera stuff
	Matrix proj = CameraManger::GetActive()->getProjMatrix();

	glUniformMatrix4fv(this->pShaderObj->GetLocation("proj_matrix"), 1, GL_FALSE, (float *)&proj);
	glUniformMatrix4fv(this->pShaderObj->GetLocation("view_matrix"), 1, GL_FALSE, (float *)&view);
	glUniformMatrix4fv(this->pShaderObj->GetLocation("world_matrix"), 1, GL_FALSE, (float *)&world);

	Vect light = *this->pLightPos;
	Vect color = *this->pLightColor;
	glUniform3fv(this->pShaderObj->GetLocation("vLightPos"), 1, (float *)&light);
	glUniform4fv(this->pShaderObj->GetLocation("vColor"), 1, (float *)&color);
}

void GraphicsObject_PointLight::Draw()
{
	//call for drawing the triangles
	glDrawElements(GL_TRIANGLES, 3 * this->GetModel()->numtris, GL_UNSIGNED_INT, nullptr);
}

void GraphicsObject_PointLight::RestoreState()
{
	//totally not nesseacry for this state but safe gaaurd;
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);
}
