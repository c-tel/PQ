//developed by Stanislal Telizhenko
//on 2018.03.31

#ifndef ARRAY_H
#define ARRAY_H

#include <iostream>
using namespace std;
template <typename Elem>
class Array {
public:
	class BadArray; 
	explicit Array(size_t); 
	~Array();
	Elem& operator[](const size_t index);
	const Elem& operator[](const size_t index) const; 
	size_t size() const;
private:
	const size_t _size;
	Elem* const _allocator;
	Array(const Array&); 
	Array& operator=(const Array&);
};

template <typename Elem>
class Array<Elem>::BadArray
{
private:
	const string _reason; 
	size_t _index; 
	BadArray& operator=(const BadArray&);
public:
	BadArray(string reason="", const size_t index=0): _reason(reason), _index(index){}
	~BadArray(){};
	ostream& diagnose(ostream&) const { return os << reason << ' ' << index;}
};

template <typename Elem>
Array<Elem>::Array(const size_t sz): _size(sz), _allocator(new Elem[_size]){}

template <typename Elem>
Array<Elem>::~Array() {delete [] _allocator;}

template <typename Elem>
Elem& Array<Elem>::operator[](const size_t index) {
	if(index>=_size)
		throw BadArray("Bad index: ", index);
	return _allocator[index];
}

template <typename Elem>
const Elem& Array<Elem>::operator[](const size_t index) const {
	if(index>=_size)
		throw BadArray("Bad index: ", index);
	return _allocator[index];
}

template <typename Elem>
size_t Array<Elem>::size() const
{
	return _size;
}

#endif