#pragma once
#include"Processor.h"
#include"FCSFProcessor.h"
#include"RRProcessor.h"
#include"SJFProcessor.h"                                //NOTE:for test only not the requested
#include"LinkedQueue.h"                                 //WARNING: NOT CHANGE ANYTHING IN INCLUDING 
#include"Process.h"
class Processor;
class Scheduler
{
private:
    Processor* PRL[3];  // list of processors           array for test in my opinion the array is the best choice WE DON'T NEED DELETE ONLY ARRAY OF POINTERS
	LinkedQueue<Process*>New;   //New processes         //PIRORITY QUEUE WITH RESPECT TO TYPE OF PROCESS
	LinkedQueue<Process*>BLK;   //processes requested i/o
	LinkedQueue<Process*>TERM;  //Terminated processes
	int Clock;                  // TO USE IN CALCULATIONS
public:
	Scheduler();
	void preprocessing();
	void advance();
	void AdvanceBLK();
	bool MovetoReady(Process*);
	bool MovetoTerm(Process*);
	bool MovetoBLK(Process*);
	void StealWork();
	void Loading();
	void Statistics();
	~Scheduler();
};