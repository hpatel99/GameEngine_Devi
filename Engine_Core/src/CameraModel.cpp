#include <sb7.h>
#include <assert.h>

#include "CameraModel.h"
#include "CameraManager.h"
#include "Camera.h"


void CameraModel::update()
{
	this->privCreateVAO(0);
}

void CameraModel::privCreateVAO( const char * const modelFileName )
{

#define TRILIST_NUM_TRIANGLES (sizeof(triList)/sizeof(Tri_index))
#define SPHERE_DATA_NUM_VERTS (sizeof(pVerts)/sizeof(Vert_xyzuvn))

Vert_xyzuvn pVerts[9];
Tri_index triList[8];

pVerts[0].x = -0.000000f;
pVerts[0].y = 0.000000f;
pVerts[0].z = 0.500000f;
pVerts[0].nx = 0.000000f;
pVerts[0].ny = 0.000000f;
pVerts[0].nz = 0.000000f;
pVerts[0].u = 0.000000f;
pVerts[0].v = 0.000000f;


triList[0].v0 = 0;
triList[0].v1 = 1;
triList[0].v2 = 2;

triList[1].v0 = 0;
triList[1].v1 = 2;
triList[1].v2 = 3;

triList[2].v0 = 0;
triList[2].v1 = 3;
triList[2].v2 = 4;

triList[3].v0 = 0;
triList[3].v1 = 4;
triList[3].v2 = 1;

// far
triList[4].v0 = 1;
triList[4].v1 = 2;
triList[4].v2 = 3;

// far
triList[5].v0 = 3;
triList[5].v1 = 4;
triList[5].v2 = 1;

// near
triList[6].v0 = 5;
triList[6].v1 = 6;
triList[6].v2 = 7;

// near
triList[7].v0 = 7;
triList[7].v1 = 8;
triList[7].v2 = 5;

Vect vTmp;

Camera *pCam =(Camera*) CameraManger::pCameraManager->pFrustrumRender;
pCam->updateCamera();

pCam->getPos(vTmp);
pVerts[0].x = vTmp[x];
pVerts[0].y = vTmp[y];
pVerts[0].z = vTmp[z];
pVerts[0].nx = 0.000000f;
pVerts[0].ny = 0.000000f;
pVerts[0].nz = 0.000000f;
pVerts[0].u = 0.000000f;
pVerts[0].v = 0.000000f;

pCam->getFarTopRight(vTmp);
pVerts[1].x = vTmp[x];
pVerts[1].y = vTmp[y];
pVerts[1].z = vTmp[z];
pVerts[1].nx = 0.000000f;
pVerts[1].ny = 0.000000f;
pVerts[1].nz = 0.000000f;
pVerts[1].u = 0.000000f;
pVerts[1].v = 0.000000f;

pCam->getFarTopLeft(vTmp);
pVerts[2].x = vTmp[x];
pVerts[2].y = vTmp[y];
pVerts[2].z = vTmp[z];
pVerts[2].nx = 0.000000f;
pVerts[2].ny = 0.000000f;
pVerts[2].nz = 0.000000f;
pVerts[2].u = 0.000000f;
pVerts[2].v = 0.000000f;

pCam->getFarBottomLeft(vTmp);
pVerts[3].x = vTmp[x];
pVerts[3].y = vTmp[y];
pVerts[3].z = vTmp[z];
pVerts[3].nx = 0.000000f;
pVerts[3].ny = 0.000000f;
pVerts[3].nz = 0.000000f;
pVerts[3].u = 0.000000f;
pVerts[3].v = 0.000000f;

pCam->getFarBottomRight(vTmp);
pVerts[4].x = vTmp[x];
pVerts[4].y = vTmp[y];
pVerts[4].z = vTmp[z];
pVerts[4].nx = 0.000000f;
pVerts[4].ny = 0.000000f;
pVerts[4].nz = 0.000000f;
pVerts[4].u = 0.000000f;
pVerts[4].v = 0.000000f;

pCam->getNearTopRight(vTmp);
pVerts[5].x = vTmp[x];
pVerts[5].y = vTmp[y];
pVerts[5].z = vTmp[z];
pVerts[5].nx = 0.000000f;
pVerts[5].ny = 0.000000f;
pVerts[5].nz = 0.000000f;
pVerts[5].u = 0.000000f;
pVerts[5].v = 0.000000f;

pCam->getNearTopLeft(vTmp);
pVerts[6].x = vTmp[x];
pVerts[6].y = vTmp[y];
pVerts[6].z = vTmp[z];
pVerts[6].nx = 0.000000f;
pVerts[6].ny = 0.000000f;
pVerts[6].nz = 0.000000f;
pVerts[6].u = 0.000000f;
pVerts[6].v = 0.000000f;

pCam->getNearBottomLeft(vTmp);
pVerts[7].x = vTmp[x];
pVerts[7].y = vTmp[y];
pVerts[7].z = vTmp[z];
pVerts[7].nx = 0.000000f;
pVerts[7].ny = 0.000000f;
pVerts[7].nz = 0.000000f;
pVerts[7].u = 0.000000f;
pVerts[7].v = 0.000000f;

pCam->getNearBottomRight(vTmp);
pVerts[8].x = vTmp[x];
pVerts[8].y = vTmp[y];
pVerts[8].z = vTmp[z];
pVerts[8].nx = 0.000000f;
pVerts[8].ny = 0.000000f;
pVerts[8].nz = 0.000000f;
pVerts[8].u = 0.000000f;
pVerts[8].v = 0.000000f;

	// future proofing it for a file
	UNUSED_VAR(modelFileName);

	this->numVerts = SPHERE_DATA_NUM_VERTS;
	this->numtris = TRILIST_NUM_TRIANGLES;
	//Clear old memory memory 
	if(this->vao != 0)
	{
		glDeleteVertexArrays(1, &this->vao);
		glDeleteBuffers(2, &this->vbo[0]);
	}
	// Create a VAO
	glGenVertexArrays(1, &this->vao);
	assert( this->vao != 0 );
	glBindVertexArray(this->vao);

	// Create a VBO
    glGenBuffers(2, &this->vbo[0]);
	assert( this->vbo[0] != 0 );

	
    // Load the combined data: ---------------------------------------------------------

		glBindBuffer(GL_ARRAY_BUFFER, this->vbo[0]);

		// load the data to the GPU
		glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)(sizeof(Vert_xyzuvn) * this->numVerts), pVerts, GL_STATIC_DRAW);

		// Vertext data in location 0
		void *offsetVert = (void *)((unsigned int)&pVerts[0].x - (unsigned int)pVerts);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vert_xyzuvn), offsetVert);
		glEnableVertexAttribArray(0);

		// Texture data in location 1
		void *offsetTex = (void *)((unsigned int)&pVerts[0].u - (unsigned int)pVerts);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vert_xyzuvn), offsetTex);
		glEnableVertexAttribArray(1);

		// Normal data in location 2
		void *offsetNorm = (void *)((unsigned int)&pVerts[0].nx - (unsigned int)pVerts);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vert_xyzuvn), offsetNorm);
		glEnableVertexAttribArray(2);


	// Load the index data: ---------------------------------------------------------

		// Bind our 2nd VBO as being the active buffer and storing index )
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[1]);

		// Copy the index data to our buffer 
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, (GLsizeiptr)(sizeof(Tri_index) * this->numtris), triList, GL_STATIC_DRAW);

}


CameraModel::CameraModel( const char * const modelFileName )
	: Model(Model::Name::CameraModel)
{
	this->privCreateVAO( modelFileName );
}

CameraModel::~CameraModel()
{
	// remove anything dynamic here
}