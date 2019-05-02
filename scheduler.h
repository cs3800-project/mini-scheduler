///////////////////////////////////////////////////////////////////////////////
// Scheduler.h
// @desc: Scheduler class header file
///////////////////////////////////////////////////////////////////////////////

#pragma once

#ifndef SCHEDULER_H
#define SCHEDULER_H	

#include "process.h"
#include <vector>
#include <climits>
#include <iostream>

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

#endif