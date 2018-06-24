#include "SkyBox.h"
#include  "File.h"
#include <sb7.h>
#define WRITE_DATA_TO_FILE 1
#if WRITE_DATA_TO_FILE
#define TRILIST_NUM_TRIANGLES (sizeof(skyboxtriList)/sizeof(Tri_index))

Tri_index skyboxtriList[] =
{
	{ 0,1,2 },
	{ 0,2,3 },

	{ 6,5,4 },
	{7 ,6,4 },

	{8,9,10},
	{8,10,11},

	{12,13,14},
	{12,14,15},

	{16,17,18},
	{16,18,19},

	{20,21,22},
	{20,22,23}

};

#define SKYBOX_DATA_NUM_VERTS (sizeof(skyboxData)/sizeof(Vert_xyzuvn))

Vert_xyzuvn skyboxData[] =
{
	// Forward

	{ 0.5f, 0.5f, 0.5f, 0.75f, 0.34f,	0.6f,0.6f,0.6f},			
	{-0.5f, 0.5f, 0.5f, 1.0f, 0.34f , -0.6f ,0.6f,0.6f },
	{-0.5f, -0.5f, 0.5f, 1.0f, 0.65f, -0.6f ,-0.6f,0.6f },
	{0.5f, -0.5f, 0.5f, 0.75f, 0.65f, 0.6f ,-0.6f,0.6f},
	// back

	{0.5f, 0.5f, -0.5f, 0.5f, 0.34f		,0.6f,0.6f,-0.6f},
	{-0.5f, 0.5f, -0.5f, 0.25f, 0.34f	,-0.6f,0.6f,-0.6f},
	{-0.5f, -0.5f, -0.5f, 0.25f, 0.65f	,-0.6f,-0.6f,-0.6f},
	{0.5f, -0.5f, -0.5f, 0.5f, 0.65f	,0.6f,-0.6f,-0.6f},


	// left 8
	
	{0.5f, 0.5f, -0.5f, 0.5f, 0.33f	,0.6f,0.6f,-0.6f},
	{0.5f, 0.5f, 0.5f, 0.75f, 0.33f	,0.6f,0.6f,0.6f},
	{0.5f, -0.5f, 0.5f, 0.75f, 0.65f,0.6f,-0.6f,0.6f},
	{0.5f, -0.5f, -0.5f, 0.5f, 0.65f,0.6f,-0.6f,-0.6f},
	
	// Right 12
		
		{-0.5f, 0.5f, 0.5f, 0.05f, 00.34f	,-0.6f,0.6f,0.6f  },
		{-0.5f, 0.5f, -0.5f, 0.25f, 00.34f	,-0.6f,0.6f,-0.6f  },
		{-0.5f, -0.5f, -0.5f, 0.25f, 0.65f	,-0.6f,-0.6f,-0.6f  },
		{-0.5f, -0.5f, 0.5f, 0.05f, 0.65f	,-0.6f,-0.6f,0.6f  },
		//{t(vind + 2, vind + 1, vind);
		//{].set(vind + 3, vind + 2, vind);
		
		// Top 16
		
		  
		{0.5f, 0.5f, -0.5f, 0.5f, 0.32f		,0.6f,0.6f,-0.6f},
		{-0.5f, 0.5f, -0.5f, 0.25f, 0.32f	,-0.6f,0.6f,-0.6f},
		{-0.5f, 0.5f, 0.5f, 0.25f, 0.0f		,-0.6f,0.6f,0.6f},
		{0.5f, 0.5f, 0.5f, 0.5f, 0.0f		,0.6f,0.6f,0.6f},
		//{t(vind + 2, vind + 1, vind);
		//{].set(vind + 3, vind + 2, vind);
		
		// Bottom 20
		
	
	{0.5f, -0.5f, 0.5f, 0.5f, 1.0f		,0.6f,-0.6f,0.6f},
	{-0.5f, -0.5f, 0.5f, 0.28f, 1.0f	,-0.6f,-0.6f,0.6f},
	{-0.5f, -0.5f, -0.5f, 0.28f, 0.65f	,-0.6f,-0.6f,-0.6f},
	{0.5f, -0.5f, -0.5f, 0.5f, 0.65f	,0.6f,-0.6f,-0.6f}
		//(vind + 2, vind + 1, vind);
		//.set(vind + 3, vind + 2, vind);

	
};
#endif
SkyBox::SkyBox(const char * const pModelFileName)
	:Model(Model::Name::SKYBOX)
{
	assert(pModelFileName);
	this->privCreateVAO(pModelFileName);

}


