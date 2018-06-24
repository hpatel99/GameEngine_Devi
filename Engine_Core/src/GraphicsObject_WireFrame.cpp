#include "GraphicsObject_WireFrame.h"
#include "ShaderObject.h"
#include "Model.h"
#include "Camera.h"
#include "CameraManager.h"


GraphicsObject_WireFrame::GraphicsObject_WireFrame(Model * model, ShaderObject * pShaderObj,Name inName)
	:GraphicsObject(model,pShaderObj,inName)
{
	assert(model);
	assert(pShaderObj);

}

void GraphicsObject_WireFrame::SetState()
{
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);
}

void GraphicsObject_WireFrame::SetDataGPU()
{// Draw Me: -----------------------------------------
	this->pShaderObj->SetActive();
	// set the vao
	glBindVertexArray(this->GetModel()->vao);

	// Set state
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDisable(GL_CULL_FACE);

	Matrix world = this->GetWorld();

	Matrix view = CameraManger::GetActive()->getViewMatrix();
	Matrix proj = CameraManger::GetActive()->getProjMatrix();
	

	glUniformMatrix4fv(this->pShaderObj->GetLocation("proj_matrix"), 1, GL_FALSE, (float *)&proj);
	glUniformMatrix4fv(this->pShaderObj->GetLocation("view_matrix"), 1, GL_FALSE, (float *)&view);
	glUniformMatrix4fv(this->pShaderObj->GetLocation("world_matrix"), 1, GL_FALSE, (float *)&world);
}

void GraphicsObject_WireFrame::Draw()
{
	glDrawElements(GL_TRIANGLES, (3 * this->GetModel()->numtris), GL_UNSIGNED_INT, 0);
}

void GraphicsObject_WireFrame::RestoreState()
{
	glEnable(GL_CULL_FACE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
