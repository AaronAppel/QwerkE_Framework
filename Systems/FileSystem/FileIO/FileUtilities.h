#ifndef __FileUtilities_H_
#define __FileUtilities_H_

#include <string>
#include <vector>

// reading
char* LoadFile(const char* filename);
char* LoadCompleteFile(const char* filename, long* length);
char* ReadRawBytesFromFile(const char* filename);

// reading by file type
unsigned char* LoadWaveFileData(const char* filePath, unsigned long& bufferSize, unsigned short& channels, unsigned int& frequency, unsigned short& bitsPerSample);

// writing
void WriteRawBytesToFile(const char* filename, const char* data, int numBytes);
void WriteStringToFile(const char* filename, const char* string);

// directory
bool FileExists(const char* filePath);
std::vector<std::string> ReadDir(const char* directory);

// file creation
void CreateUniqueFile(const char* filename); // won't overwrite existing file

// file name manipulation
std::string GetFileExtension(const char* filePath);
std::string GetFileNameWithExt(const char* filePath);
std::string GetFileNameNoExt(const char* filePath);

#endif // __FileUtilities_H_