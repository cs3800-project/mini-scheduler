///////////////////////////////////////////////////////////////////////////////
// Process.h
// @desc: Process class header file
///////////////////////////////////////////////////////////////////////////////

#pragma once

#ifndef PROCESS_H
#define PROCESS_H	

#include <string>

using namespace std;

struct Process
{
public:
	string mName;	// process name
	bool mFinished;	// true if done executing, false otherwise
	bool mScheduled; // true if process has been added to scheduler
	int mArrivalT;	// scheduled arrival time
	int mStartT;	// start time ???
	int mExeT;		// time needed to execute
	int mProgressT;	// cumulative time spent executing 
	int mRunT;		// total run time
	int mEndT;		// end time

	Process() { mRunT = 0; mProgressT = 0; 
				mFinished = false; mScheduled = false; }
};

#endif