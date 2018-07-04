//-----------------------------------------------------------------------------
// Copyright Ed Keenan 2017
// Optimized C++
//----------------------------------------------------------------------------- 

#include <assert.h>

#define STUB_PLEASE_REPLACE(x) (x)
// Windows.h include
	// many warnings - need to wrap for Wall warnings
	#pragma warning( push )
	#pragma warning( disable : 4820 )
	#pragma warning( disable : 4668 )
		#include <Windows.h>
	#pragma warning( pop ) 

#include "File.h"
//#include <fileapi.h>
//
//#include <xutility>

#define UNUSED_VAR(x) ((void *)x)
File::Error File::Open( File::Handle &fh, const char * const fileName, File::Mode mode )
{
	Error toreturn = Error::NOT_INITIALIZED;
	DWORD CreateDipo;
	DWORD DesiredAccess;
	DWORD SharedMode;
	switch (mode)
	{
	case READ:
		CreateDipo = OPEN_EXISTING ;
		DesiredAccess = GENERIC_READ;
		SharedMode = FILE_SHARE_READ;

		break;
	case WRITE:
		CreateDipo = CREATE_ALWAYS;
		DesiredAccess = GENERIC_WRITE;
		SharedMode = FILE_SHARE_WRITE;
		break;
	case READ_WRITE:
		CreateDipo = OPEN_ALWAYS;				// open if exist else create a new one
		DesiredAccess = GENERIC_READ |GENERIC_WRITE;
		SharedMode = FILE_SHARE_WRITE;
		break;
	default:
		CreateDipo = 0;
		DesiredAccess = 0;
		SharedMode = 0;
		break;
	}


	fh= CreateFile(fileName, DesiredAccess, SharedMode, nullptr, CreateDipo, FILE_ATTRIBUTE_NORMAL, nullptr);
	 DWORD const   result = GetLastError();
	 if(result == 0 || result == ERROR_ALREADY_EXISTS)
	 {		//File was built
			//TODO: open it
		 toreturn = Error::SUCCESS;
	 }	
	 else
	 {
		 toreturn = Error::OPEN_FAIL;
	 }

	return 	toreturn;
}

File::Error File::Close(const File::Handle &fh )	//HAck : cosnt removed :D
{
	Error toreturn = Error::NOT_INITIALIZED;
	
	if(CloseHandle(fh))
		toreturn = Error::SUCCESS;
	
	else
	{
		toreturn = Error::CLOSE_FAIL;
	}

	return toreturn;
}

File::Error File::Write( const File::Handle &fh, const void * const buffer, const size_t inSize )
{
	Error toreturn = Error::NOT_INITIALIZED;
	
	if (WriteFile(fh, buffer, inSize, nullptr, nullptr) != 0)
	{
		toreturn = Error::SUCCESS;
	}
	else
	{
		DWORD const   result = GetLastError();
		toreturn = Error::WRITE_FAIL;
	}
	return toreturn;
}

File::Error File::Read(const File::Handle &fh,  void * const buffer, const size_t inSize )
{
	Error toreturn = Error::NOT_INITIALIZED;
	if(ReadFile(fh, buffer, inSize, nullptr, nullptr))
	{
		toreturn = Error::SUCCESS;
	}
	else
		toreturn = Error::READ_FAIL;

	return toreturn;
}

File::Error File::Seek(const File::Handle &fh, File::Location location, int offset)
{
	Error toreturn = Error::NOT_INITIALIZED;
	DWORD result = 0;
	if (location == Location::BEGIN)
	{
		result = SetFilePointer(fh, offset, nullptr, 0);
		
	}
	else if (location == Location::CURRENT)
	{
		result = SetFilePointer(fh, offset, nullptr, 1);
		
	}
	else if (location == Location::END)
	{
		result = SetFilePointer(fh, offset, nullptr, 2);
		
	}

	if (result != INVALID_SET_FILE_POINTER)
	{
		toreturn = Error::SUCCESS;
	}
	else
	{
		toreturn = Error::SEEK_FAIL;
	}

	return toreturn;
}

File::Error File::Tell(const File::Handle &fh, unsigned int &offset )
{
	Error result = NOT_INITIALIZED;
	

	offset = SetFilePointer(fh,0, nullptr, 1);
	  
	if (offset == INVALID_SET_FILE_POINTER)
	{
		
		result = Error::TELL_FAIL;
	}
	else
	{

		result = Error::SUCCESS;
	}

	return result	;
}

File::Error File::Flush(const File::Handle &fh )
{
	Error result = Error::NOT_INITIALIZED;
	if(FlushFileBuffers(fh))
	{
		result = Error::SUCCESS;
	}
	else
	{
		result = Error::FLUSH_FAIL;
	}
	return 	result;

	
}

File::Error File::Getlist(const char * Filename, SingleName *& ListOfName,unsigned int & Num)
{
	UNUSED_VAR(Filename);
	UNUSED_VAR(ListOfName);
	UNUSED_VAR(Num);

	WIN32_FIND_DATA FileData;
	Handle f_handle;
	File::Error result = File::NOT_INITIALIZED;
	
	
	f_handle = FindFirstFile(Filename, &FileData);
	
	if(f_handle != INVALID_HANDLE_VALUE)	//There is atleast one file found 
	{
		char *pSource = FileData.cFileName;
		char *pDestination = ListOfName->Filename;

		while(*pSource != '\0')
		{
			memcpy_s(pDestination, 1, pSource, 1);
			pSource++;
			pDestination++;

		}
		memcpy_s(pDestination, 1, pSource, 1);
		Num++;
		ListOfName++;

		while(FindNextFile(f_handle, &FileData))
		{
			

			pSource = FileData.cFileName;
			pDestination = ListOfName->Filename;
			while (*pSource != '\0')
			{
				memcpy_s(pDestination, 1, pSource, 1);
				pSource++;
				pDestination++;

			}
			memcpy_s(pDestination, 1, pSource, 1);
			Num++;
			ListOfName++;
			
		}

		result = File::SUCCESS;
	}
	else
	{
		result = File::GETLIST_FAIL;
	}
	
	return result;
	
}



// ---  End of File ---------------
