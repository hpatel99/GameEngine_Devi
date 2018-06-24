#include "Log.h"
#include "File.h"


#define WRITE_DATA_TO_FILE 1
#if WRITE_DATA_TO_FILE
#define TRILIST_NUM_TRIANGLES (sizeof(logtriList)/sizeof(Tri_index))
#define LOG_DATA_NUM_VERTS (sizeof(logData)/sizeof(Vert_xyzuvn))

Tri_index logtriList[] =
{
	//Face 1
	{ 1, 2, 0 },
	{ 2, 3, 0 },
	{ 3, 4, 0 },
	{ 4, 5, 0 },
	{ 5, 6, 0 },
	{ 6, 7, 0 },

	//Face 2
	{ 8, 10, 9 },
	{ 8, 11, 10 },
	{ 8, 12, 11 },
	{ 8, 13, 12 },
	{ 8, 14, 13 },
	{ 8, 15, 14 },

	{ 16, 17, 18 },
	{ 19, 20, 21 },

	{ 22, 23, 24 },
	{ 25, 26, 27 },

	{ 28, 29, 30 },
	{ 31, 32, 33 },

	{ 34, 35, 36 },
	{ 37, 38, 39 },

	{ 40, 41, 42 },
	{ 43, 44, 45 },

	{ 46, 47, 48 },
	{ 49, 50, 51 },

	{ 52, 53, 54 },
	{ 55, 56, 57 },

	{ 58, 59, 60 },
	{ 61, 62, 63 }
};

