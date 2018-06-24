#include "Space_Frigate.h"
#include "ChunkHeader.h"
#include "eat.h"

SpaceModel::SpaceModel(const char * const pModelFileName)
	:Model(Model::Name::SPACE_FRIGATE)
{
	assert(pModelFileName);
	this->privCreateVAO(pModelFileName);

}

SpaceModel::~SpaceModel()
{
	
}

void SpaceModel::privCreateVAO(const char * const modelfileNAME)
{
	
	assert(modelfileNAME);
	unsigned char *vertbuff;
	unsigned int vertsize;
	unsigned char *tribuff;
	unsigned int trisize;
	eat(modelfileNAME, VERTS_TYPE, "Space_Frigate_Verts", vertbuff, vertsize);
	eat(modelfileNAME, ChunkType::TRILIST, "Frigate_TriList", tribuff, trisize);

	//eat has shorts need int	
	Tri_index *TriList = new Tri_index[trisize / 6];			//6 because 3 shorts and 2 bytes each short
	unsigned short *pconductor =(unsigned short*)tribuff;
	for(unsigned int i =0;i<trisize/6;i ++)
	{
		TriList[i].v0 = *pconductor;
		pconductor++;
		TriList[i].v1 = *pconductor;
		pconductor++;
		TriList[i].v2 = *pconductor;
		pconductor++;

	}

	this->numVerts = (signed) (vertsize / sizeof(Vert_xyzuvn));
	this->numtris = (signed)(trisize / 6);
	
	// Create a VAO
	glGenVertexArrays(1, &this->vao);
	assert(this->vao != 0);
	glBindVertexArray(this->vao);
	// Create a VBO
	glGenBuffers(2, &this->vbo[0]);
	assert(this->vbo[0] != 0);
	glBindBuffer(GL_ARRAY_BUFFER, this->vbo[0]);

	// load the data to the GPU
	glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)(vertsize), vertbuff, GL_STATIC_DRAW);

	Vert_xyzuvn *ptemp = (Vert_xyzuvn*) vertbuff;	//to find the offset of the data in the array

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
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, (GLsizeiptr)(trisize*2), TriList, GL_STATIC_DRAW);


	delete[] TriList;		// freeing memory for list
	delete vertbuff;
	delete tribuff;
}
