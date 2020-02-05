#ifndef _FileSystem_H_
#define _FileSystem_H_

#include "../../QwerkE_Common/Libraries/OpenAL/include/al.h"
#include "../../QwerkE_Common/Libraries/glew/GL/glew.h"
#include "../../QwerkE_Common/Utilities/PrintFunctions.h"
#include <string>

class Mesh;
typedef int ALsizei;

namespace QwerkE {

    struct QFile
    {
        std::string s_Name = "null"; // with .extension
        unsigned long s_Size = 0;
        std::string s_Type = "null";
        char* s_Data = nullptr;

        QFile() {}
        virtual ~QFile() {}; // TODO: { delete s_Data; }
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
#ifdef OpenAL
        ALuint s_Handle = 0; // TODO: Keep?
#endif

        QSoundFile() {}
        ~QSoundFile() {} // TODO: alDeleteBuffers(1, &s_Handle)
    };

    class FileSystem
    {
    public:
        FileSystem();
        ~FileSystem();

        // TODO: Allow flags for loading images a certain way
        // TODO: Remove GLenum and any implementation specific variables or styles
        // TODO: LoadHDRImage // https://learnopengl.com/PBR/IBL/Diffuse-irradiance
        unsigned char* LoadImageFileData(const char* path, unsigned int* imageWidth, unsigned int* imageHeight, GLenum& channels, bool flipVertically = 0); // LoadImage is a macro somewhere

#ifdef OpenAL
        typedef unsigned int ALuint;
        ALuint LoadSound(const char* soundName);
#elif defined(XAudio)
        ? ? ? LoadSound(const char* soundName);
#else
#pragma error "Define audio library!"
#endif // OpenAL


        Mesh* LoadMeshInModelByName(const char* modelFilePath, const char* meshName);
        bool LoadModelFileToMeshes(const char* path);
        Mesh* LoadModelFileTo1Mesh(const char* path); // TODO:

        // TODO: Load scene from software like 3DS Max, Blender, etc
        // load things like lights, cameras and everything from 1 file
        // look at creating a conversion helper for QwerkE.scene to unity, blender, etc

        // Material* GetMaterialFromMatFile(const char* path);

    private:
        void LoadSoundFileData(const char* soundName, QSoundFile& soundFile);

    };

}
#endif //!_FileSystem_H_
