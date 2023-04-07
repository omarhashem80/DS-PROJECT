#include "Process.h"
#include<iostream>
using namespace std;
Process::Process(int a, int b, int c, int d, bool e)
{
	AT = a;
	PID = b;
	CT = c;
	N = d;
	User = e;
	TT = 0;
	RT = 0;
	Advance = 0;
}

Process::Process(Process&p)
{
	AT = p.AT;
	PID = p.PID;
	CT = p.CT;
	N = p.N;
	TT = p.TT;
	RT = p.RT;
	User = p.User;
	Advance = p.Advance;
	Pair<int, int>pt;
	for (int i = 0; i < N; i++)
	{
		IOoper.dequeue(pt);
		p.IOoper.enqueue(pt);
		IOoper.enqueue(pt);
	}
}
bool Process::iooperin(const Pair<int, int>& p)
{
	return IOoper.enqueue(p);
}

bool Process::iooperout()
{
	Pair<int, int>p;
	return IOoper.dequeue(p);
}

bool Process::Gotoblock()
{
	Pair<int, int>p;
	IOoper.peek(p);
	return Advance == p.getfirst();
}
bool Process::GetIOD()
{
	Pair<int, int>p;
	IOoper.peek(p);
	return Advance==p.getfirst()+p.getsecond()-1;
}
int Process::GetIO()
{
	Pair<int, int>p;
	IOoper.peek(p);
	return p.getsecond();
}
void Process::incrementadvance()
{
	Advance++;
}

void Process::setTT(int t)
{
	TT = t;
}

void Process::setRT(int t)
{
	if(!RT)
	  RT = t;
}

int Process::getAT()
{
	return AT;
}

int Process::getPID()
{
	return PID;
}

int Process::getCT()
{
	return CT;
}

int Process::getN()
{
	return N;
}

int Process::getTT()
{
	return TT;
}

int Process::getRT()
{
	return RT;
}

int Process::getAdvance()
{
	return Advance;
}

int Process::getTRT()
{
	return TT - AT;
}

int Process::getWT()
{
	int WT = getTRT() - CT;
	return WT;
}

bool Process::isUser()
{
	return User;
}
bool Process::operator==(Process& P)
{
	return(CT == P.CT && User == P.User);
}

bool Process::operator>(Process& P)
{
	if (User < P.User)
		return true;
	else if (User > P.User)
		return false;
	else if (User == P.User)
		return CT > P.CT;
}

bool Process::operator<(Process& P)
{
	if (User > P.User)
		return true;
	else if (User < P.User)
		return false;
	else if (User == P.User)
		return CT < P.CT;
}

bool Process::operator>=(Process& P)
{
	return *this > P && *this == P;
}

bool Process::operator<=(Process& P)
{
	return *this < P && *this == P;
}
void Process::print()
{
	cout << TT << "  " << PID << "  " << AT << "  " << CT;
	while (!IOoper.isEmpty())
	{
		Pair<int, int> temp;
		IOoper.dequeue(temp);
		cout << "  " << temp.getsecond();
	}
	cout <<"  "<< getWT() << "  " << RT << "  " << getTRT() <<endl;
}
Process::~Process()
{
	if (child)
		child->~Process();
}