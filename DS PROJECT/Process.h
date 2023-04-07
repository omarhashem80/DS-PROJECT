#pragma once
#include"Pair.h"
#include"LinkedQueue.h"

class Process
{
private:
	int AT;        //arrival time
	int PID;       //id
	int CT;        //cpu time
	int N;         // # of pairs which request i/o
	int TT;        // time of termination
	int RT;        // response time
	bool User;     // system or user
	int Advance;   // # of achieved steps
	LinkedQueue<Pair<int, int>>IOoper;   //queue of pairs which request I/O
	Process* child;  //for Fork
public:
	Process(int at=0, int pid=0, int ct=0, int n=0, bool user=0);
	Process(Process&);
	bool iooperin(const Pair<int, int>& );
	bool iooperout();
	bool Gotoblock();
	bool GetIOD();
	void incrementadvance();
	void setTT(int);
	void setRT(int);
	int GetIO();
	int getAT();
	int getPID();
	int getCT();
	int getN();
	int getTT();
	int getRT();
	int getAdvance();
	int getTRT();
	int getWT();
	bool isUser();
	bool operator==(Process& P);   // if the first process is sys and the second is user the greater will be the first
	bool operator>(Process& P);    // if they have the same type which one has the greater CT will be the greater 
	bool operator<(Process& P);
	bool operator>=(Process& P);
	bool operator<=(Process& P);
	void print();
	~Process();
};


