#include "ImportedModel.h"
#include <ChunkHeader.h>

ImportedModel::ImportedModel(const char * const pModelFileName, Model::Name inName)
	:Model(inName)
{
	assert(pModelFileName);
	this->privCreateVAO(pModelFileName);
	this->RenderSphere = true;
}

ImportedModel::ImportedModel(unsigned char * VertBuff,unsigned char * Tribuff, unsigned int vertsize, unsigned int trisize, Model::Name inName)
	:Model(inName)
{
	this->privCreateVAO(VertBuff, Tribuff, vertsize, trisize);
}

ImportedModel::~ImportedModel()
{
}

void ImportedModel::privCreateVAO(const char * const modelfileNAME)		//deprecated Method
{
	assert(modelfileNAME);
	
}   // Deprecatead methdods

void ImportedModel::privCreateVAO(unsigned char * VertBuff,unsigned char * Tribuff, unsigned int vertsize, unsigned int trisize)
{
	Tri_index *TriList = new Tri_index[trisize / 6];
	unsigned short *pconductor = (unsigned short*)Tribuff;
	Vert_xyzuvn *pVerts = (Vert_xyzuvn*)VertBuff;
	for (unsigned int i = 0;i<trisize / 6;i++)
	{
		TriList[i].v0 = *pconductor;
		pconductor++;
		TriList[i].v1 = *pconductor;
		pconductor++;
		TriList[i].v2 = *pconductor;
		pconductor++;

	}
	this->numVerts = (signed)(vertsize / sizeof(Vert_xyzuvn));
	this->numtris = (signed)(trisize / 6);
	//Need stuff below for rittersphere as bounding box:D
	Vect *p_vect = new Vect[(unsigned int)this->numVerts];
	for(int i = 0; i < this->numVerts;i++)
	{
		p_vect[i].set(pVerts[i].x, pVerts[i].y, pVerts[i].z);
	}
	
	RitterSphere(*this->psphere, p_vect, this->numVerts);
	this->psphere->rad *= 2.0;		//ceause sphere is not unit






	// Create a VAO
	glGenVertexArrays(1, &this->vao);
	assert(this->vao != 0);
	glBindVertexArray(this->vao);
	// Create a VBO
	glGenBuffers(2, &this->vbo[0]);
	assert(this->vbo[0] != 0);
	glBindBuffer(GL_ARRAY_BUFFER, this->vbo[0]);

	// load the data to the GPU
	glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)(vertsize), VertBuff, GL_STATIC_DRAW);

	Vert_xyzuvn *ptemp = (Vert_xyzuvn*)VertBuff;	//to find the offset of the data in the array

													// define an array of generic vertex attribute data
													// Vert data is 0
													// todo make a table or enum
	void *offsetVert = (void *)((unsigned int)&ptemp[0].x - (unsigned int)ptemp);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vert_xyzuvn), offsetVert);

	// Enable or disable a generic vertex attribute array
	glEnableVertexAttribArray(0);

	// Texture data is location: 1  (used in vertex shader)
	void *offsetTex = (void *)((unsigned int)&ptemp[0].u - (unsigned int)ptemp);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vert_xyzuvn), offsetTex);
	glEnableVertexAttribArray(1);

	//NormAL data in location 2
	void *offsetNorm = (void *)((unsigned int)&ptemp[0].nx - (unsigned int)ptemp);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vert_xyzuvn), offsetNorm);
	glEnableVertexAttribArray(2);

	/* Bind our 2nd VBO as being the active buffer and storing index ) */
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[1]);

	/* Copy the index data to our buffer */
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, (GLsizeiptr)(trisize * 2), TriList, GL_STATIC_DRAW);


	delete[] TriList;		// freeing memory for list
	delete VertBuff;
	delete Tribuff;
}
