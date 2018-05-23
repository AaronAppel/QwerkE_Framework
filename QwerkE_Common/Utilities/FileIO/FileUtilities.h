#ifndef __FileUtilities_H_
#define __FileUtilities_H_

char* LoadFile(const char* filename);
char* LoadCompleteFile(const char* filename, long* length);
void WriteStringToFile(const char* filename, const char* string);

const char* GetFileExtension(const char* filePath);
const char* GetFileNameWithExt(const char* filePath);
const char* GetFileNameNoExt(const char* filePath);

#endif // __FileUtilities_H_