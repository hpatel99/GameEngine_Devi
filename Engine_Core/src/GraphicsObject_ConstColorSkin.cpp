
#include "Model.h"

#include "CameraManager.h"
#include "GraphicsObject_ConstColorSkin.h"

//extern Camera *pCam;

GraphicsObject_ConstColorSkin::GraphicsObject_ConstColorSkin(Model * model, ShaderObject * pShaderObj, Skeleton *pSkeleton_, Animation* pinAnim,Name inName)
	:GraphicsObject(model,pShaderObj,inName)
{
	this->p_skeleton = pSkeleton_;
	this->p_anim = pinAnim;
}

GraphicsObject_ConstColorSkin::~GraphicsObject_ConstColorSkin()
{
	
}

void GraphicsObject_ConstColorSkin::SetState()
{
	glEnable(GL_CULL_FACE);
	if (this->pModel->isCCW)
	{
		glFrontFace(GL_CCW);
	}
	else
	{
		glFrontFace(GL_CW);
	}
}

void GraphicsObject_ConstColorSkin::SetDataGPU()
{
	glBindVertexArray(this->GetModel()->vao);

	// use this shader
	this->pShaderObj->SetActive();

	Matrix world = this->GetWorld();
	Matrix view = CameraManger::GetActive()->getViewMatrix();
	Matrix proj = CameraManger::GetActive()->getProjMatrix();

	glUniformMatrix4fv(this->pShaderObj->GetLocation("proj_matrix"), 1, GL_FALSE, (float *)&proj);
	glUniformMatrix4fv(this->pShaderObj->GetLocation("view_matrix"), 1, GL_FALSE, (float *)&view);
	//glUniformMatrix4fv(this->pShaderObj->GetLocation("world_matrix"), 1, GL_FALSE, (float *)&world);
	p_anim->pBit_ssbo->BindLayout(0);
	//glUniformMatrix4fv(this->pShaderObj->GetLocation("bit"), 100, GL_FALSE, (float*)p_skeleton->pWorldOfBones);	//sending world matrix of each bbones
	//glUniformMatrix4fv(this->pShaderObj->GetLocation("inv"), 100, GL_FALSE, (float*)p_skeleton->pPoseInverse);	//sending matrix of boind pose inbverse

	//glUniform3fv(this->pShaderObj->GetLocation("vLightPos"), 1, (float *)&light);
	//glUniform4fv(this->pShaderObj->GetLocation("vColor"), 1, (float *)&color);

}

void GraphicsObject_ConstColorSkin::Draw()
{
	glDrawElements(GL_TRIANGLES, 3 * this->GetModel()->numtris, GL_UNSIGNED_INT, 0);
}

void GraphicsObject_ConstColorSkin::RestoreState()
{
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);
}
