#pragma once
#include"Process.h"
class Scheduler;
class Processor
{
protected:
	bool Busy;
	Process* Run;
	int Time;
	Scheduler* psm;
public:
	Processor(Scheduler* ptr);
	bool GetBusy()
	{
		return Busy;
	}
	void SendToTerm(Process* Term);
	void SendToBlock(Process* BLK);
	int GetTiming();
	virtual void SendToReady(Process*) {}
	virtual void schedule(int ) {}
	virtual void Advance(int) {}
};




