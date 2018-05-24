#ifndef UNORDEREDPQ_H
#define UNORDEREDPQ_H

#include "PriorityQueue.h"
#include "Array.h"

template <typename Elem, bool (*higherPrior)(const Elem&, const Elem&) = defaultPrior<Elem>>
class UnorderedPQ: public PriorityQueue<Elem, higherPrior>
{
public:
	UnorderedPQ(size_t size=4);
	~UnorderedPQ();
private:
	UnorderedPQ& do_insert(const Elem&);
	bool do_empty() const;
	const Elem& do_top() const;
	UnorderedPQ& do_pop();
	size_t do_size() const;

	void resize(size_t);
	size_t _size;
	Array<Elem> * _queue;
};

template <typename Elem, bool (*higherPrior)(const Elem&, const Elem&)>
UnorderedPQ<Elem, higherPrior>::UnorderedPQ(size_t size): PriorityQueue(), _queue(new Array<Elem>(size)), _size(0){}

template <typename Elem, bool (*higherPrior)(const Elem&, const Elem&)>
UnorderedPQ<Elem, higherPrior>::~UnorderedPQ() { delete _queue; }

template<typename Elem, bool (*higherPrior)(const Elem&, const Elem&)>
size_t UnorderedPQ<Elem, higherPrior>::do_size() const { return _size; }

template <typename Elem, bool (*higherPrior)(const Elem&, const Elem&)>
bool UnorderedPQ<Elem, higherPrior>::do_empty() const { return size() == 0; }

template <typename Elem, bool (*higherPrior)(const Elem&, const Elem&)>
UnorderedPQ<Elem, higherPrior>& UnorderedPQ<Elem, higherPrior>::do_insert(const Elem& e)
{
	if(size() == (*_queue).size())
		resize((*_queue).size()*2 + 1);
	(*_queue)[_size++] = e;
	
	return *this;
}

template <typename Elem, bool (*higherPrior)(const Elem&, const Elem&)>
const Elem& UnorderedPQ<Elem, higherPrior>::do_top() const
{
	int max = 0;
	for(size_t i = 0; i<size(); ++i)
	{
		if(_better((*_queue)[i], (*_queue)[max]))
			max = i;
	}
	return (*_queue)[max];
}

template <typename Elem, bool (*higherPrior)(const Elem&, const Elem&)>
UnorderedPQ<Elem, higherPrior>& UnorderedPQ<Elem, higherPrior>::do_pop() 
{
	int max = 0;
	for(size_t i = 0; i<size(); ++i)
	{
		if(_better((*_queue)[i], (*_queue)[max]))
			max = i;
	}
	(*_queue)[max] = (*_queue)[--_size];
	if(size() <= (*_queue).size()/4)
		resize((*_queue).size()/2);
	
	return *this;
}

template <typename Elem, bool (*higherPrior)(const Elem&, const Elem&)>
void UnorderedPQ<Elem, higherPrior>::resize(size_t capacity)
{
	Array<Elem> * new_queue = new Array<Elem>(capacity);
	for(size_t i = 0; i<size(); ++i)
	{
		(*new_queue)[i] = (*_queue)[i];
	}
	delete _queue;
	_queue = new_queue;
}

#endif;