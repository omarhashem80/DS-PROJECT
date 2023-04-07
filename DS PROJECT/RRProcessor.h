#pragma once
#include"LinkedQueue.h"
#include"Processor.h"
class RRProcessor : public Processor
{
private:
	LinkedQueue<Process*>Ready;
	int Slicetime;
public:
	RRProcessor(Scheduler* );
	void SendToReady(Process* );
	void schedule(int);
	void Advance(int);
};




