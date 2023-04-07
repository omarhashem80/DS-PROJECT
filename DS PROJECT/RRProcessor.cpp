#include "RRProcessor.h"
#include<iostream>
using namespace std;
RRProcessor::RRProcessor(Scheduler*ptr):Processor(ptr)
{}

void RRProcessor::SendToReady(Process* ptr)        //take process and put into ready list and increase the time load;
{
	Time += ptr->getCT();
	Ready.enqueue(ptr);
}

void RRProcessor::schedule(int Clock)
{
	cout << "FCSF: The Time: " << Time << endl;
	cout << "FCSF: The Clock: " << Clock << endl;
	if (!(Ready.isEmpty()) || Run)
	{
		if (!Busy)
		{
			Ready.dequeue(Run);
			Busy = 1;
		}
		int R = rand() % 100;
		if (R <= 15 && R >= 1)
		{
			Time -= Run->getCT() - Run->getAdvance();
			SendToBlock(Run);
			Run = 0;
			Ready.dequeue(Run);
		}
		else if (R <= 30 && R >= 20)
		{
			Process* Temp = 0;
			Ready.dequeue(Temp);
			SendToReady(Temp);
			Ready.peek(Run);
		}
		else if (R <= 60 && R >= 50)
		{
			SendToTerm(Run);
			Run = 0;
			Ready.dequeue(Run);
			Time--;
		}
		else
		{
			Run->incrementadvance();
			Time--;
		}
	}
	else
	{
		Busy = 0;
		Time = 0;
	}
}

void RRProcessor::Advance(int Clock)
{												          
	if (!(Ready.isEmpty())||Run)                              // check if the ready list is empty or not same for Run if not empty or run refer to sth                       
	{                                                         //check if the processor is busy if not make run refer 
		if (!Busy)					                          //the next process
			Ready.dequeue(Run);					          
		Run->incrementadvance();				          
		if (Run->getCT() != Run->getAdvance())               // check if the process is end if not
		{										          
			if (Run->getAdvance() == Slicetime)              // check if the process reach to slice time if happen 
			{									          
				SendToReady(Run);                         // send it to ready list and take the next one
				Ready.dequeue(Run);
				//Time -= Run->getCT() - Run->getAdvance();  //decrease the Time load of the processor (((((not sure)))))
			}
			if ((Run->Gotoblock()))                          // check if the process ask for IO if send it to Block and take the next one
			{
				Time -= Run->getCT() - Run->getAdvance();    //decrease the Time load of the processor by the remaining steps
				SendToBlock(Run);
				Ready.dequeue(Run);
			}
			else
				Time--;                                     // if it doesn't ask for IO decrease the Time Load by one step
		}
		else                                                // if the process is end send it to term list and take the next
		{

			SendToTerm(Run);
			Ready.dequeue(Run);
			Time--;
		}
	}
	else
	{
		Busy = 0;
		Time = 0;
	}                                          // if the processing is end, set the Busy =0
	cout << "RR: The Time: " << Time << endl;
	cout << "RR: The Clock: " << Clock << endl;
}
