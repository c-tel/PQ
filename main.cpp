#include "OrderedPQ.h"
#include "UnorderedPQ.h"
#include "HeapPQ.h"
#include <iostream>
#include "TestClasses.h"
using namespace std;

bool absVal(const int& i, const int& j)
{
	return abs(i) > abs(j);
}

bool mod10(const size_t& i, const size_t& j)
{
	return i%10 > j%10;
}

int main()
{
	cout << "*****Unordered PQ of ints*****"  << endl;
	cout << "Prior function: default(e1>e2)" << endl;
	UnorderedPQ<int> intUPQ;
	intUPQ.insert(5).insert(10).insert(0);
	cout << "After insertion of 5, 10 and 0 top is " << intUPQ.top() << endl;
	intUPQ.insert(11).insert(-1);
	while(!intUPQ.empty())
	{
		cout << intUPQ.top() << ' ';
		intUPQ.pop();
	}
	cout << endl;
	try
	{
		intUPQ.pop();
	}
	catch(PriorityQueue<int>::BadPQ bpq)
	{
		bpq.diagnose();
	}
	cout << endl;

	cout << "Unordered PQ of plain vectors"  << endl;
	cout << "Prior function: using lenght" << endl;
	PlainVec v1(3, 3), v2, v3(10), v4(1, 1), v5(4, 0.5);
	UnorderedPQ<PlainVec, length_comparison> vecUPQ;
	vecUPQ.insert(v1).insert(v2).insert(v3).insert(v4).insert(v5);
	while(!vecUPQ.empty())
	{
		cout << vecUPQ.top() << endl;
		vecUPQ.pop();
	}
	cout << endl << endl;
	

	cout << "*********Ordered PQ of ints*********"  << endl;
	cout << "Prior function: using absolute value" << endl;
	OrderedPQ<int, absVal> intOPQ;
	intOPQ.insert(3).insert(-4).insert(-2);
	cout << "After insertion of 3, -4 and -1 top is " << intOPQ.top() << endl;
	intOPQ.insert(0).insert(-10);
	for(int i = 0; i<3; ++i)
	{
		cout << intOPQ.top() << ' ';
		intOPQ.pop();
	}
	cout << endl;
	intOPQ.insert(-3).insert(11).insert(-1).insert(8).insert(-7);
	while(!intOPQ.empty())
	{
		cout << intOPQ.top() << ' ';
		intOPQ.pop();
	}
	cout << endl << endl;
	
	cout << "Ordered PQ of natural numbers"  << endl;
	cout << "Prior function: using mod 10" << endl;
	
	OrderedPQ<size_t, mod10> uintOPQ;
	uintOPQ.insert(9).insert(14).insert(112);
	cout << "After insertion of 9, 14 and 112 top is " << uintOPQ.top() << endl;
	uintOPQ.insert(10).insert(11);
	for(int i = 0; i<3; ++i)
	{
		cout << uintOPQ.top() << ' ';
		uintOPQ.pop();
	}
	cout << endl;
	uintOPQ.insert(13).insert(115).insert(122).insert(18).insert(17);
	while(!uintOPQ.empty())
	{
		cout << uintOPQ.top() << ' ';
		uintOPQ.pop();
	}
	cout << endl << endl;
	

	Student s1(61, "Adamenko"), s2(92, "Yakovchuk"), s3(71, "Petrenko"), s4(83, "Ivanenko"), s5(75, "Kovalchuk");
	
	// compile error: Student has no operator>, must specify comparison function
	// HeapPQ<Student> studHPQ;

	cout << "***********Binary heap PQ of students************"  << endl;
	cout << "Prior function: lexicographical order of surnames" << endl;
	
	HeapPQ<Student, lexicographical> studLexHPQ;
	studLexHPQ.insert(s1).insert(s2).insert(s3).insert(s4).insert(s5);
	while(!studLexHPQ.empty())
	{
		cout << studLexHPQ.top() << endl;
		studLexHPQ.pop();
	}
	cout << endl;

	cout << "*****Binary heap PQ of students*****" << endl;
	cout << "Prior function: using average grades" << endl;	
	HeapPQ<Student, educational> studGradeHPQ;
	studGradeHPQ.insert(s1).insert(s2).insert(s3).insert(s4).insert(s5);
	while(!studGradeHPQ.empty())
	{
		cout << studGradeHPQ.top() << endl;
		studGradeHPQ.pop();
	}
	cout << endl;

	return 0;
}