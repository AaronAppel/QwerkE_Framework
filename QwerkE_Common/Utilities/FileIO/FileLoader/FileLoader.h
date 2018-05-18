#ifndef _FileLoader_H_
#define _FileLoader_H_

// TODO: Depending on how files are loaded, FileLoader
// should be a part of Framework instead of Common.

class Model;
class Material;

namespace QwerkE
{
	namespace FileLoader
	{
		void LoadSound();

		// TODO: Allow flags for loading images a certain way
		// TODO: Remove GLenum and any implementation specific variables or styles
		unsigned char* LoadImageFile(const char* path, unsigned int* imageWidth, unsigned int* imageHeight, GLenum& channels, bool flipVertically = 0); // LoadImage is a macro somewhere

		Model* LoadModelFile(const char* path);

		// TODO: Load scene from software like 3DS Max, Blender, etc
		// load things like lights, cameras and everything from 1 file
		// look at creating a conversion helper for QwerkE.scene to unity, blender, etc

		// Material* GetMaterialFromMatFile(const char* path);
	}
}

#endif // !_FileLoader_H_
