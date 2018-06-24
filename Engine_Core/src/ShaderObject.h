#ifndef SHADER_OBJ_H
#define SHADER_OBJ_H
#include <sb7.h>
#include "PCSNode.h"


class ShaderObject :public  PCSNode
{
public:

	enum Name
	{	NULL_SHADER,
		SINGLECOLOR_WIREFRAME,
		Simple_Color,
		POINTLIGHT_TEXTURE,
		CONST_COLOR,
		TOON_SHADER,
		SKYBOX,
		Texture,
		SKINNING,
		GPU_SKINNIG,
		COMP_Interpolate,
		COMP_localtoworld,
		COMP_TEST

	};
	enum ShaderType
	{
		Graphics,
		Compute
	};

public:
	ShaderObject(Name name, const char * const shaderBaseFileName, ShaderType intype = Graphics);

	ShaderObject() = delete;
	ShaderObject(const ShaderObject &) = delete;
	ShaderObject &operator = (ShaderObject &) = delete;
	~ShaderObject() = default;




	void SetActive();
	GLint GetLocation(const char * uniformName);
	void Dispatch(unsigned int x, unsigned int y, unsigned int z);

private:
	bool privShaderLoadAndCompile(GLuint &ShaderObj, const char*const fileName, GLenum shaderType);
	bool privCreateShader(GLuint &ProgramObject, const char * const ShaderBaseFileName, ShaderType intype = Graphics);

public:
	//Data Members
	Name name;
	GLuint programObject;
	ShaderType myType;
};



#endif // !SHADER_OBJ_H
