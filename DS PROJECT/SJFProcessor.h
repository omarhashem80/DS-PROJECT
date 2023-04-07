#pragma once
#include "Processor.h"
#include"PriorityQueue.h"
#include"Pair.h"
class SJFProcessor :public Processor
{
	PriorityQueue<Process*> Ready;   //PriorityQueue sorted by timesteps
public:
	SJFProcessor(Scheduler* ptr);
	void SendToReady(Process* );
	void schedule(int );
	void Advance(int);
};




