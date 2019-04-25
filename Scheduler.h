///////////////////////////////////////////////////////////////////////////////
// Scheduler.h
// @desc: Scheduler class header file
///////////////////////////////////////////////////////////////////////////////

#pragma once

#ifndef SCHEDULER_H
#define SCHEDULER_H	

#include "Process.h"
#include <vector>
#include <climits>

class Scheduler
{
public:
	vector <Process*> mProcesses; // processes to be scheduled

	void clean();	// remove all finished processes from Scheduler

	void FCFS(const int quantum, const int time);	// First-Come, First-Serve scheduling 
	void RR(const int quantum, const int time);		// Round Robin scheduling 
	void SJN(const int quantum, const int time);	// Shortest Job Next scheduling 
	void SRT(const int quantum, const int time);	// Shortest Remaining Time scheduling 
	void HRRN(const int quantum, const int time);	// Highest Response Ratio Next scheduling 
};

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

#endif