///////////////////////////////////////////////////////////////////////////////
// main.cpp
// @desc: simulate a variety of scheduling algorithms given a job list of
//		  processes to execute
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <sstream>
#include <fstream>

#include "sys.h"
#include "scheduler.h"

vector<string> readProcFile(string filename);
vector<Process> spawnProcs(vector<string> procData);
int selectScheduler();
int setQuantum();
vector<string> parse(string str, char delim = ' ');

int main(int argc, char** argv)
{
	if(argc < 2) {
		cout << "Please specify a file on the command line." << endl;
		exit(1);
	}
	string filename = argv[1];
	vector<string> procData;
	
	procData = readProcFile(filename);

	// spawn processes from input file's process data
	vector<Process> processes = spawnProcs(procData);

	// initialize Scheduler
	Scheduler SystemScheduler;
	Scheduler* scheduler = &SystemScheduler;

	// initalize System with Scheduler and process job list 
	Sys System;
	Sys* sys = &System;
	sys->mScheduler = scheduler;
	sys->mProcesses = processes;

	// select System scheduling algorithm
	sys->mSchedSel = selectScheduler();

	// set System scheduling quantum for Round Robin and initialize count
	if (sys->mSchedSel == 4)
		sys->mQuantum = setQuantum();

	int rrCount = 0;

	// true if all processes in job list are finished
	bool finished = false;

	// TODO: rework logic to run every time slice instead of once per quantum
	// run processes until all jobs finished
	while (!finished)
	{
		// check for newly arrived processes and add them to Scheduler
		sys->schedule();

		// clean finished processes from Scheduler
		sys->mScheduler->clean();

		///* execute processes according to selected scheduling algorithm *///	
		// First Come - First Serve
		//if (sys->mSchedSel == 1)
			//sys->mScheduler->FCFS(sys->mQuantum, sys->mTime);

		//// Shortest Job Next
		if (sys->mSchedSel == 2)
			sys->mScheduler->SJN(sys->mTime);

		// Shortest Remaining Time
		else if (sys->mSchedSel == 3)
			sys->mScheduler->SRT(sys->mTime);

		// Round Robin
		else if (sys->mSchedSel == 4)
			sys->mScheduler->RR(sys->mQuantum, sys->mTime, rrCount);

		// Highest Response Ratio Next
		else if (sys->mSchedSel == 5)
			sys->mScheduler->HRRN(sys->mTime);

		// display process progress
		sys->printProgress();

		// mark completed processes as finished and check if all done
		finished = sys->jobsFinished();
	} 

	return 0;
}

// read process data input file line-by-line
// return: string vector of each line in file
vector<string> readProcFile(string filename)
{
	ifstream file;
	file.open(filename);
	// TODO: if (!file.is_open()) 

	string line;
	vector<string> procData;
	while (getline(file, line))
		procData.push_back(line);

	return procData;
}

// convert process data read from input file to Process objects
// return: Process vector of processes to be scheduled
vector<Process> spawnProcs(vector<string> procData)
{
	vector<Process> procs;

	// for each line read into procData, spawn new process
	for (int i = 0; i < procData.size(); i++)
	{
		vector<string> process = parse(procData[i]);

		Process newProc;
		newProc.mName		= process[0];
		newProc.mArrivalT	= stoi(process[1]);
		newProc.mExeT		= stoi(process[2]);

		procs.push_back(newProc);
	}

	return procs;
}

// prompt user to select a scheduling algorithm
// return: integer scheduler selection
int selectScheduler()
{
	cout << "\nSelect a scheduling algorithm:\n";
	cout << "1: First Come - First Serve\n";
	cout << "2: Shortest Job Next\n";
	cout << "3: Shortest Remaining Time\n";
	cout << "4: Round Robin\n";
	cout << "5: Highest Response Ratio Next\n";

	int schedSel = -1;
	while (schedSel < 1 || schedSel > 5)
	{
		cout << "\nEnter scheduler selection # : ";
		cin >> schedSel;

		// TODO : catch string input error
		//while (cin.fail())
		//{
		//	cout << "dbg\n";
		//	cin.clear();
		//	cin.ignore();
		//}

		if (schedSel < 1 || schedSel > 5)
			cout << "invalid selection number\n";
	}

	return schedSel;
}

// prompt user to set a scheduling quantum
// return: integer scheduler selection
int setQuantum()
{
	int quantum = -1;
	while (quantum < 1)
	{
		cout << "Set scheduling quantum : ";
		cin >> quantum;

		// TODO : catch string input error
		//while (cin.fail())
		//{
		//	cout << "dbg\n";
		//	cin.clear();
		//	cin.ignore();
		//}

		if (quantum < 1)
			cout << "invalid scheduling quantum\n";
	}

	return quantum;
}

// parse argument string str into substrings using specified delimiter
// return: string vector of str's substrings
vector<string> parse(string str, char delim)
{
	vector<string> ret;
	stringstream sStream(str);
	string substr;

	while (getline(sStream, substr, delim))
		ret.push_back(substr);

	return ret;
}