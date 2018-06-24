#include "GraphicsObject_ToonShader.h"
#include "Model.h"

#include "CameraManager.h"

GraphicsObject_ToonShader::GraphicsObject_ToonShader(Model * model, ShaderObject * pShaderObj, Name inName)
	:GraphicsObject(model,pShaderObj,inName)
{
	static const GLubyte toon_tex_data[] =
	{
		0x44, 0x00, 0x00, 0x00,
		0x88, 0x00, 0x00, 0x00,
		0xCC, 0x00, 0x00, 0x00,
		0xFF, 0x00, 0x00, 0x00
	};

	glGenTextures(1, &tex_toon);
	glBindTexture(GL_TEXTURE_1D, tex_toon);
	glTexStorage1D(GL_TEXTURE_1D, 1, GL_RGB8, sizeof(toon_tex_data) / 4);
	glTexSubImage1D(GL_TEXTURE_1D, 0,
		0, sizeof(toon_tex_data) / 4,
		GL_RGBA, GL_UNSIGNED_BYTE,
		toon_tex_data);

	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);

}

void GraphicsObject_ToonShader::SetState()
{
	glActiveTexture(GL_TEXTURE0);

	// Bind the texture
	//GLuint textureID = Texture::Find(this->textName);
	glBindTexture(GL_TEXTURE_1D, tex_toon);

	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);
}

void GraphicsObject_ToonShader::SetDataGPU()
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

void GraphicsObject_ToonShader::Draw()
{
	glDrawElements(GL_TRIANGLES, (3 * this->GetModel()->numtris), GL_UNSIGNED_INT, 0);
}

void GraphicsObject_ToonShader::RestoreState()
{
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);
}
