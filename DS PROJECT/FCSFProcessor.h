#pragma once
#include "Processor.h"
#include"LinkedQueue.h"
#include"Scheduler.h"
class FCSFProcessor :public Processor
{
private:
	LinkedQueue<Process*>Ready;
public:
	FCSFProcessor(Scheduler* ptr);
	void SendToReady(Process* );
	void schedule(int Clock);
	void Advance(int);
};




