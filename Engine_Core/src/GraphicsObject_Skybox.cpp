#include "GraphicsObject_Skybox.h"
#include "CameraManager.h"
#include "Model.h"

void GraphicsObject_Skybox::SetState()
{
	glActiveTexture(GL_TEXTURE0);

	// Bind the texture
	GLuint textureID = Texture::Find(this->textName);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);
}

void GraphicsObject_Skybox::SetDataGPU()
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


void GraphicsObject_Skybox::Draw()
{
	glDrawElements(GL_TRIANGLES, (3 * this->GetModel()->numtris), GL_UNSIGNED_INT, 0);
}

void GraphicsObject_Skybox::RestoreState()
{
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);
}

GraphicsObject_Skybox::GraphicsObject_Skybox(Model * model, ShaderObject * pShaderObj, Texture::Name texname, Name inName)
	:GraphicsObject(model, pShaderObj, inName), textName(texname)
{
	assert(model);
	assert(pShaderObj);

}