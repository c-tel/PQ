#include <string>
using namespace std;
class Student
{
public:
	Student(size_t aveGrade=0, const string& surname="unknown"): _surname(surname), _averageGrade(aveGrade){}
	~Student(){};
	Student(const Student& src): _surname(src._surname), _averageGrade(src._averageGrade){}
	Student& operator=(const Student& src)
	{
		_averageGrade = src._averageGrade;
		_surname = src._surname;
		return *this;
	}
	size_t getAveGrade() const { return _averageGrade; }
	const string& getSurname() const { return _surname; }
private:
	string _surname;
	size_t _averageGrade;
};

bool lexicographical(const Student& s1, const Student& s2)
{
	return s1.getSurname() < s2.getSurname();
}

bool educational(const Student& s1, const Student& s2)
{
	return s1.getAveGrade() > s2.getAveGrade();
}

ostream& operator<<(ostream& out, const Student& s)
{
	return out << "Student " << s.getSurname() << " with average grade " << s.getAveGrade(); 
}

class PlainVec
{
public:
	PlainVec(double x = 0, double y = 0): _x_coord(x), _y_coord(y){}
	PlainVec(const PlainVec& src): _x_coord(src._x_coord), _y_coord(src._y_coord){}
	PlainVec& operator=(const PlainVec& src)
	{
		_x_coord = src._x_coord;
		_y_coord = src._y_coord;

		return *this;
	}
	~PlainVec(){}
	double get_x() const { return _x_coord; }
	double get_y() const { return _y_coord; }
	double len() const {return sqrt(get_x()*get_x() + get_y()*get_y());}
private:
	double _x_coord, _y_coord;
};

ostream& operator<<(ostream& out, const PlainVec& v)
{
	return out << "Plain vector " << '(' << v.get_x() << ", " << v.get_y() << ')' << " with length " << v.len(); 
}

bool length_comparison(const PlainVec& v1, const PlainVec& v2)
{
	return v1.len() > v2.len();
}