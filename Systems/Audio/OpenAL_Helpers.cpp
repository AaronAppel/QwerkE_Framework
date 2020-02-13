#include "OpenAL_Helpers.h"

namespace QwerkE {

    void CheckForOpenALErrors(const char* file, int line)
    {
        switch (alGetError())
        {
            // case AL_INVALID_DEVICE:
            // case AL_INVALID_CONTEXT:
        case AL_INVALID_NAME:
            LOG_ERROR("AL_INVALID_NAME");
            break;
        case AL_INVALID_ENUM:
            LOG_ERROR("AL_INVALID_ENUM");
            break;
        case AL_INVALID_VALUE:
            LOG_ERROR("AL_INVALID_VALUE");
            break;
        case AL_OUT_OF_MEMORY:
            LOG_ERROR("AL_OUT_OF_MEMORY");
            break;
        default:
            LOG_ERROR("Unknown error!");
            break;
        }
    }

    // TODO: Source this or rewrite
    std::string list_audio_devices(const ALCchar* devices)
    {
        // TODO: Improve device detection and assignment
        const ALCchar* device = devices, * next = devices + 1;
        std::string retValue = device;
        size_t len = 0;

        LOG_INFO("OpenAL devices list:");
        LOG_INFO("----------");
        while (device && *device != '\0' && next && *next != '\0') {
            LOG_INFO("%s", (char*)device);
            len = strlen(device);
            device += (len + 1);
            next += (len + 2);
        }
        LOG_INFO("----------");
        return retValue;
    }

    ALuint OpenAL_LoadSound(const QSoundFile& soundFile)
    {
        if (soundFile.s_Data == nullptr) return 0;

        ALuint retValue = 0;
        GLenum format = 0;

        if (soundFile.s_Channels == 1)
        {
            if (soundFile.s_BitsPerSample == 16)
                format = AL_FORMAT_MONO16;
            else if (soundFile.s_BitsPerSample == 8)
                format = AL_FORMAT_MONO8;
            else
                LOG_ERROR("OpenAL_LoadSound(): Invalid bits per sample in %s", soundFile.s_Name);
        }
        else if (soundFile.s_Channels == 2)
        {
            if (soundFile.s_BitsPerSample == 16)
                format = AL_FORMAT_STEREO16;
            else if (soundFile.s_BitsPerSample == 8)
                format = AL_FORMAT_STEREO8;
            else
                LOG_ERROR("OpenAL_LoadSound(): Invalid bits per sample in %s", soundFile.s_Name);
        }
        else
        {
            return 0; // invalid number of channels
        }

        alGenBuffers(1, &retValue);
        alBufferData(retValue, format, soundFile.s_Data, soundFile.s_Size, soundFile.s_Frequency);

        CheckForOpenALErrors(__FILE__, __LINE__);
        return retValue;
    }

}
