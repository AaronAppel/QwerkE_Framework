#ifndef _FileSystem_H_
#define _FileSystem_H_

class Mesh;
typedef int ALsizei;

class FileSystem
{
public:
	FileSystem();
	~FileSystem();

	// TODO: LoadHDRImage // https://learnopengl.com/PBR/IBL/Diffuse-irradiance
	unsigned char* LoadSoundFile(const char* path, DWORD& bufferSize, unsigned short& channels, ALsizei frequency);

	// TODO: Allow flags for loading images a certain way
	// TODO: Remove GLenum and any implementation specific variables or styles
	unsigned char* LoadImageFile(const char* path, unsigned int* imageWidth, unsigned int* imageHeight, GLenum& channels, bool flipVertically = 0); // LoadImage is a macro somewhere
	// TODO:
	Mesh* LoadMeshInModelByName(const char* modelFilePath, const char* meshName);
	bool LoadModelFileToMeshes(const char* path);
	Mesh* LoadModelFileTo1Mesh(const char* path);

	// TODO: Load scene from software like 3DS Max, Blender, etc
	// load things like lights, cameras and everything from 1 file
	// look at creating a conversion helper for QwerkE.scene to unity, blender, etc

	// Material* GetMaterialFromMatFile(const char* path);

private:

};

#endif //!_FileSystem_H_
