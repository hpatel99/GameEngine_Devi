#include "GraphicsObject_Texture.h"

#include "TextureNode.h"
#include "Model.h"
#include "Camera.h"
#include "CameraManager.h"


GraphicsObject_Texture::GraphicsObject_Texture(Model * model, ShaderObject * pShaderObj, Texture::Name texname, Name inName)
	:GraphicsObject(model,pShaderObj,inName),textName(texname)
{
	assert(model);
	assert(pShaderObj);
	
}

void GraphicsObject_Texture::SetState()
{
	glActiveTexture(GL_TEXTURE0);

	// Bind the texture
	GLuint textureID = Texture::Find(this->textName);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);
}

void GraphicsObject_Texture::SetDataGPU()
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


void GraphicsObject_Texture::Draw()
{
	glDrawElements(GL_TRIANGLES, (3 * this->GetModel()->numtris), GL_UNSIGNED_INT, 0);
}

void GraphicsObject_Texture::RestoreState()
{
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);
}

void GraphicsObject_Texture::ChangeTexName(Texture::Name iNnEW)
{
	this->textName = iNnEW;
}
