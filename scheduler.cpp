///////////////////////////////////////////////////////////////////////////////
// scheduler.cpp
// @desc: Scheduler class implementation file
///////////////////////////////////////////////////////////////////////////////

#include "scheduler.h"

// First-Come First-Serve
void Scheduler::FCFS(int& sysTime)
{
	// no processes to schedule
    if(mProcesses.size() == 0)
        return;

	// run processes to completion
	mProcesses[0]->mProgressT = mProcesses[0]->mExeT;

	// update system time to reflect process execution
	sysTime += mProcesses[0]->mExeT;

	// update process run time
	mProcesses[0]->mRunT = sysTime - mProcesses[0]->mArrivalT;
}

// Round Robin
void Scheduler::RR(const int quantum, int& sysTime, int& count) {
  // no processes to schedule
    if(mProcesses.size() == 0)
        return;

	int minProgT = INT_MAX;
	Process* nextProc;

	// determine next process
	int index = count % mProcesses.size();
	nextProc = mProcesses[index];

	// "run" next process by incrementing its progress time by quantum
	nextProc->mProgressT += quantum;

	// increment system time by quantum
	sysTime += quantum;

	// increment Round Robin count
	count++;

	// process progress time exceeds process execution time
	if (nextProc->mProgressT > nextProc->mExeT)
	{
		// roll back system time to when process actually completed execution
		sysTime -= (nextProc->mProgressT - nextProc->mExeT);
		nextProc->mProgressT = nextProc->mExeT;
	}
	
	// update process run time
	nextProc->mRunT = sysTime - nextProc->mArrivalT;

	// process finished
	if (nextProc->mProgressT == nextProc->mExeT)
		cout << "\n\tprocess \'" << nextProc->mName << "\' finished | " 
			<< "run time: " << nextProc->mRunT << "\n";
	// process not finished
	else {
		// move process to back to continue execution
		mProcesses.push_back(nextProc);
		// remove original process from starting position
		mProcesses.erase(mProcesses.begin() + index);
	}
}

// Shortest Job Next
void Scheduler::SJN(int& sysTime) {
    // no processes to schedule
    if(mProcesses.size() == 0)
        return;

	Process* sjnProc;

	sjnProc = *min_element(mProcesses.begin(), mProcesses.end(), shorterJob);

	// run shortest job to completion
	sjnProc->mProgressT = sjnProc->mExeT;

	// update system time to reflect process execution
	sysTime += sjnProc->mExeT;		

	// update process run time
	sjnProc->mRunT = sysTime - sjnProc->mArrivalT;

	cout << "\n\tprocess \'" << sjnProc->mName << "\' finished | " 
		<< "run time: " << sjnProc->mRunT << "\n";
}

// Shortest Remaining Time
void Scheduler::SRT(int& sysTime) {
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
void Scheduler::HRRN(int& sysTime) {
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
	sysTime += hrrProc->mExeT;

	// update process run time
	hrrProc->mRunT = sysTime - hrrProc->mArrivalT;

	cout << "\n\tprocess \'" << hrrProc->mName << "\' finished | " 
		<< "run time: " << hrrProc->mRunT << "\n";
}

// remove finished processes from Scheduler
void Scheduler::clean() {
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

bool Scheduler::shorterJob(Process *p1, Process *p2) {
	return p1->mExeT < p2->mExeT;
}