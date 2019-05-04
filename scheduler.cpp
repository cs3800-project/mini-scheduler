#include "scheduler.h"

// Shortest Job Next
void Scheduler::SJN(int &time) {
    // no processes to schedule
    if(mProcesses.size() == 0) {
        return;
    }

	Process* sjnProc;

    // sort original processes by arrival time of job
    // sort(mProcesses.begin(), mProcesses.end(), earlierJob);

	for(int i = 0; i < mProcesses.size(); i++) {
		cout << mProcesses[i]->mName << endl;
	}
	cout << "-----------------------------" << endl;

	for(int i = 0; i < mProcesses.size(); i++) {
		// if the process has shown up yet at the current time
		if(mProcesses[i]->mArrivalT <= time) {
			sjnProc = *min_element(mProcesses.begin(), mProcesses.end(), shorterJob);
			cout << "runnable process found: " << sjnProc->mName << endl;
			time += sjnProc->mExeT;		
		}
		
		auto it = find(mProcesses.begin(), mProcesses.end(), sjnProc);
		if (it != mProcesses.end()) {
			mProcesses.erase(it);
		}
	}
}

// Shortest Remaining Time
void Scheduler::SRT(int& sysTime)
{
	 // no processes to schedule
    if(mProcesses.size() == 0)
        return;

	Process* srtProc; // process with shortest remaining exe time

	int srt = INT_MAX;	// shortest remaining time

	// determine process with shortest remaining exe time
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

	// "run" SRT process by incrementing its progress time
	srtProc->mProgressT++;

	// increment system time
	sysTime++;

	// update process run time
	srtProc->mRunT = sysTime - srtProc->mArrivalT;

	// process finished
	if (srtProc->mProgressT == srtProc->mExeT)
		cout << "\n\tprocess \'" << srtProc->mName << "\' finished | " 
			<< "run time: " << srtProc->mRunT << "\n";
}

// Highest Response Ratio Next
void Scheduler::HRRN(int& sysTime)
{
	 // no processes to schedule
    if(mProcesses.size() == 0)
        return;

	int hrr = 0; // highest response ratio
	Process* hrrProc; // process with highest response ratio

	// determine process with highest response ratio
	for (int i = 0; i < mProcesses.size(); i++)
	{
		// time spent waiting
		int waitT = sysTime - mProcesses[i]->mArrivalT;

		// response ratio: ( w + s ) / s
		int rr = ( waitT + mProcesses[i]->mExeT )
					/ mProcesses[i]->mExeT;

		if (rr > hrr)
		{
			hrr = rr;
			hrrProc = mProcesses[i];
		}
	}

	// run process with highest response ratio to completion
	hrrProc->mProgressT = hrrProc->mExeT;

	// update system time to reflect process execution
	sysTime+= hrrProc->mExeT;

	// update process run time
	hrrProc->mRunT = sysTime - hrrProc->mArrivalT;

	cout << "\n\tprocess \'" << hrrProc->mName << "\' finished | " 
		<< "run time: " << hrrProc->mRunT << "\n";
}

// remove finished processes from Scheduler
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

bool Scheduler::earlierJob(Process *p1, Process *p2) {
	return p1->mArrivalT < p2->mArrivalT;
}

bool Scheduler::shorterJob(Process *p1, Process *p2) {
	return p1->mExeT < p2->mExeT;
}