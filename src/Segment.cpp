#include "Segment.h"
#include <iostream>
#include "Algorithms.h"

/**
*   Wojciech Janaszek 273689 ISI
*   T11 - rozpl¹tywanie odcinków
*/

using namespace std;

Segment::Segment()
{
    //ctor
}

Segment::Segment(Point2D left, Point2D right, int index)
{
    this->left = new Point2D(left.getX(), left.getY(), left.groupNumber);
    this->right = new Point2D(right.getX(), right.getY(), right.groupNumber);
    this->N = index;
}

Segment::~Segment()
{
    delete left;
    delete right;
}

Point2D Segment::getLeft()
{
    return *left;
}

Point2D Segment::getRight()
{
    return *right;
}

/*bool Segment::intersects(Segment s1, Segment s2)
{
    Point2D p1, p2, p3, p4;
    p1 = s1.getLeft();
    p2 = s1.getRight();
    p3 = s2.getLeft();
    p4 = s2.getRight();
    int d1, d2, d3, d4;
    d1 = Point2D::direction(p3, p4, p1);
    d2 = Point2D::direction(p3, p4, p2);
    d3 = Point2D::direction(p1, p2, p3);
    d4 = Point2D::direction(p1, p2, p4);
    if(((d1 > 0 && d2 < 0) || (d1 < 0 && d2 > 0)) && ((d3 > 0 && d4 < 0) || (d3 < 0 && d4 > 0))){
        return true;
    }
    else if(d1 == 0 && Point2D::onSegment(p3, p4, p1)){
        return true;
    }
    else if(d2 == 0 && Point2D::onSegment(p3, p4, p2)){
        return true;
    }
    else if(d3 == 0 && Point2D::onSegment(p1, p2, p3)){
        return true;
    }
    else if(d4 == 0 && Point2D::onSegment(p1, p2, p4)){
        return true;
    }
    else {
        return false;
    }
}*/

bool Segment::intersects(Segment * s1, Segment * s2)
{
    Point2D p1, p2, p3, p4;
    p1 = s1->getLeft();
    p2 = s1->getRight();
    p3 = s2->getLeft();
    p4 = s2->getRight();
    int d1, d2, d3, d4;
    d1 = Point2D::direction(p3, p4, p1);
    d2 = Point2D::direction(p3, p4, p2);
    d3 = Point2D::direction(p1, p2, p3);
    d4 = Point2D::direction(p1, p2, p4);
    if(((d1 > 0 && d2 < 0) || (d1 < 0 && d2 > 0)) && ((d3 > 0 && d4 < 0) || (d3 < 0 && d4 > 0))){
        return true;
    }
    else if(d1 == 0 && Point2D::onSegment(p3, p4, p1)){
        return true;
    }
    else if(d2 == 0 && Point2D::onSegment(p3, p4, p2)){
        return true;
    }
    else if(d3 == 0 && Point2D::onSegment(p1, p2, p3)){
        return true;
    }
    else if(d4 == 0 && Point2D::onSegment(p1, p2, p4)){
        return true;
    }
    else {
        return false;
    }
}

// s2 to odcinek "miotly"
Point2D * Segment::getIntersectionPoint(Segment s1, Segment s2)
{
    Point2D * result;
    int y, y1, y2, x2, x1, x;
    x1 = s1.getLeft().getX();
    y1 = s1.getLeft().getY();
    x2 = s1.getRight().getX();
    y2 = s1.getRight().getY();
    y = (y2 - y1)*(s2.getLeft().getX() - x1)/(x2 - x1) + y1;
    if(y < 0){
        y = y*(-1);
    }
    result = new Point2D(s2.getLeft().getX(), y, -1);
    return result;
}
