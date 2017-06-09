#ifndef SETOFSEGMENTS_H
#define SETOFSEGMENTS_H

/**
*   Wojciech Janaszek 273689 ISI
*   T11 - rozpl¹tywanie odcinków
*/

#include <vector>
#include "Segment.h"
#include "Point2D.h"

using namespace std;

class SetOfSegments
{
    public:
        SetOfSegments();
        ~SetOfSegments();
        void addSegment(Segment * segment);
        Segment * getSegmentAtIndex(int index);
        Segment & getSegmentAt(int index);
        void removeSegmentAtIndex(int index);
        bool anyIntersects();
        bool isEmpty();
        int getSize();
        vector<Segment*> & getSegments();
        // Lepiej przeniesc do Algorithm.h
        int static partition(Point2D * tab, int p, int r);
        void static quicksort(Point2D * tab, int p, int r);
    private:
        vector<Segment*> segments;
        vector<Point2D*> getSortedPoints();
};

#endif // SETOFSEGMENTS_H