Vert_xyzuvn  logData[] =
{

	{ 0.5f,		0.0f,	0.0f, 1.0f,	 0.5f,  -0.6f, -0.6f,  -0.6f },		//Vert 0
	{ 0.35f,	0.35f,	0.0f, 0.85f, 0.85f, -0.6f, -0.6f, -0.6f },		//Vert 1
	{ -0.09f,	0.5f,	0.0f, 0.41f, 1.0f,   0.6f, -0.6f, -0.6f },		//Vert 2
	{ -0.36f,	0.35f,	0.0f, 0.14f, 0.85f,  0.6f, -0.6f, -0.6f },		//Vert 3
	{ -0.5f,	-0.009f,0.0f, 0.0f,  0.49f,  0.6f, 0.6f, -0.6f },		//Vert 4
	{ -0.36f,	-0.36f, 0.0f, 0.14f, 0.14f,  0.6f,0.6f,  -0.6f },		//Vert 5
	{ 0.0f,		-0.5f,	0.0f, 0.5f,  0.0f,   -0.6f, 0.6f, -0.6f },		//Vert 6
	{ 0.35f,	-0.36f, 0.0f, 0.85f, 0.14f,  -0.6f, 0.6f, -0.6f },		//Vert 7

	{ 0.5f,		0.0f,	1.0f, 1.0f,	 0.5f,  0.6f, 0.6f,  0.6f },		//Vert 8
	{ 0.35f,	0.35f,	1.0f, 0.85f, 0.85f, 0.6f, 0.6f, 0.6f },			//Vert 9
	{ -0.09f,	0.5f,	1.0f, 0.41f, 1.0f,   -0.6f, 0.6f, 0.6f },		//Vert 10
	{ -0.36f,	0.35f,	1.0f, 0.14f, 0.85f,  -0.6f, 0.6f, 0.6f },		//Vert 11
	{ -0.5f,	-0.009f,1.0f, 0.0f,  0.49f,  -0.6f, -0.6f, 0.6f },		//Vert 12
	{ -0.36f,	-0.36f, 1.0f, 0.14f, 0.14f,  -0.6f,-0.6f,  0.6f },		//Vert 13
	{ 0.0f,		-0.5f,	1.0f, 0.5f,  0.0f,   0.6f, -0.6f, 0.6f },		//Vert 14
	{ 0.35f,	-0.36f, 1.0f, 0.85f, 0.14f,  0.6f, -0.6f, 0.6f },		//Vert 15


																		//Edges
	{ 0.5f,		0.0f,	1.0f, 1.0f,	 1.0f,  0.6f, 0.6f,  0.6f },		//Vert 8 16
	{ 0.35f,	0.35f,	0.0f, 0.0f,	 0.0f, 0.6f, 0.6f, 0.6f },		//Vert 1 17
	{ 0.5f,		0.0f,	0.0f, 0.0f,	 1.0f,  0.6f, 0.6f,  0.6f },		//Vert 0 18

	{ 0.35f,	0.35f,	1.0f, 1.0f, 0.0f, 0.6f, 0.6f, 0.6f },		//Vert 9
	{ 0.35f,	0.35f,	0.0f, 0.0f, 0.0f, 0.6f, 0.6f, 0.6f },		//Vert 1
	{ 0.5f,		0.0f,	1.0f, 1.0f,	1.0f,  0.6f, 0.6f,  0.6f },		//Vert 8


	{ 0.35f,	0.35f,	1.0f, 1.0f,	 1.0f, 0.6f, 0.6f, 0.6f },		//Vert 9
	{ -0.09f,	0.5f,	0.0f, 0.0f,	 0.0f,  -0.6f, 0.6f, 0.6f },		//Vert 2
	{ 0.35f,	0.35f,	0.0f, 0.0f,	 1.0f, 0.6f, 0.6f, 0.6f },		//Vert 1

	{ -0.09f,	0.5f,	1.0f, 1.0f, 0.0f,   -0.6f, 0.6f, 0.6f },		//Vert 10
	{ -0.09f,	0.5f,	0.0f, 0.0f, 0.0f,   -0.6f, 0.6f, 0.6f },		//Vert 2
	{ 0.35f,	0.35f,	1.0f, 1.0f,	1.0f,  0.6f, 0.6f, 0.6f },		//Vert 9


	{ -0.09f,	0.5f,	1.0f, 1.0f,	 1.0f,  -0.6f, 0.6f, 0.6f },		//Vert 10
	{ -0.36f,	0.35f,	0.0f, 0.0f,	 0.0f,  -0.6f, 0.6f, 0.6f },		//Vert 3
	{ -0.09f,	0.5f,	0.0f, 0.0f,	 1.0f,  -0.6f, 0.6f, 0.6f },		//Vert 2

	{ -0.36f,	0.35f,	1.0f, 1.0f, 0.0f,  -0.6f, 0.6f, 0.6f },		//Vert 11
	{ -0.36f,	0.35f,	0.0f, 0.0f, 0.0f,   -0.6f, 0.6f, 0.6f },		//Vert 3
	{ -0.09f,	0.5f,	1.0f, 1.0f,	1.0f,   -0.6f, 0.6f, 0.6f },		//Vert 10


	{ -0.36f,	0.35f,	1.0f, 1.0f,	 1.0f,  -0.6f, 0.6f, 0.6f },		//Vert 11
	{ -0.5f,	-0.009f,0.0f, 0.0f,	 0.0f,  -0.6f, -0.6f,  0.6f },		//Vert 4
	{ -0.36f,	0.35f,	0.0f, 0.0f,	 1.0f,  -0.6f, 0.6f, 0.6f },		//Vert 3

	{ -0.5f,	-0.009f,1.0f, 1.0f, 0.0f,   -0.6f, -0.6f,  0.6f },		//Vert 12
	{ -0.5f,	-0.009f,0.0f, 0.0f, 0.0f,   -0.6f, -0.6f,  0.6f },		//Vert 4
	{ -0.36f,	0.35f,	1.0f, 1.0f,	1.0f,   -0.6f, 0.6f, 0.6f },		//Vert 11


	{ -0.5f,	-0.009f,1.0f, 1.0f,	 1.0f,  -0.6f, -0.6f,  0.6f },		//Vert 12
	{ -0.36f,	-0.36f, 0.0f, 0.0f,	 0.0f,  -0.6f,-0.6f,  0.6f },		//Vert 5
	{ -0.5f,	-0.009f,0.0f, 0.0f,	 1.0f,  -0.6f, -0.6f,  0.6f },		//Vert 4

	{ -0.36f,	-0.36f, 1.0f, 1.0f, 0.0f,   -0.6f,-0.6f,  0.6f },		//Vert 13
	{ -0.36f,	-0.36f, 0.0f, 0.0f, 0.0f,   -0.6f,-0.6f,  0.6f },		//Vert 5
	{ -0.5f,	-0.009f,1.0f, 1.0f,	1.0f,   -0.6f, -0.6f,  0.6f },		//Vert 12


	{ -0.36f,	-0.36f, 1.0f, 1.0f,	 1.0f,  -0.6f,-0.6f,  0.6f },		//Vert 13
	{ 0.0f,		-0.5f,	0.0f, 0.0f,	 0.0f,  0.6f, -0.6f, 0.6f },		//Vert 6
	{ -0.36f,	-0.36f, 0.0f, 0.0f,	 1.0f,  -0.6f,-0.6f,  0.6f },		//Vert 5

	{ 0.0f,		-0.5f,	1.0f, 1.0f, 0.0f,   0.6f, -0.6f, 0.6f },		//Vert 14
	{ 0.0f,		-0.5f,	0.0f, 0.0f, 0.0f,   0.6f, -0.6f, 0.6f },		//Vert 6
	{ -0.36f,	-0.36f, 1.0f, 1.0f,	1.0f,   -0.6f,-0.6f,  0.6f },		//Vert 13


	{  0.0f,	 -0.5f,	1.0f, 1.0f,	 1.0f, 0.6f, -0.6f, 0.6f },		//Vert 14
	{ 0.35f,	-0.36f, 0.0f, 0.0f,	 0.0f, 0.6f, -0.6f, 0.6f },		//Vert 7
	{  0.0f,	 -0.5f,	0.0f, 0.0f,	 1.0f, 0.6f, -0.6f, 0.6f },		//Vert 6

	{ 0.35f,	-0.36f, 1.0f, 1.0f, 0.0f,  0.6f, -0.6f, 0.6f },		//Vert 15
	{ 0.35f,	-0.36f, 0.0f, 0.0f, 0.0f,  0.6f, -0.6f, 0.6f },		//Vert 7
	{  0.0f,		 -0.5f,	1.0f, 1.0f,	1.0f,  0.6f, -0.6f, 0.6f },		//Vert 14


	{ 0.35f,	-0.36f, 1.0f,1.0f,	 1.0f, 0.6f, -0.6f, 0.6f },		//Vert 15
	{  0.5f,	 0.0f,	0.0f,0.0f,	 0.0f,0.6f, 0.6f,  0.6f },		//Vert 0
	{ 0.35f,	-0.36f, 0.0f,0.0f,	 1.0f, 0.6f, -0.6f, 0.6f },		//Vert 7

	{  0.5f,	 0.0f,	1.0f,1.0f, 0.0f, 0.6f, 0.6f,  0.6f },		//Vert 8
	{  0.5f,	 0.0f,	0.0f,0.0f, 0.0f, 0.6f, 0.6f,  0.6f },		//Vert 0
	{ 0.35f,	-0.36f, 1.0f,1.0f,	1.0f,  0.6f, -0.6f, 0.6f },		//Vert 15
};
#endif

