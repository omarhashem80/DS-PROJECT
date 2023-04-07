#include "Processor.h"
#include"Scheduler.h"
Processor::Processor(Scheduler* ptr): psm(ptr)
{
		Busy = 0;
		Run = NULL;
		Time = 0;
}
void Processor::SendToTerm(Process* Term)
{
	psm->MovetoTerm(Term);
}

void Processor::SendToBlock(Process* BLK)
{
	psm->MovetoBLK(BLK);
}

int Processor::GetTiming()
{
	return Time;
}
