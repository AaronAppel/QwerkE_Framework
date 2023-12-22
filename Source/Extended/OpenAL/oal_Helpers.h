#pragma once

#include <string>

#include "../../../Libraries/OpenAL/include/al.h"
#include "../../../Libraries/OpenAL/include/alc.h"

#include "../../FileSystem/FileSystem.h"

namespace QwerkE {

    void CheckForOpenALErrors(const char* file, int line);
    std::string list_audio_devices(const ALCchar* devices);
    ALuint OpenAL_LoadSound(const QSoundFile& soundFile);

}
