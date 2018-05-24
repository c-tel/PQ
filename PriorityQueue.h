#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include <string>
using namespace std;

template<typename Elem>
bool defaultPrior(const Elem& e1, const Elem& e2)
{
	return e1>e2;
}

template<typename Elem, bool (*higherPrior)(const Elem&, const Elem&) = defaultPrior<Elem>>
class PriorityQueue
{
public:
	class BadPQ;
	virtual ~PriorityQueue(){}
	PriorityQueue();
	PriorityQueue& insert(const Elem& el);
	bool empty() const;
	const Elem& top() const;
	PriorityQueue& pop();
	size_t size() const;

protected:
	bool (* const _better)(const Elem&, const Elem&);

private:
	virtual PriorityQueue& do_insert(const Elem&) = 0;
	virtual bool do_empty() const = 0;
	virtual const Elem& do_top() const = 0;
	virtual PriorityQueue& do_pop() = 0;
	virtual size_t do_size() const = 0;
};

template<typename Elem, bool (*higherPrior)(const Elem&, const Elem&)>
class PriorityQueue<Elem, higherPrior>::BadPQ
{
private:
	const string _reason; 
	BadPQ& operator=(const BadPQ&);
public:
	BadPQ(const string& reason="unknown"): _reason(reason){}
	~BadPQ(){};
	void diagnose() const { cerr << _reason << endl;}
};

template<typename Elem, bool (*higherPrior)(const Elem&, const Elem&)>
PriorityQueue<Elem, higherPrior>::PriorityQueue(): _better(higherPrior){}

template<typename Elem, bool (*higherPrior)(const Elem&, const Elem&)>
PriorityQueue<Elem, higherPrior>& PriorityQueue<Elem, higherPrior>::insert(const Elem& el) {return do_insert(el); }

template<typename Elem, bool (*higherPrior)(const Elem&, const Elem&)>
bool PriorityQueue<Elem, higherPrior>::empty() const { return do_empty(); }

template<typename Elem, bool (*higherPrior)(const Elem&, const Elem&)>
size_t PriorityQueue<Elem, higherPrior>::size() const { return do_size(); }

template<typename Elem, bool (*higherPrior)(const Elem&, const Elem&)>
const Elem& PriorityQueue<Elem, higherPrior>::top() const
{
	if(empty())
	{
		BadPQ bpq("Trying to get a top of the empty PQ!");
		throw bpq;
	}
	return do_top();
}

template<typename Elem, bool (*higherPrior)(const Elem&, const Elem&)>
PriorityQueue<Elem, higherPrior>& PriorityQueue<Elem, higherPrior>::pop()
{
	if(empty())
	{
		BadPQ bpq("Trying to remove elem from the empty PQ!");
		throw bpq;
	}
	return do_pop();
}

#endif