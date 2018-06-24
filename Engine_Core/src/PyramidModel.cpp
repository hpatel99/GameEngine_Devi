#include "PyramidModel.h"
#include "Model.h"
#include "Matrix.h"

#define WRITE_DATA_TO_FILE 1

#if WRITE_DATA_TO_FILE
#define PYRAMID_DATA_NUM_VERTS (sizeof(pyramidData)/sizeof(Vert_xyzuvn))
#define TRILIST_NUM_TRIANGLES (sizeof(pyramidtriList)/sizeof(Tri_index))




Tri_index pyramidtriList[] =
{
	{ 0,1,2 },
{ 2,3,0 },
{ 4,5,6 },
{ 5,7,6 },
{ 8,9,10 },
{ 9,11,10 },
{ 12,13,14 },
{ 13,15,14 },
{ 16,17,18 },
{ 18,19,16 },
{ 20,21,22 },
{ 22,23,20 }
};

Vert_xyzuvn pyramidData[] =
{
	// Triangle 0
	{ -0.25f,  0.0f, -0.25f, 0.0f, 0.0f, -0.6f,  0.6f, -0.6f }, //0
{ -0.25f, -0.0f, -0.25f, 0.0f, 1.0f, -0.6f, -0.6f, -0.6f },// 1
{ 0.25f, -0.0f, -0.25f, 1.0f, 1.0f,  0.6f, -0.6f, -0.6f }, //2

														   // Triangle 1

{ 0.0f,   1.0f, -0.0f, 1.0f, 0.0f,  0.6f,  0.6f, -0.6f },  //4  3


														   // Triangle 2
{ 0.25f, -0.0f, -0.25f, 0.0f, 1.0f, 0.6f, -0.6f, -0.6f }, //6
{ 0.25f, -0.0f,  0.25f, 1.0f, 1.0f, 0.6f, -0.6f,  0.6f }, //7
{ 0.0f,  1.0f, -0.0f, 0.0f, 0.0f, 0.6f,  0.6f, -0.6f }, //8

														// Triangle 3

{ 0.25f,  0.0f,  0.25f, 1.0f, 0.0f, 0.6f,  0.6f,  0.6f }, //9 


														  // Triangle 4
{ 0.25f, -0.0f,  0.25f, 1.0f, 1.0f,  0.6f, -0.6f, 0.6f },  // 12
{ -0.25f, -0.0f, 0.25f, 0.0f, 1.0f, -0.6f, -0.6f, 0.6f },   // 13
{ 0.0f,  1.0f,  0.0f, 1.0f, 0.0f,  0.6f,  0.6f, 0.6f },  // 14

														 // Triangle 5

{ -0.0f,  1.0f,  0.0f, 0.0f, 0.0f, -0.6f,  0.6f, 0.6f },  //15


														  // Triangle 6
{ -0.25f, -0.0f,  0.25f, 0.0f, 0.0f, -0.6f, -0.6f,  0.6f }, //18
{ -0.25f, -0.0f, -0.25f, 0.0f, 1.0f, -0.6f, -0.6f, -0.6f }, //19
{ -0.0f,  1.0f,  0.0f, 1.0f, 0.0f, -0.6f,  0.6f,  0.6f }, //20

														  // Triangle 7

{ -0.0f,  1.0f, -0.0f, 1.0f, 1.0f, -0.6f,  0.6f, -0.6f }, // 21


														  // Triangle 8
{ -0.25f, -0.0f,  0.25f, 0.0f, 0.0f, -0.6f, -0.6f,  0.6f }, //24
{ 0.25f, -0.0f,   0.25f, 1.0f, 0.0f,  0.6f, -0.6f,  0.6f }, //25
{ 0.25f, -0.0f,  -0.25f, 1.0f, 1.0f,  0.6f, -0.6f, -0.6f }, //26

															// Triangle 9

{ -0.25f, -0.0f, -0.25f, 0.0f, 1.0f, -0.6f, -0.6f, -0.6f }, // 27


															// Triangle 10
{ -0.0f,  1.0f, -0.0f, 0.0f, 1.0f, -0.6f, 0.6f, -0.6f }, //30
{ 0.0f,  1.0f,  -0.0f, 1.0f, 1.0f,  0.6f, 0.6f, -0.6f }, //31
{ 0.0f,  1.0f,   0.0f, 1.0f, 0.0f,  0.6f, 0.6f,  0.6f }, //32

														 // Triangle 11

{ -0.0f,  1.0f,  0.0f, 0.0f, 0.0f, -0.6f, 0.6f,  0.6f }, //33

};
#endif

PyramidModel::PyramidModel(const char * const pModelFileName)
	:Model(Model::Name::Pyramid)
{
	assert(pModelFileName);
	this->privCreateVAO(pModelFileName);

}

PyramidModel::~PyramidModel()
{
}