SkyBox::~SkyBox()
{
}

void SkyBox::privCreateVAO(const char * const modelfileNAME)
{
	assert(modelfileNAME);
	// future proofing it for a file
	UNUSED_VAR(modelfileNAME);

#if WRITE_DATA_TO_FILE
	//Write the data to file
	this->numVerts = SKYBOX_DATA_NUM_VERTS;
	this->numtris = TRILIST_NUM_TRIANGLES;
	

	//Create fileheader
	ModelFileHeader modelHeader;
	//write nME
	strncpy_s(modelHeader.objName, OBJECT_NAME_SIZE, "Skybox", _TRUNCATE);

	//Vertex buffer
	modelHeader.numTriList = this->numtris;
	modelHeader.triListBufferOffset = 0;
	modelHeader.numVerts = this->numVerts;
	modelHeader.vertBufferOffset = 0;

	// header is set now write the file;

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

	ferror = File::Write(fh, skyboxData, sizeof(Vert_xyzuvn) * this->numVerts);
	assert(ferror == File::Error::SUCCESS);

	// write the index buffer
	ferror = File::Tell(fh, modelHeader.triListBufferOffset);
	assert(ferror == File::Error::SUCCESS);

	ferror = File::Write(fh, skyboxtriList, sizeof(Tri_index) * this->numtris);
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
	Vert_xyzuvn  *skyboxData = new Vert_xyzuvn[(unsigned int)modelHdr.numVerts];
	Tri_index *skyboxtriList = new Tri_index[(unsigned int)modelHdr.numTriList];



	// Read verts
	ferror = File::Seek(fh2, File::Location::BEGIN, (int)modelHdr.vertBufferOffset);
	assert(ferror == File::Error::SUCCESS);

	ferror = File::Read(fh2, skyboxData, sizeof(Vert_xyzuvn) * this->numVerts);
	assert(ferror == File::Error::SUCCESS);

	// Read trilist
	ferror = File::Seek(fh2, File::Location::BEGIN, (int)modelHdr.triListBufferOffset);
	assert(ferror == File::Error::SUCCESS);

	ferror = File::Read(fh2, skyboxtriList, sizeof(Tri_index) * this->numtris);
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
	glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)(sizeof(Vert_xyzuvn) * this->numVerts), skyboxData, GL_STATIC_DRAW);

	// define an array of generic vertex attribute data
	// Vert data is 0
	// todo make a table or enum
	void *offsetVert = (void *)((unsigned int)&skyboxData[0].x - (unsigned int)skyboxData);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vert_xyzuvn), offsetVert);

	// Enable or disable a generic vertex attribute array
	glEnableVertexAttribArray(0);

	// Texture data is location: 1  (used in vertex shader)
	void *offsetTex = (void *)((unsigned int)&skyboxData[0].u - (unsigned int)skyboxData);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vert_xyzuvn), offsetTex);
	glEnableVertexAttribArray(1);

	//NormAL data in location 2
	void *offsetNorm = (void *)((unsigned int)&skyboxData[0].nx - (unsigned int)skyboxData);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vert_xyzuvn), offsetNorm);
	glEnableVertexAttribArray(2);



	/* Bind our 2nd VBO as being the active buffer and storing index ) */
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[1]);

	/* Copy the index data to our buffer */
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, (GLsizeiptr)(sizeof(Tri_index) * this->numtris), skyboxtriList, GL_STATIC_DRAW);

}
