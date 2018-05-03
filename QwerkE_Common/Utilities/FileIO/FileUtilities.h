#ifndef __FileUtilities_H_
#define __FileUtilities_H_

char* LoadFile(const char* filename);
char* LoadCompleteFile(const char* filename, long* length);
void WriteStringToFile(const char* filename, const char* string);

#endif // __FileUtilities_H_