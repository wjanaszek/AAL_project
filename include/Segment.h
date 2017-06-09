#ifndef SEGMENT_H
#define SEGMENT_H

/**
*   Wojciech Janaszek 273689 ISI
*   T11 - rozpl¹tywanie odcinków
*/

#include "Point2D.h"

class Segment
{
    public:
        Segment();
        Segment(Point2D left, Point2D right, int index);
        ~Segment();

        Point2D getLeft();
        Point2D getRight();
        static bool intersects(Segment s1, Segment s2);
        static bool intersects(Segment * s1, Segment * s2);
        static Point2D * getIntersectionPoint(Segment s1, Segment s2);

        int N;          // index

    private:
        Point2D * left;
        Point2D * right;
};

#endif // SEGMENT_H