LogModel::LogModel(const char * const pModelFileName)
	:Model(Model::Name::LOG)
{
	assert(pModelFileName);
	this->privCreateVAO(pModelFileName);
}

LogModel::~LogModel()
{
}

void LogModel::privCreateVAO(const char * const modelfileNAME)
{
	//calculate

	assert(modelfileNAME);
	// future proofing it for a file
	UNUSED_VAR(modelfileNAME);

#if WRITE_DATA_TO_FILE
	//Write the data to file
	this->numVerts = LOG_DATA_NUM_VERTS;
	this->numtris = TRILIST_NUM_TRIANGLES;
	

	//Create fileheader
	ModelFileHeader modelHeader;
	//write nME
	strncpy_s(modelHeader.objName, OBJECT_NAME_SIZE, "Log", _TRUNCATE);

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

	ferror = File::Write(fh, logData, sizeof(Vert_xyzuvn) * this->numVerts);
	assert(ferror == File::Error::SUCCESS);

	// write the index buffer
	ferror = File::Tell(fh, modelHeader.triListBufferOffset);
	assert(ferror == File::Error::SUCCESS);

	ferror = File::Write(fh, logtriList, sizeof(Tri_index) * this->numtris);
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
	Vert_xyzuvn  *logData = new Vert_xyzuvn[(unsigned int)modelHdr.numVerts];
	Tri_index *logtriList = new Tri_index[(unsigned int)modelHdr.numTriList];



	// Read verts
	ferror = File::Seek(fh2, File::Location::BEGIN, (int)modelHdr.vertBufferOffset);
	assert(ferror == File::Error::SUCCESS);

	ferror = File::Read(fh2, logData, sizeof(Vert_xyzuvn) * this->numVerts);
	assert(ferror == File::Error::SUCCESS);

	// Read trilist
	ferror = File::Seek(fh2, File::Location::BEGIN, (int)modelHdr.triListBufferOffset);
	assert(ferror == File::Error::SUCCESS);

	ferror = File::Read(fh2, logtriList, sizeof(Tri_index) * this->numtris);
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
	glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)(sizeof(Vert_xyzuvn) * this->numVerts), logData, GL_STATIC_DRAW);

	// define an array of generic vertex attribute data
	// Vert data is 0
	// todo make a table or enum
	void *offsetVert = (void *)((unsigned int)&logData[0].x - (unsigned int)logData);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vert_xyzuvn), offsetVert);

	// Enable or disable a generic vertex attribute array
	glEnableVertexAttribArray(0);

	// Texture data is location: 1  (used in vertex shader)
	void *offsetTex = (void *)((unsigned int)&logData[0].u - (unsigned int)logData);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vert_xyzuvn), offsetTex);
	glEnableVertexAttribArray(1);

	//NormAL data in location 2
	void *offsetNorm = (void *)((unsigned int)&logData[0].nx - (unsigned int)logData);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vert_xyzuvn), offsetNorm);
	glEnableVertexAttribArray(2);



	/* Bind our 2nd VBO as being the active buffer and storing index ) */
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[1]);

	/* Copy the index data to our buffer */
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, (GLsizeiptr)(sizeof(Tri_index) * this->numtris), logtriList, GL_STATIC_DRAW);

}
