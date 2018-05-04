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
#include "../../Shared_Generic/Libraries/pThreads/pthread.h"

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

#include <queue>

class JobManager
{
public:
	JobManager();
	~JobManager();

	void ScheduleTask(QJob* job);

private:
	std::queue<QJob*> m_JobList;
	void ProcessNextTask();
};

#endif // !_JobManager_H_
