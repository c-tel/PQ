#ifndef HEAPPQ_H
#define HEAPPQ_H

#include "Array.h"
#include "PriorityQueue.h"

template <typename Elem, bool (* higherPrior)(const Elem&, const Elem&)=defaultPrior<Elem>>
class HeapPQ: public PriorityQueue<Elem, higherPrior>
{
public:
	HeapPQ(size_t size = 4);
	~HeapPQ();

private:
	size_t _n;
	Array<Elem> * _heap;
	void swap(size_t, size_t);
	void sink(size_t);
	void swim(size_t);
	void resize(size_t);

	bool do_empty() const;
	HeapPQ& do_insert(const Elem&);
	const Elem& do_top() const;
	HeapPQ& do_pop();
	size_t do_size() const;
};

template <typename Elem, bool (* higherPrior)(const Elem&, const Elem&)>
HeapPQ<Elem, higherPrior>::HeapPQ(size_t size): _n(0), _heap(new Array<Elem>(size+1)){}

template <typename Elem, bool (* higherPrior)(const Elem&, const Elem&)>
HeapPQ<Elem, higherPrior>::~HeapPQ() { delete _heap; }

template <typename Elem, bool (* higherPrior)(const Elem&, const Elem&)>
void HeapPQ<Elem, higherPrior>::swap(size_t i, size_t j)
{
	Elem buf = (*_heap)[i];
	(*_heap)[i] = (*_heap)[j];
	(*_heap)[j] = buf;
}

template <typename Elem, bool (* higherPrior)(const Elem&, const Elem&)>
void HeapPQ<Elem, higherPrior>::sink(size_t i)
{
	while (2*i <= _n) {
		size_t child = 2*i;
		if (child < _n && higherPrior((*_heap)[child+1], (*_heap)[child])) 
			++child;
		if (higherPrior((*_heap)[i], (*_heap)[child])) break;
		swap(i, child);
		i = child;
	}
}

template <typename Elem, bool (* higherPrior)(const Elem&, const Elem&)>
void HeapPQ<Elem, higherPrior>::swim(size_t i)
{
	while (i > 1 && higherPrior((*_heap)[i], (*_heap)[i/2])) {
		swap(i/2, i);
		i /= 2;
	}
}

template<typename Elem, bool (*higherPrior)(const Elem&, const Elem&)>
size_t HeapPQ<Elem, higherPrior>::do_size() const
{
	return _n;
}

template <typename Elem, bool (* higherPrior)(const Elem&, const Elem&)>
bool HeapPQ<Elem, higherPrior>::do_empty() const
{
	return size() == 0;
}

template <typename Elem, bool (* higherPrior)(const Elem&, const Elem&)>
HeapPQ<Elem, higherPrior>& HeapPQ<Elem, higherPrior>::do_insert(const Elem& e)
{
	if(_n == (*_heap).size()-1)
		resize((*_heap).size()*2 + 1);
	(*_heap)[++_n] = e;
    swim(_n);

	return *this;
}

template <typename Elem, bool (* higherPrior)(const Elem&, const Elem&)>
const Elem& HeapPQ<Elem, higherPrior>::do_top() const
{
	return (*_heap)[1];
}

template <typename Elem, bool (* higherPrior)(const Elem&, const Elem&)>
HeapPQ<Elem, higherPrior>& HeapPQ<Elem, higherPrior>::do_pop()
{
	swap(1, _n--);
    sink(1);
	if(_n <= (*_heap).size()/4)
		resize((*_heap).size()/2);

	return *this;
}

template <typename Elem, bool (*higherPrior)(const Elem&, const Elem&)>
void HeapPQ<Elem, higherPrior>::resize(size_t capacity)
{
	Array<Elem> * new_heap = new Array<Elem>(capacity);
	for(size_t i = 1; i<=_n; ++i)
	{
		(*new_heap)[i] = (*_heap)[i];
	}
	delete _heap;
	_heap = new_heap;
}

#endif