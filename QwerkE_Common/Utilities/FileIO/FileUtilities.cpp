#include "../PrintFunctions.h"

#include <fstream>
#include <iostream>
#include <string>

#define _Win32 // TODO: Fix multi platform

#ifdef _Win32
#include <windows.h>
#include <handleapi.h> // INVALID_HANDLE_VALUE
#include <vector>
// https://msdn.microsoft.com/en-us/library/windows/desktop/aa364418(v=vs.85).aspx
// https://msdn.microsoft.com/en-us/library/windows/desktop/aa365740(v=vs.85).aspx
// https://stackoverflow.com/questions/26475540/c-having-problems-with-a-simple-example-of-findfirstfile
// https://docs.microsoft.com/en-us/cpp/standard-library/filesystem-functions
std::vector<std::string> ReadDir(const char* directory)
{
	// variables
	std::vector<std::string> fileList; // list of file names with extensions
	WIN32_FIND_DATA ffd; // file data object
	HANDLE hand = INVALID_HANDLE_VALUE; // file handle
	std::string dir = directory; // used for easy appending

	dir.append("*.*"); // append "search for all" instruction
	hand = FindFirstFile(dir.c_str(), &ffd); // get the first file in directory

	// valid directory?
	if (INVALID_HANDLE_VALUE == hand)
	{
		int bp = 1; // error
		return fileList;
	}

	// read directory
	do
	{
		if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			// std::cout << ffd.cFileName << std::endl;
		}
		else
		{
			std::cout << ffd.cFileName << std::endl;
			fileList.push_back(ffd.cFileName);
		}
	} while (FindNextFile(hand, &ffd) != 0);

	DWORD dwError = GetLastError();
	if (dwError != ERROR_NO_MORE_FILES)
	{
		//DisplayErrorBox(TEXT("FindFirstFile"));
		int bp = 1;
	}

	FindClose(hand);
	return fileList;
}
#else
#include <fstream>
#include <iostream>
#include <string>
#include <filesystem>
// TODO: Look at std::filesystem
// http://www.modernescpp.com/index.php/c-17-more-details-about-the-library
//http://www.martinbroadhurst.com/list-the-files-in-a-directory-in-c.html
//struct path_leaf_string
//{
//	std::string operator()(const std::filesystem::directory_entry& entry) const
//	{
//		return entry.path().leaf().string();
//	}
//};
//
//void read_directory(const std::string& name, stringvec& v)
//{
//	std::filesystem::path p(name);
//	std::filesystem::directory_iterator start(p);
//	std::filesystem::directory_iterator end;
//	std::transform(start, end, std::back_inserter(v), path_leaf_string());
//}

// MAC
// Linux
// Android
#endif // _Win32


int CharToInt(char num)
{
	return num - 49;
}

void WriteRawBytesToFile(const char* filename, const char* data, int numBytes)
{
	std::ofstream oStream;
	oStream.open(filename, std::ios_base::binary);
	if (oStream.is_open())
	{
		oStream.write((char*)data, numBytes);
		oStream.close();
	}
}

char* ReadRawBytesFromFile(const char* filename)
{
	std::ifstream iStream;
	iStream.open(filename, std::ios_base::binary);

	char* data = nullptr;
	if (iStream.is_open())
	{
		int size = 0;
		iStream.seekg(0, std::ios::end);
		size = (int)iStream.tellg();

		data = new char[size];
		iStream.read(data, size);
		iStream.close();
		return data;
	}

	return nullptr; // pass bytes back
}


// FileUtilities.cpp
char* LoadFile(const char* filename)
{
	FILE* filehandle;
	errno_t error = fopen_s(&filehandle, filename, "rb");
	if (filehandle)
	{
		// find the length of the file
		fseek(filehandle, 0, SEEK_END); // go to the end
		long size = ftell(filehandle); // read the position in bytes
		rewind(filehandle); // go back to the beginning
							// before we can read, we need to allocate a buffer of the right size
		char* buffer = new char[size];
		fread(buffer, size, 1, filehandle);
		fclose(filehandle);

		return buffer;
	}
	else
	{
		return NULL;
	}
}

char* LoadCompleteFile(const char* filename, long* length)
{
	char* filecontents = 0;

	FILE* filehandle;
	errno_t error = fopen_s(&filehandle, filename, "rb");

	if (filehandle)
	{
		fseek(filehandle, 0, SEEK_END);
		long size = ftell(filehandle);
		rewind(filehandle);

		filecontents = new char[size + 1];
		fread(filecontents, size, 1, filehandle);
		filecontents[size] = 0;

		if (length)
			*length = size;

		fclose(filehandle);
	}

	if (filecontents == 0)
	{
		OutputPrint("\nUtilityWin32: LoadCompleteFile() encountered errors loading \"%s\"-> ", filename);
		if (error == 2)
		{
			OutputPrint("No such file or directory!");
		}
	}

	return filecontents;
}

void WriteStringToFile(const char* filename, const char* string)
{
	FILE* filehandle;
	errno_t error = fopen_s(&filehandle, filename, "w+");
	if (filehandle)
	{
		fwrite(string, 1, strlen(string), filehandle); // write to file
		fclose(filehandle); // close file stream
	}
	/*
	fopen_S(&filehandle, "filename", "mode")
	FILE* filehandle;
	char* filename;

	Modes:
	"r"
	Opens for reading. If the file does not exist or cannot be found, the fopen_s call fails.
	"r+" = Opens for both reading and writing. (The file must exist.)

	"w"
	Opens an empty file for writing. If the file exists, its contents are destroyed.
	"w+" = Opens an empty file for both reading and writing. If the file exists, its contents are destroyed.

	"a" = Opens for writing at the end of the file (appending) without removing the EOF marker before writing new data to the file. Creates the file if it doesn't exist.
	"a+" = Opens for reading and appending. The appending operation includes the removal of the EOF marker before
	new data is written to the file and the EOF marker is restored after writing is complete.
	Creates the file if it doesn't exist.

	"T" = Specifies a file as temporary. If possible, it is not flushed to disk.

	"D" = Specifies a file as temporary. It is deleted when the last file pointer is closed.
	*/
}

const char* GetFileExtension(const char* filePath)
{
	std::string test = filePath;
	int extLength = test.size() - test.find_last_of('.') + 1;
	test = test.substr(test.find_last_of('.') + 1, extLength);
	return test.c_str();
}

const char* GetFileNameWithExt(const char* filePath)
{
	std::string test = filePath;

	size_t size = test.find_last_of('/') != test.npos;

	if (size)
	{
		test = test.substr(test.find_last_of('/') + 1, test.size() - test.find_last_of('/') + 1);
	}

	return test.c_str();
}

const char* GetFileNameNoExt(const char* filePath)
{
	std::string test = filePath;

	size_t size = test.find_last_of('/') != test.npos;

	if (size)
	{
		test = test.substr(test.find_last_of('/') + 1, test.find_last_of('.') - 1 - test.find_last_of('/'));

	}
	else
	{
		test = test.substr(0, test.find_last_of('.') - 1);
	}



	return test.c_str();
}