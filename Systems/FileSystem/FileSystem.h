#ifndef _File_System_H_
#define _File_System_H_

// TODO: Remove
#include "../../Libraries/OpenAL/include/al.h"
#include "../../Libraries/glew/GL/glew.h"

#include <string>

namespace QwerkE {

    class Mesh;

    typedef unsigned int SoundHandle;

    struct QFile
    {
        std::string s_Name = gc_DefaultStringValue; // With .extension
        unsigned long s_Size = 0;
        std::string s_Extension = gc_DefaultStringValue; // Only extension
        char* s_Data = nullptr;

        std::string Extension() {} // TODO:

        QFile() {}
        virtual ~QFile() {}; // TODO: { delete s_Data; }

        // TODO: Meta data
    };

    struct QImageFile : public QFile
    {
        unsigned int s_Width = 0;
        unsigned int s_Height = 0;
        unsigned short s_Channels = 0;

        QImageFile() {}
        ~QImageFile() {}
    };

    struct QSoundFile : public QFile
    {
        unsigned short s_Channels = 0;
        unsigned int s_Frequency = 0;
        unsigned short s_BitsPerSample = 0;

        SoundHandle s_Handle = 0;

        QSoundFile() {}
        ~QSoundFile() {} // TODO: alDeleteBuffers(1, &s_Handle)
    };

    class FileSystem
    {
    public:
        // TODO: Allow flags for loading images a certain way
        // TODO: Remove GLenum and any implementation specific variables or styles
        // TODO: LoadHDRImage // https://learnopengl.com/PBR/IBL/Diffuse-irradiance
        static unsigned char* LoadImageFileData(const char* path, unsigned int* imageWidth, unsigned int* imageHeight, GLenum& channels, bool flipVertically = 0); // LoadImage is a macro somewhere

        static SoundHandle LoadSound(const char* soundName);

        static Mesh* LoadMeshInModelByName(const char* modelFilePath, const char* meshName);
        static bool LoadModelFileToMeshes(const char* path);
        static Mesh* LoadModelFileTo1Mesh(const char* path); // TODO:

        // TODO: Load scene from software like 3DS Max, Blender, etc
        // load things like lights, cameras and everything from 1 file
        // look at creating a conversion helper for QwerkE.scene to unity, blender, etc

        // Material* GetMaterialFromMatFile(const char* path);

    private:
        FileSystem();
        ~FileSystem();

        static void LoadSoundFileData(const char* soundName, QSoundFile& soundFile);
    };

}
#endif //_File_System_H_
