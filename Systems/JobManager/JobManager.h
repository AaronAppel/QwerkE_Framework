#ifndef _JobManager_H_
#define _JobManager_H_

/*
	An interface for multi threaded tasks
	https://computing.llnl.gov/tutorials/pthreads/
*/

// TODO: Remove have struct order dependency
#ifndef HAVE_STRUCT_TIMESPEC
#define HAVE_STRUCT_TIMESPEC
#endif
#include "../../../QwerkE_Common/Libraries/pThreads/pthread.h"

#include "../../Graphics/GraphicsUtilities/GraphicsHelpers.h"
#include "../Events/EventManager.h"
#include "../Events/Event.h"
#include "../Events/AssetLoadedEvent.h"
#include "../FileSystem/FileSystem.h"

#include <queue>

namespace QwerkE {

    void* LoadAssetData(void* value); // TODO: Improve logic

    class QJob
    {
    public:
        virtual void Process() = 0;
    };

    class QPathfind : QJob
    {
    public:
        void Process() {};
    };

    class QLoadAsset : public QJob
    {
    public:
        QLoadAsset(const char* assetName)
        {
            m_AssetName = DeepCopyString(assetName);
        }

        void Process()
        {
            // TODO: check duplicate asset
            pthread_t threadID;
            pthread_create(&threadID, NULL, LoadAssetData, (void*)m_AssetName);
        };
    private:
        const char* m_AssetName;
    };

    class JobManager
    {
    public:
        JobManager();
        ~JobManager();

        void ScheduleTask(QJob* job);

        void ProcessTasks();

    private:
        std::queue<QJob*> m_JobList;
        void ProcessNextTask();
    };

}
#endif // !_JobManager_H_
