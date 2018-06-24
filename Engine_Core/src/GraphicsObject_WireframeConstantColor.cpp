#include <assert.h>

#include "Model.h"
#include "GraphicsObject_WireframeConstantColor.h"
#include "ShaderObject.h"
#include "Camera.h"
#include "CameraManager.h"


GraphicsObject_WireframeConstantColor::GraphicsObject_WireframeConstantColor(Model *model, ShaderObject *pShaderObj, Vect &wireColor, Name InName)
: GraphicsObject(model, pShaderObj)
{
	assert(model);
	assert(pShaderObj);
	this->pWireColor = new Vect(wireColor);
	this->name = InName;
}


void GraphicsObject_WireframeConstantColor::SetState()
{	
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CW);
}

void GraphicsObject_WireframeConstantColor::SetDataGPU()
{	     
	// Draw Me: -----------------------------------------

	// set the vao
	glBindVertexArray(this->GetModel()->vao);
	
		// Set state
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDisable(GL_CULL_FACE);

	// use this shader
	this->pShaderObj->SetActive();

	Matrix world = this->GetWorld();
	Matrix view = CameraManger::GetActive()->getViewMatrix();
	Matrix proj = CameraManger::GetActive()->getProjMatrix();

	glUniformMatrix4fv(this->pShaderObj->GetLocation("proj_matrix"), 1, GL_FALSE, (float *)&proj);
	glUniformMatrix4fv(this->pShaderObj->GetLocation("view_matrix"), 1, GL_FALSE, (float *)&view);
	glUniformMatrix4fv(this->pShaderObj->GetLocation("world_matrix"), 1, GL_FALSE, (float *)&world);

	glUniform4fv(this->pShaderObj->GetLocation("wire_color"), 1, (float *)this->pWireColor);
}

void GraphicsObject_WireframeConstantColor::Draw( )
{	     
	//The starting point of the IBO
	glDrawElements(GL_TRIANGLES, 3 * this->GetModel()->numtris, GL_UNSIGNED_INT, 0);
}

void GraphicsObject_WireframeConstantColor::RestoreState()
{	     
	// Restore state
	glEnable(GL_CULL_FACE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void GraphicsObject_WireframeConstantColor::setcolor(Vect * incolor)
{
	this->pWireColor = incolor;
}
