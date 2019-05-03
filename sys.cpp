#include "sys.h"

// add newly arrived processes from job list to Scheduler
// return: true if one or more processes added to Scheduler
void Sys::schedule()
{
	// if no jobs left to schedule
	if (mProcesses.size() == 0)
	{
		cout << "\nno processes left to schedule!\n";
		return;
	}

	// check for processes arriving at current time
	for (int i = 0; i < mProcesses.size(); i++)
	{
		// add process to Scheduler
		if (mProcesses[i].mArrivalT == mTime)
			mScheduler->mProcesses.push_back(&mProcesses[i]);
	}
}

// check if all processes finished
// return: true if all processes in job list are finished
bool Sys::jobsFinished()
{
	// if no processes in job list
	if (mProcesses.size() == 0)
		return true;

	// print progress of each process on Scheduler
	for (int i = 0; i < mProcesses.size(); i++)
	{
		if (mProcesses[i].mFinished == false)
			return false;
	}

	return true;
}

// print progress of all processes on Scheduler
// return: NONE
void Sys::printProgress()
{
	// if no jobs left to schedule
	if (mScheduler->mProcesses.size() == 0)
		return;

	cout << "\n" << mTime-1 << " ~ " << mTime << " _________________________________\n";

	// print progress of each process on Scheduler
	for (int i = 0; i < mScheduler->mProcesses.size(); i++)
	{
		cout << mScheduler->mProcesses[i]->mName << "\t| ";
		for (int j = 0; j < mScheduler->mProcesses[i]->mProgressT; j++)
			cout << ".";

		cout << "(" << mScheduler->mProcesses[i]->mProgressT << ")\n";
	}
}