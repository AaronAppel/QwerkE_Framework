#ifndef _Jobs_H_
#define _Jobs_H_

/*
	An interface for multi threaded tasks
	https://computing.llnl.gov/tutorials/pthreads/
*/

// TODO: Remove have struct order dependency
#ifndef HAVE_STRUCT_TIMESPEC
#define HAVE_STRUCT_TIMESPEC
#endif
#include "../../Libraries/pThreads/pthread.h"

#include "../Events/EventManager.h"
#include "../Events/Event.h"
#include "../Events/AssetLoadedEvent.h"

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

    class Jobs
    {
    public:
        static void ScheduleTask(QJob* job);

        static void ProcessTasks();

    private:
        Jobs() {}
        ~Jobs() {}

        static std::queue<QJob*> m_JobList;
        static void ProcessNextTask();
    };

}
#endif // _Jobs_H_
