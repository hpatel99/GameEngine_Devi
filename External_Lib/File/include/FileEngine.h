//-----------------------------------------------------------------------------
// Copyright Ed Keenan 2017
// Optimized C++
//----------------------------------------------------------------------------- 

#ifndef FILE_H
#define FILE_H

// Make the assumption of c-char strings, not UNICODE
// 32 bit files, not supporting 64 bits

class FileEngine
{
public:

	typedef void *Handle;

	enum Mode
	{
		READ = GENERIC_READ,
		WRITE = GENERIC_WRITE,
		READ_WRITE = GENERIC_ALL
	};

	enum Location
	{
		BEGIN = 0x7B000000,
		CURRENT,
		END
	};

	enum Error
	{
		SUCCESS = 0x7C000000,
		OPEN_FAIL,
		CLOSE_FAIL,
		WRITE_FAIL,
		READ_FAIL,
		SEEK_FAIL,
		TELL_FAIL,
		FLUSH_FAIL,
		GETLIST_FAIL,
		NOT_INITIALIZED
	};

	struct SingleName
	{
		char Filename[32];
	};
public:
	static FileEngine::Error Open(FileEngine::Handle &fh, const char * const fileName, FileEngine::Mode mode);
	static FileEngine::Error Close(const FileEngine::Handle &fh);
	static FileEngine::Error Write(const FileEngine::Handle &fh, const void * const buffer, const size_t inSize);
	static FileEngine::Error Read(const FileEngine::Handle &fh, void * const _buffer, const size_t _size);
	static FileEngine::Error Seek(const FileEngine::Handle &fh, FileEngine::Location location, int offset);
	static FileEngine::Error Tell(const FileEngine::Handle &fh, unsigned int &offset);
	static FileEngine::Error Flush(const FileEngine::Handle &fh);
	static FileEngine::Error Getlist(char * Filename, SingleName *& ListOfName, unsigned int & Num);

};

#endif

// ---  End of FileEngine ---------------