void PyramidModel::privCreateVAO(const char * const modelfileNAME)
{
	assert(modelfileNAME);
#if WRITE_DATA_TO_FILE
	//Write the data to file
	this->numVerts = PYRAMID_DATA_NUM_VERTS;
	this->numtris = TRILIST_NUM_TRIANGLES;
	
	Matrix M(ROT_X, MATH_PI2);
	for (int i = 0; i < this->numVerts; i++)
	{
		Vect v(pyramidData[i].x, pyramidData[i].y, pyramidData[i].z);
		v = v * M;
		pyramidData[i].x = v[x];
		pyramidData[i].y = v[y];
		pyramidData[i].z = v[z];
	}

	//Create fileheader
	ModelFileHeader modelHeader;
	//write nME
	strncpy_s(modelHeader.objName, OBJECT_NAME_SIZE, "Pyramid", _TRUNCATE);

	//Vertex buffer
	modelHeader.numTriList = this->numtris;
	modelHeader.triListBufferOffset = 0;
	modelHeader.numVerts = this->numVerts;
	modelHeader.vertBufferOffset = 0;

	// header is set now write the File;

	File::Handle fh;
	File::Error  ferror;

	//open towrite
	ferror = File::Open(fh, modelfileNAME, File::Mode::READ_WRITE);
	assert(ferror == File::Error::SUCCESS);

	//write header to File
	ferror = File::Write(fh, &modelHeader, sizeof(ModelFileHeader));
	assert(ferror == File::Error::SUCCESS);

	//Wrie vertex buffer
	ferror = File::Tell(fh, modelHeader.vertBufferOffset);	//write offset to object
	assert(ferror == File::Error::SUCCESS);

	ferror = File::Write(fh, pyramidData, sizeof(Vert_xyzuvn) * this->numVerts);
	assert(ferror == File::Error::SUCCESS);

	// write the index buffer
	ferror = File::Tell(fh, modelHeader.triListBufferOffset);
	assert(ferror == File::Error::SUCCESS);

	ferror = File::Write(fh, pyramidtriList, sizeof(Tri_index) * this->numtris);
	assert(ferror == File::Error::SUCCESS);

	// Finish the write
	ferror = File::Flush(fh);
	assert(ferror == File::Error::SUCCESS);

	// Rewind and overwrite model hdr
	ferror = File::Seek(fh, File::Location::BEGIN, 0);
	assert(ferror == File::Error::SUCCESS);

	ferror = File::Write(fh, &modelHeader, sizeof(ModelFileHeader));
	assert(ferror == File::Error::SUCCESS);

	ferror = File::Flush(fh);
	assert(ferror == File::Error::SUCCESS);

	// VERIFY
	ModelFileHeader modelHdr2;

	ferror = File::Seek(fh, File::Location::BEGIN, 0);
	assert(ferror == File::Error::SUCCESS);

	ferror = File::Read(fh, &modelHdr2, sizeof(ModelFileHeader));
	assert(ferror == File::Error::SUCCESS);

	// CLOSE
	ferror = File::Close(fh);
	assert(ferror == File::Error::SUCCESS);
#else

	File::Handle fh2;
	File::Error  ferror;

	ferror = File::Open(fh2, modelfileNAME, File::Mode::READ);
	assert(ferror == File::Error::SUCCESS);

	// Read the Hdr
	ModelFileHeader modelHdr;
	ferror = File::Read(fh2, &modelHdr, sizeof(ModelFileHeader));
	assert(ferror == File::Error::SUCCESS);

	// Using the hdr, allocate the space for the buffers
	this->numVerts = modelHdr.numVerts;
	this->numtris = modelHdr.numTriList;

	// allocate buffers
	Vert_xyzuvn  *pyramidData = new Vert_xyzuvn[(unsigned int)modelHdr.numVerts];
	Tri_index *pyramidtriList = new Tri_index[(unsigned int)modelHdr.numTriList];



	// Read verts
	ferror = File::Seek(fh2, File::Location::BEGIN, (int)modelHdr.vertBufferOffset);
	assert(ferror == File::Error::SUCCESS);

	ferror = File::Read(fh2, pyramidData, sizeof(Vert_xyzuvn) * this->numVerts);
	assert(ferror == File::Error::SUCCESS);

	// Read trilist
	ferror = File::Seek(fh2, File::Location::BEGIN, (int)modelHdr.triListBufferOffset);
	assert(ferror == File::Error::SUCCESS);

	ferror = File::Read(fh2, pyramidtriList, sizeof(Tri_index) * this->numtris);
	assert(ferror == File::Error::SUCCESS);

	ferror = File::Close(fh2);
	assert(ferror == File::Error::SUCCESS);
#endif
	// Create a VAO
	glGenVertexArrays(1, &this->vao);
	assert(this->vao != 0);
	glBindVertexArray(this->vao);

	// Create a VBO
	glGenBuffers(2, &this->vbo[0]);
	assert(this->vbo[0] != 0);
	glBindBuffer(GL_ARRAY_BUFFER, this->vbo[0]);

	// load the data to the GPU
	glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)(sizeof(Vert_xyzuvn) * this->numVerts), pyramidData, GL_STATIC_DRAW);

	// define an array of generic vertex attribute data
	// Vert data is 0
	// todo make a table or enum
	void *offsetVert = (void *)((unsigned int)&pyramidData[0].x - (unsigned int)pyramidData);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vert_xyzuvn), offsetVert);

	// Enable or disable a generic vertex attribute array
	glEnableVertexAttribArray(0);

	// Texture data is location: 1  (used in vertex shader)
	void *offsetTex = (void *)((unsigned int)&pyramidData[0].u - (unsigned int)pyramidData);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vert_xyzuvn), offsetTex);
	glEnableVertexAttribArray(1);

	//NormAL data in location 2
	void *offsetNorm = (void *)((unsigned int)&pyramidData[0].nx - (unsigned int)pyramidData);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vert_xyzuvn), offsetNorm);
	glEnableVertexAttribArray(2);



	/* Bind our 2nd VBO as being the active buffer and storing index ) */
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[1]);

	/* Copy the index data to our buffer */
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, (GLsizeiptr)(sizeof(Tri_index) * this->numtris), pyramidtriList, GL_STATIC_DRAW);

}
