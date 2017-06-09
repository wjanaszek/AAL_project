#include "Point2D.h"
#include <string>
#include "Algorithms.h"

/*
	@author Wojciech Janaszek
	T11 - odplatywanie odcinkow
	Implementacja klasy reprezentujacej punkt 2D.
*/
using namespace std;

Point2D::Point2D()
{
	x = 0;
	y = 0;
	groupNumber = 0;
}

Point2D::Point2D(int x, int y)
{
	this->x = x;
	this->y = y;
	this->groupNumber = NULL;
}

Point2D::Point2D(int x, int y, int groupNumber)
{
	this->x = x;
	this->y = y;
	this->groupNumber = groupNumber;
}

Point2D::Point2D(string input, int groupNumber)
{
	int x, y;
	vector<string> result = split(input, ',');
	x = stoi(result[0]);
	y = stoi(result[1]);
	this->x = x;
	this->y = y;
	this->groupNumber = groupNumber;
}

Point2D::~Point2D()
{
}

int Point2D::getX()
{
	return x;
}

int Point2D::getY()
{
	return y;
}

void Point2D::setX(int val)
{
	this->x = val;
}

void Point2D::setY(int val)
{
	this->y = val;
}

vector<string> Point2D::split(const string & text, char sep)
{
	vector<std::string> tokens;
	size_t start = 0, end = 0;
	while ((end = text.find(sep, start)) != string::npos) {
		tokens.push_back(text.substr(start, end - start));
		start = end + 1;
	}
	tokens.push_back(text.substr(start));
	return tokens;
}

bool Point2D::onSegment(Point2D p1, Point2D p2, Point2D p3)
{
	if (Algorithms::min(p1.getX(), p2.getX()) <= p3.getX() && p3.getX() <= Algorithms::max(p1.getX(), p2.getX())
      && (Algorithms::min(p1.getY(), p2.getY()) <= p3.getY() && p3.getY() <= Algorithms::max(p1.getY(), p2.getY()))) {
		return true;
	}
	return false;
}

int Point2D::direction(Point2D p1, Point2D p2, Point2D p3)
{
	Point2D pk_pi, pj_pi;
	pk_pi.setX(p3.getX() - p1.getX());
	pk_pi.setY(p3.getY() - p1.getY());
	pj_pi.setX(p2.getX() - p1.getX());
	pj_pi.setY(p2.getY() - p1.getY());
	return pk_pi.getX() * pj_pi.getY() - pj_pi.getX() * pk_pi.getY();
}
