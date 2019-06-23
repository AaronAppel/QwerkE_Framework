#include "JobManager.h"

JobManager::JobManager()
{
}

JobManager::~JobManager()
{
}

void JobManager::ScheduleTask(QJob* job)
{
	m_JobList.push(job);
}
// Private
void JobManager::ProcessNextTask()
{
	QPathfind* next = (QPathfind*)m_JobList.front();
	m_JobList.pop();

	next->Process(); // get a thread and process job
}