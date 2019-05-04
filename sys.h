///////////////////////////////////////////////////////////////////////////////
// sys.h
// @desc: Sys class header file
///////////////////////////////////////////////////////////////////////////////

#pragma once

#include <iostream>
#include "scheduler.h"

#ifndef SYS_H
#define SYS_H

class Sys
{
public:
	Scheduler* mScheduler;			// system's Scheduler
	vector <Process> mProcesses;	// process job list read in at start 
	
	int mQuantum;	// time units for process execution before rescheduling 
	int mSchedSel;	// scheduling algorithm selection
	int mTime;		// current system time

	Sys() { mTime = 0; mQuantum = 1; } // initiliaze run time = 0

	void schedule();		// add newly arrived processes from job list to Scheduler
	bool jobsFinished();	// return true if all processes in job list are finished
	void printProgress();	// print progress of all processes on Scheduler
};

#endif