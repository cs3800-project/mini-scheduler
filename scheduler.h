///////////////////////////////////////////////////////////////////////////////
// scheduler.h
// @desc: Scheduler class header file
///////////////////////////////////////////////////////////////////////////////

#pragma once

#ifndef SCHEDULER_H
#define SCHEDULER_H	

#include "process.h"
#include <vector>
#include <climits>
#include <iostream>
#include <algorithm>

class Scheduler
{
public:
	vector <Process*> mProcesses; // processes to be scheduled

	void clean();	// remove all finished processes from Scheduler

	void FCFS(int& sysTime); // First-Come, First-Serve scheduling 
	void RR(const int quantum, int& sysTime, int& count); // Round Robin scheduling 
	void SJN(int& sysTime);	// Shortest Job Next scheduling
	void SRT(int& sysTime);	// Shortest Remaining Time scheduling 
	void HRRN(int& sysTime); // Highest Response Ratio Next scheduling 

	static bool earlierJob(Process *p1, Process *p2);
	static bool shorterJob(Process *p1, Process *p2);
};

#endif