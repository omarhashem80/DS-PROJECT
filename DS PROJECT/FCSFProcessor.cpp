#include "FCSFProcessor.h"
#include<iostream>
using namespace std;
FCSFProcessor::FCSFProcessor(Scheduler* ptr) :Processor(ptr)
{
	
}
void FCSFProcessor::SendToReady(Process* ptr)
{
	Time += ptr->getCT();
	Ready.enqueue(ptr);
}

void FCSFProcessor::schedule(int Clock)
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
		int R = rand()%100;
		if (R <= 15&&R>=1)
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

void FCSFProcessor::Advance(int Clock)
{
	if (!(Ready.isEmpty()) || Run)                                     // check if the ready list is empty or not same for Run if not empty or run refer to sth 
	{
		if (!Busy)                                                     //check if the processor is busy if not make run refer  
		{                                                              //the next process   
			Ready.dequeue(Run);
			Busy = 1;												  
		}
		Run->incrementadvance();
		if (Run->getCT() != Run->getAdvance())						  // check if the process is end if not 
		{
			if ((Run->Gotoblock()))                                   // check if the process ask for IO if send it to Block and take the next one		
			{														  	
				Time -= Run->getCT() - Run->getAdvance();             //decrease the Time load of the processor by the remaining steps
				SendToBlock(Run);
				Run = 0;
				Ready.dequeue(Run);
			}
			else                                                      // if it doesn't ask for IO decrease the Time Load by one step
				Time--;
		}															  
		else                                                          // if the process is end send it to term list and take the next
		{															
			SendToTerm(Run);
			Run = 0;
			Ready.dequeue(Run);
			Time--;
		}
	}
	else                                                             // if the processing is end, set the Busy = 0
	{
		Busy = 0;
		Time = 0;
	}
	cout <<"FCSF: The Time: "<<Time<<endl;
	cout << "FCSF: The Clock: " << Clock << endl;
}																	
