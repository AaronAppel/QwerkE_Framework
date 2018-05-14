#ifndef _FileLoader_H_
#define _FileLoader_H_

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
