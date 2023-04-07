#include "Scheduler.h"
#include<iostream>
Scheduler::Scheduler()
{
	/*Clock = 0;
	Process*p1=new Process(1,1,5,0,0);
	Process*p2=new Process(1, 2, 5, 0, 0);
	Process*p3=new Process(1, 3, 1, 0, 0);
	Process*p4=new Process(1, 4, 2, 0, 0);
	Process*p5=new Process(1, 5, 4, 0, 0);
	Process*p6=new Process(1, 6, 6, 0, 0);
	New.enqueue(p1);
	New.enqueue(p2);
	New.enqueue(p3);
	New.enqueue(p4);
	New.enqueue(p5);
	New.enqueue(p6);
	FCSFProcessor f(this);
	RRProcessor d(this);
	SJFProcessor s(this);
	f.SendToReady(p1);
	f.SendToReady(p3);
	d.SendToReady(p2);
	d.SendToReady(p6);
	s.SendToReady(p4);
	s.SendToReady(p5);
	PRL[0] = &f;
	PRL[1] = &d;
	PRL[2] = &s;*/
}

void Scheduler::preprocessing()
{
	
}

void Scheduler::advance()
{
	Clock++;
	Process* p1 = new Process(1, 1, 7, 1, 0);
	p1->iooperin({ 2,5 });
	Process* p2 = new Process(1, 2, 5, 0, 0);
	Process* p3 = new Process(1, 3, 1, 0, 0);
	Process* p4 = new Process(1, 4, 2, 0, 0);
	Process* p5 = new Process(1, 5, 4, 0, 0);
	Process* p6 = new Process(1, 6, 6, 0, 0);
	New.enqueue(p1);
	New.enqueue(p2);
	New.enqueue(p3);
	New.enqueue(p4);
	New.enqueue(p5);
	New.enqueue(p6);
	FCSFProcessor f(this);
	RRProcessor d(this);
	SJFProcessor s(this);
	f.SendToReady(p1);
	f.SendToReady(p3);
	d.SendToReady(p2);
	d.SendToReady(p6);
	s.SendToReady(p4);
	s.SendToReady(p5);
	Processor* ab = &f;
	PRL[0] = ab;
	ab = &d;
	PRL[1] = ab;
	ab = &s;
	PRL[2] = ab;
	for (int i = 0;f.GetTiming()+!BLK.isEmpty()/*+s.GetTiming()+s.GetTiming()*/>0; i++)
	{
		if (i > 2)
		{
			i = 0;
			Clock++;
		}
		/*f.schedule(Clock);*/
		PRL[0]->schedule(Clock);
		Clock++;
		AdvanceBLK();
	}

	
	//MovetoReady();
}
void Scheduler::AdvanceBLK()
{
	Process* P;
	if (!BLK.isEmpty())
	{
		BLK.peek(P);
		P->incrementadvance();
		if (P->GetIOD())
		{
			BLK.dequeue(P);
			MovetoReady(P);
			cout << "GOTOREADY\n";
		}
		cout << "INBLK\n";
	}
}

bool Scheduler::MovetoReady(Process* p)
{
	p->setRT(Clock);
	PRL[0]->SendToReady(p);
	cout << "INREADY\n";
	return true;
}
bool Scheduler::MovetoTerm(Process* p)
{
	cout << "INTERM\n";
	p->setTT(Clock);
	return TERM.enqueue(p);
}

bool Scheduler::MovetoBLK(Process* p)
{
	cout << "MOVETOBLOCK\n";
	return BLK.enqueue(p);
}

void Scheduler::StealWork()
{
	cout << "steal\n";
}

void Scheduler::Loading()
{
}

void Scheduler::Statistics()
{
}

Scheduler::~Scheduler()
{
	while (!TERM.isEmpty())
	{
		Process* temp;
		TERM.dequeue(temp);
		temp->print();
	}
}
