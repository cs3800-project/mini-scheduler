#include "scheduler.h"

// TODO: rework logic to increment by time slice instead of quantum
// Shortest Remaining Time
void Scheduler::SRT(const int quantum, const int time)
{
	// if no processes to schedule
	if (mProcesses.size() == 0)
		return;

	int srt = INT_MAX;	// shortest remaining time
	Process* srtProc;	// process with shortest remaining exe time

	for (int i = 0; i < mProcesses.size(); i++)
	{
		// remaining exe time for process
		int rt = mProcesses[i]->mExeT - mProcesses[i]->mProgressT;

		if (rt < srt)
		{
			srt = rt;
			srtProc = mProcesses[i];
		}
	}

	// "run" SRT process by incrementing its progress time by quantum
	srtProc->mProgressT += quantum;

	// process finished
	if (srtProc->mProgressT >= srtProc->mExeT)
	{
		srtProc->mFinished = true;
		srtProc->mRunT = time + quantum - srtProc->mArrivalT;
		cout << "\n\tprocess \'" << srtProc->mName << "\' finished | " 
			<< "run time: " << srtProc->mRunT << "\n";
	}
}

void Scheduler::clean()
{
	// if no jobs left to clean
	if (mProcesses.size() == 0)
		return;

	// check for finished processes 
	for (int i = 0; i < mProcesses.size(); i++)
	{
		// remove process from Scheduler
		if (mProcesses[i]->mFinished)
			mProcesses.erase(mProcesses.begin()+i);
	}
}