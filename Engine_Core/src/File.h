//-----------------------------------------------------------------------------
// Copyright Ed Keenan 2017
// Optimized C++
//----------------------------------------------------------------------------- 

#ifndef FILE_NEW_H
#define FILE_NEW_H

// Make the assumption of c-char strings, not UNICODE
// 32 bit files, not supporting 64 bits

class File
{
public:

	typedef void *Handle;

	enum Mode
	{
		READ = 0x7A000000,
		WRITE ,
		READ_WRITE
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
   static File::Error Open(		File::Handle &fh, const char * const fileName, File::Mode mode );
   static File::Error Close(	const File::Handle &fh );
   static File::Error Write(	const File::Handle &fh, const void * const buffer, const size_t inSize );
   static File::Error Read(		const File::Handle &fh, void * const _buffer, const size_t _size );
   static File::Error Seek(		const File::Handle &fh, File::Location location, int offset );
   static File::Error Tell(		const File::Handle &fh, unsigned int &offset );
   static File::Error Flush(	const File::Handle &fh );
   static File::Error Getlist(const char * Filename, SingleName *& ListOfName, unsigned int & Num);

};

#endif

// ---  End of File ---------------
