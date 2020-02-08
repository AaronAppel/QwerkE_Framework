#include "Jobs.h"
#include "../Events/EventManager.h"
#include "../Events/JobQueuedEvent.h"
#include "../../QwerkE_Common/Utilities/FileIO/FileUtilities.h"

namespace QwerkE {

    std::queue<QJob*> Jobs::m_JobList;

    void Jobs::ScheduleTask(QJob* job)
    {
        // TODO: Think of avoiding duplicate jobs
        m_JobList.push(job);
        Event* _event = new JobQueuedEvent();
        ((EventManager*)QwerkE::Services::GetService(eEngineServices::Event_System))->QueueEvent(_event);
    }

    void Jobs::ProcessTasks()
    {
        for (size_t i = 0; i < m_JobList.size(); i++)
        {
            QJob* next = m_JobList.front();
            m_JobList.pop();

            next->Process(); // get a thread and process job
        }
    }

    // Private
    void Jobs::ProcessNextTask()
    {
        QJob* next = m_JobList.front();
        m_JobList.pop();

        next->Process(); // get a thread and process job
    }

    void* LoadAssetData(void* value)
    {
        // TODO: Support all types of assets or files
        QImageFile fileData;
        fileData.s_Name = (char*)value;

        if (FileExists(TextureFolderPath(fileData.s_Name.c_str())))
        {
            fileData.s_Data = (char*)FileSystem::LoadImageFileData(TextureFolderPath(fileData.s_Name.c_str()), &fileData.s_Width, &fileData.s_Height, (GLenum&)fileData.s_Channels, false);
        }

        if (fileData.s_Data != nullptr)
        {
            // raise event
            AssetLoadedEvent* _event = new AssetLoadedEvent(fileData);
            ((EventManager*)QwerkE::Services::GetService(eEngineServices::Event_System))->QueueEvent(_event);
        }

        pthread_exit(NULL);

        return NULL;
    }

}
