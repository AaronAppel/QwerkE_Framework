#ifndef __FileUtilities_H_
#define __FileUtilities_H_

char* LoadFile(const char* filename);
char* LoadCompleteFile(const char* filename, long* length);
void WriteStringToFile(const char* filename, const char* string);

std::string GetFileExtension(const char* filePath);
std::string GetFileNameWithExt(const char* filePath);
std::string GetFileNameNoExt(const char* filePath);

#endif // __FileUtilities_H_