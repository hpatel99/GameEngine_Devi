#include "ShaderBufferObject.h"


ShaderBufferObject::ShaderBufferObject()
{
	glGenBuffers(1, &this->ID);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, ID);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}

ShaderBufferObject::~ShaderBufferObject()
{
	glDeleteBuffers(1, &ID);
}

void ShaderBufferObject::PushDataToGpu(Desc inDesc_)
{
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, this->ID);
	glBufferData(GL_SHADER_STORAGE_BUFFER, (GLsizeiptr)(inDesc_.numberofElements * inDesc_.StructureSize), inDesc_.pData, GL_STATIC_DRAW); 
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}

void ShaderBufferObject::BindLayout(unsigned int LayoutID_)
{
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, LayoutID_, this->ID);
}

unsigned int ShaderBufferObject::GetID() const
{
	return this->ID;
}

void * ShaderBufferObject::MapData(Access access)
{
	//glBindBuffer(GL_SHADER_STORAGE_BUFFER, ID);
	void *result = glMapNamedBuffer(this->ID, GLenum(access));
	assert(result != nullptr);
	return result;

}

void ShaderBufferObject::UnMapData()
{
	glUnmapNamedBuffer(ID);
}
