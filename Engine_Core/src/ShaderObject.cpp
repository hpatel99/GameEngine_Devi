#include <sb7.h>
#include <math.h>
#include <assert.h>
#include "ShaderObject.h"
#include "Game.h"
#include "File.h"


ShaderObject::ShaderObject( ShaderObject::Name inname, const char * const shaderBaseFileName, ShaderType intype_)
	:name(inname)
{
	assert(shaderBaseFileName);
	this->privCreateShader(this->programObject, shaderBaseFileName,intype_);
	this->myType = intype_;
}

void ShaderObject::SetActive()
{
	glUseProgram(this->programObject);
}

GLint ShaderObject::GetLocation(const char * uniformName)
{
	assert(uniformName != 0);
	GLint loc = glGetUniformLocation(this->programObject, uniformName);
	assert(loc != -1);

	return loc;
}

void ShaderObject::Dispatch(unsigned int x, unsigned int y, unsigned int z)
{
	assert(this->myType == Compute);
	glDispatchCompute((unsigned int)x, (unsigned int)y, (unsigned int)z);
}

bool ShaderObject::privShaderLoadAndCompile(GLuint & ShaderObj, const char * const fileName, GLenum shaderType)
{
	File::Handle fh;
	File::Error  ferror;

	ferror = File::Open(fh, fileName, File::Mode::READ);
	assert(ferror == File::Error::SUCCESS);

	ferror = File::Seek(fh, File::Location::END, 0);
	assert(ferror == File::Error::SUCCESS);

	unsigned int numBytesInFile;
	ferror = File::Tell(fh, numBytesInFile);
	assert(ferror == File::Error::SUCCESS);

	ferror = File::Seek(fh, File::Location::BEGIN, 0);
	assert(ferror == File::Error::SUCCESS);

	char *data = new char[numBytesInFile + 1];
	assert(data != 0);

	ferror = File::Read(fh, data, numBytesInFile);
	assert(ferror == File::Error::SUCCESS);

	// null termination character
	data[numBytesInFile] = 0;

	ferror = File::Close(fh);
	assert(ferror == File::Error::SUCCESS);

	// create a shader object
	ShaderObj = glCreateShader(shaderType);
	assert(ShaderObj != 0);

	//load shader
	glShaderSource(ShaderObj, 1, &data, 0);
	delete[] data;

	glCompileShader(ShaderObj);

	// check for errors
	GLint status = 0;
	glGetShaderiv(ShaderObj, GL_COMPILE_STATUS, &status);

	// found one
	if (!status)
	{
		char buffer[4096];
		glGetShaderInfoLog(ShaderObj, 4096, NULL, buffer);

		printf("Error(ShaderLoadNCompile.cpp) %s: %s\n", fileName, buffer);

		glDeleteShader(ShaderObj);

		assert(false);
		return false;
	}
	else
	{
		return true;
	}
}

bool ShaderObject::privCreateShader(GLuint & ProgramObject, const char * const ShaderBaseFileName,ShaderType intype_)
{
	if (intype_ == Graphics)
	{
		bool status;
		char nameBuff[128];

		assert(ShaderBaseFileName != 0);

		strcpy_s(nameBuff, 128, ShaderBaseFileName);
		strcat_s(nameBuff, 128, ".fs.glsl");

		GLuint fs;
		status = privShaderLoadAndCompile(fs, nameBuff, GL_FRAGMENT_SHADER);
		assert(status == true);

		strcpy_s(nameBuff, 128, ShaderBaseFileName);
		strcat_s(nameBuff, 128, ".vs.glsl");

		GLuint vs;
		status = privShaderLoadAndCompile(vs, nameBuff, GL_VERTEX_SHADER);
		assert(status == true);

		// Creates an empty program object
		ProgramObject = glCreateProgram();

		//Attaches a shader object to a program object
		glAttachShader(ProgramObject, vs);
		glAttachShader(ProgramObject, fs);

		
	}
	else if(intype_== Compute)
	{
		bool status;
		char nameBuff[128];

		assert(ShaderBaseFileName != 0);

		strcpy_s(nameBuff, 128, ShaderBaseFileName);
		strcat_s(nameBuff, 128, ".comp.glsl");
		GLuint cs;
		status = privShaderLoadAndCompile(cs, nameBuff, GL_COMPUTE_SHADER);
		assert(status == true);
		// Creates an empty program object
		ProgramObject = glCreateProgram();
		//Attaches a shader object to a program object
		glAttachShader(ProgramObject, cs);
		
	}
	else
	{
		assert(false);
	}
	// Links a program object
	glLinkProgram(ProgramObject);

	return true;
}
