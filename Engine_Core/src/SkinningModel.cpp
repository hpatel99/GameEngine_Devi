#include "SkinningModel.h"
#include "MathEngine.h"

SkinnedModel::SkinnedModel(unsigned char * VertBuff, unsigned char * Tribuff, unsigned char * BoneIdx, unsigned char * Boneweight, int numverts, int numtris, Model::Name inName)
	:Model(inName)
{
	this->privCreateVAO(VertBuff, Tribuff, BoneIdx, Boneweight, numverts,numtris);
	
}

SkinnedModel::~SkinnedModel()
{
}

void SkinnedModel::privCreateVAO(const char * const modelfileNAME)
{
	UNUSED_VAR(modelfileNAME);
}

void SkinnedModel::privCreateVAO(unsigned char * VertBuff, unsigned char * Tribuff, unsigned char * BoneIdx, unsigned char * Boneweight, int numverts_, int numtris_)
{
	this->numtris = numtris_;
	this->numVerts = numverts_;
	Tri_index *TriList = (Tri_index*) Tribuff;
	Vert_xyzuvn *pVerts =(Vert_xyzuvn*) VertBuff;
	int *pBoneIndex = (int*)BoneIdx;
	float *pBoneweights = (float*)Boneweight;
	



	// Create a VAO
	glGenVertexArrays(1, &this->vao);
	assert(this->vao != 0);
	glBindVertexArray(this->vao);
	// Create a VBO
	glGenBuffers(4, &this->vbo[0]);
	assert(this->vbo[0] != 0);

	//bind 1st buffer
	glBindBuffer(GL_ARRAY_BUFFER, this->vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)(numVerts*sizeof(Vert_xyzuvn)), VertBuff, GL_STATIC_DRAW);
	
	// pointer maths to find locations(0)
	void*offset = (void*)( (unsigned int)&pVerts->x - (unsigned int)pVerts);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vert_xyzuvn), offset);
	// Enable or disable a generic vertex attribute array
	glEnableVertexAttribArray(0);
	
	//pointer maths to find location 1
	void *offsetTex = (void *)((unsigned int)&pVerts->u - (unsigned int)pVerts);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vert_xyzuvn), offsetTex);
	glEnableVertexAttribArray(1);

	//pointer maths to find location 2
	void *offsetnorm = (void *)((unsigned int)&pVerts->nx - (unsigned int)pVerts);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vert_xyzuvn), offsetnorm);
	glEnableVertexAttribArray(2);

	/* Bind our 2nd VBO as being the active buffer and storing index ) */
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->vbo[1]);
	/* Copy the index data to our buffer */
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, (GLsizeiptr)(numtris *sizeof( Tri_index)), TriList, GL_STATIC_DRAW);


	/* Bind our 3rd VBO as being the active buffer and storing index ) */ // 
	glBindBuffer(GL_ARRAY_BUFFER,this->vbo[2]);
	/* Copy the index data to our buffer */
	glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)(numVerts *4 * sizeof(float) ), pBoneweights, GL_STATIC_DRAW);
	//pointer math to show starting
	glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE,0,0 );
	glEnableVertexAttribArray(3);



	/* Bind our 4th VBO as being the active buffer and storing index ) */ // 
	glBindBuffer(GL_ARRAY_BUFFER, this->vbo[3]);
	/* Copy the index data to our buffer */
	glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)(numVerts * 4 * sizeof(int)), pBoneIndex, GL_STATIC_DRAW);
	glVertexAttribIPointer(4, 4, GL_INT, 0,0);

	glEnableVertexAttribArray(4);



}
