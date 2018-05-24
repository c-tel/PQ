#ifndef ORDEREDPQ_H
#define ORDEREDPQ_H

#include "PriorityQueue.h"
#include "Array.h"

template <typename Elem, bool (*higherPrior)(const Elem&, const Elem&) = defaultPrior<Elem>>
class OrderedPQ: public PriorityQueue<Elem, higherPrior>
{
public:
	OrderedPQ(size_t size = 4);
	~OrderedPQ();
private:
	size_t _head;
	size_t _tail;
	size_t _size;
	Array<Elem> * _queue;
	void resize(size_t);
	void normalize();
	size_t move(size_t);
	size_t back(size_t);

	OrderedPQ& do_insert(const Elem&);
	bool do_empty() const;
	const Elem& do_top() const;
	OrderedPQ& do_pop();
	size_t do_size() const;
};

template <typename Elem, bool (*higherPrior)(const Elem&, const Elem&)>
OrderedPQ<Elem, higherPrior>::OrderedPQ(size_t size): PriorityQueue(), _head(0), _tail(0), _size(0), _queue(new Array<Elem>(size)) {}

template <typename Elem, bool (*higherPrior)(const Elem&, const Elem&)>
OrderedPQ<Elem, higherPrior>::~OrderedPQ(){ delete _queue; }

template <typename Elem, bool (*higherPrior)(const Elem&, const Elem&)>
OrderedPQ<Elem, higherPrior>& OrderedPQ<Elem, higherPrior>::do_insert(const Elem& e)
{
	if(size() == (*_queue).size())
		resize((*_queue).size()*2 + 1);
	(*_queue)[_tail] = e;
	_tail = move(_tail);
	++_size;
	normalize();
	
	return *this;
}

template <typename Elem, bool (*higherPrior)(const Elem&, const Elem&)>
const Elem& OrderedPQ<Elem, higherPrior>::do_top() const
{
	return (*_queue)[_head];
}

template<typename Elem, bool (*higherPrior)(const Elem&, const Elem&)>
size_t OrderedPQ<Elem, higherPrior>::do_size() const
{
	return _size;
}

template <typename Elem, bool (*higherPrior)(const Elem&, const Elem&)>
bool OrderedPQ<Elem, higherPrior>::do_empty() const
{
	return size()==0;
}

template <typename Elem, bool (*higherPrior)(const Elem&, const Elem&)>
OrderedPQ<Elem, higherPrior>& OrderedPQ<Elem, higherPrior>::do_pop()
{
	_head = move(_head); 
	--_size;
	if(size() <= (*_queue).size()/4)
		resize((*_queue).size()/2);

	return *this;
}

template <typename Elem, bool (*higherPrior)(const Elem&, const Elem&)>
size_t OrderedPQ<Elem, higherPrior>::move(size_t pos)
{
	return (pos != (*_queue).size()-1) ? pos+1 : 0;
}

template <typename Elem, bool (*higherPrior)(const Elem&, const Elem&)>
size_t OrderedPQ<Elem, higherPrior>::back(size_t pos)
{
	return (pos != 0) ? pos-1 : (*_queue).size()-1;
}

template <typename Elem, bool (*higherPrior)(const Elem&, const Elem&)>
void OrderedPQ<Elem, higherPrior>::normalize()
{
	size_t i = back(_tail);
	while(i!=_head && _better((*_queue)[i], (*_queue)[back(i)]))
	{
		Elem buf = (*_queue)[i];
		(*_queue)[i] = (*_queue)[back(i)];
		(*_queue)[back(i)] = buf;
		i = back(i);
	}
}

template <typename Elem, bool (*higherPrior)(const Elem&, const Elem&)>
void OrderedPQ<Elem, higherPrior>::resize(size_t capacity)
{
	Array<Elem> * new_queue = new Array<Elem>(capacity);
	int bound = (*_queue).size();
	for (size_t i = 0; i < size(); i++) 
		(*new_queue)[i] = (*_queue)[(_head+i) % bound];
	delete _queue;
	_queue = new_queue;
	_head = 0;
	_tail = _size;
}

#endif