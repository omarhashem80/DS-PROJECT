#ifndef PRIORITY_QUEUE_
#define PRIORITY_QUEUE_
#include"Node.h"
#include"Pair.h"
template <class T>
class PriorityQueue
{
private:
	Node<T>* backPtr;
	Node<T>* frontPtr;
	bool InsertSorted(const T& val)
	{
		Node<T>* f = new Node<T>(val);
		if (!frontPtr)
		{
			frontPtr = f;
			return true;
		}
		Node<T>* p = frontPtr;
		Node<T>* n = frontPtr->getNext();
		if (!(frontPtr->getNext()))
		{
			if (p->getItem() <= val)
			{
				p->setNext(f);
				f->setNext(0);
				return true;
			}
			if (p->getItem() >= val)
			{
				f->setNext(p);
				frontPtr = f;
				return true;
			}
		}
		while (n)
		{
			if (p->getItem() <= val && val <= n->getItem())
			{
				p->setNext(f);
				f->setNext(n);
				return true;
			}
			else if (val <= p->getItem())
			{
				f->setNext(p);
				frontPtr = f;
				return true;
			}
			p = n;
			n = n->getNext();
		}
		if (!n && p->getItem() <= val)
		{
			p->setNext(f);
			f->setNext(0);
			return true;
		}
		return false;
	}

public:
	PriorityQueue()
	{
		backPtr = nullptr;
		frontPtr = nullptr;
	}
	bool isEmpty() const
	{
		return (frontPtr == nullptr);
	}
	bool enqueue(const T& newEntry)
	{
		InsertSorted(newEntry);
		Node<T>* p = frontPtr;
		while (p->getNext())
			p = p->getNext();
		backPtr = p;
		return true;
	}
	bool dequeue(T& frntEntry)
	{
		if (isEmpty())
			return false;

		Node<T>* nodeToDeletePtr = frontPtr;
		frntEntry = frontPtr->getItem();
		frontPtr = frontPtr->getNext();
		// Queue is not empty; remove front
		if (nodeToDeletePtr == backPtr)	 // Special case: last node in the queue
			backPtr = nullptr;

		// Free memory reserved for the dequeued node
		//delete nodeToDeletePtr;

		return true;
	}
	bool peek(T& frntEntry)  const
	{
		if (isEmpty())
			return false;

		frntEntry = frontPtr->getItem();
		return true;
	}
	~PriorityQueue()
	{
		T temp;

		//Free (Dequeue) all nodes in the queue
		while (dequeue(temp));
	}
	//copy constructor
	PriorityQueue(const PriorityQueue& PLQ)
	{
		Node<T>* NodePtr = PLQ.frontPtr;
		if (!NodePtr) //PLQ is empty
		{
			frontPtr = backPtr = nullptr;
			return;
		}

		//insert the first node
		Node<T>* ptr = new Node<T>(NodePtr->getItem());
		frontPtr = backPtr = ptr;
		NodePtr = NodePtr->getNext();

		//insert remaining nodes
		while (NodePtr)
		{
			Node<T>* ptr = new Node<T>(NodePtr->getItem());
			backPtr->setNext(ptr);
			backPtr = ptr;
			NodePtr = NodePtr->getNext();
		}
	}
};

#endif

