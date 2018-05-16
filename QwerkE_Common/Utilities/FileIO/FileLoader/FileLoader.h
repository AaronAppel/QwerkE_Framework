#ifndef _FileLoader_H_
#define _FileLoader_H_

// TODO: Depending on how files are loaded, FileLoader
// should be a part of Framework instead of Common.

class Model;

namespace QwerkE
{
	namespace FileLoader
	{
		void LoadSound();

		void LoadImageFile(); // LoadImage is a macro somewhere

		Model* LoadModelFile(const char* path);
	}
}

#endif // !_FileLoader_H_
