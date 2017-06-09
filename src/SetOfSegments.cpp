#include "SetOfSegments.h"
#include "Sweeper.h"
#include "Point2D.h"
#include <vector>
#include <iostream>

/**
*   Wojciech Janaszek 273689 ISI
*   T11 - rozpl¹tywanie odcinków
*/

using namespace std;

SetOfSegments::SetOfSegments()
{
    //ctor
}

SetOfSegments::~SetOfSegments()
{
    //dtor
}

void SetOfSegments::addSegment(Segment * segment)
{
    segments.push_back(segment);
}

Segment * SetOfSegments::getSegmentAtIndex(int index)
{
    return segments[index];
}

Segment & SetOfSegments::getSegmentAt(int index)
{
    return *segments[index];
}

void SetOfSegments::removeSegmentAtIndex(int index)
{
    segments.erase(segments.begin() + index);
}

bool SetOfSegments::anyIntersects()
{
    // "Miotla"
    Sweeper * swp = new Sweeper();
    // zbior P = posortuj konce odcinkow z lewej do prawej
    vector<Point2D*> points = getSortedPoints();
    Point2D * p;
    Segment * seg, *pseg, *nseg;
    for(int i = 0; i < points.size(); i++){
        p = points[i];

        for(int j = 0; j < segments.size(); j++){
            // znajdz odcinek, ktorego p jest lewym koncem
            seg = segments[j];
            if(p->getX() == segments[j]->getLeft().getX() && p->getY() == segments[j]->getLeft().getY() && p->groupNumber == segments[j]->N){
                swp->push(seg);
                for(int i = 0; i < swp->getSize(); i++){
                    if(swp->getElementAt(i)->N != seg->N && Segment::intersects(seg, swp->getElementAt(i))){
                        return true;
                    }
                }
                break;
            }
            // znajdz odcinek, ktorego p jest prawym koncem
            if(p->getX() == segments[j]->getRight().getX() && p->getY() == segments[j]->getRight().getY() && p->groupNumber == segments[j]->N){
                for(int i = 0; i < swp->getSize(); i++){
                    if(swp->getElementAt(i)->N != seg->N && Segment::intersects(seg, swp->getElementAt(i))){
                        return true;
                    }
                }
                swp->remove(seg);
                break;
            }
        }
    }
    delete swp;
    return false;
}

bool SetOfSegments::isEmpty()
{
    return segments.empty();
}

int SetOfSegments::getSize()
{
    return segments.size();
}

vector<Segment*> & SetOfSegments::getSegments()
{
    return segments;
}

int SetOfSegments::partition(Point2D * tab, int p, int r)
{
    int x = tab[p].getX();
    int i = p, j = r;
    //Point2D * w;
    Point2D w;
    while(true){
        while(tab[j].getX() > x){
            j--;
        }
        while(tab[i].getX() < x){
            i++;
        }
        if(i < j){
            w = tab[i];
            tab[i] = tab[j];
            tab[j] = w;
            i++;
            j--;
        }
        else {
            //w = NULL;
            return j;
        }
    }
}

void SetOfSegments::quicksort(Point2D * tab, int p, int r)
{
    int q;
    if(p < r){
        q = partition(tab, p, r);
        quicksort(tab, p, q);
        quicksort(tab, q + 1, r);
    }
}

vector<Point2D*> SetOfSegments::getSortedPoints()
{
    vector<Point2D*> result;
    vector<Point2D*> leftP;
    vector<Point2D*> rightP;
    Point2D * tmp;
    for(int i = 0; i < segments.size(); i++){
        tmp = new Point2D(segments[i]->getLeft().getX(), segments[i]->getLeft().getY(), segments[i]->N);
        leftP.push_back(tmp);
        tmp = new Point2D(segments[i]->getRight().getX(), segments[i]->getRight().getY(), segments[i]->N);
        rightP.push_back(tmp);
    }
    Point2D * leftPointsTab = new Point2D[leftP.size()];
    Point2D * rightPointsTab = new Point2D[rightP.size()];
    for(int i = 0; i < leftP.size(); i++){
        leftPointsTab[i] = *leftP[i];
    }
    for(int i = 0; i < rightP.size(); i++){
        rightPointsTab[i] = *rightP[i];
    }

    quicksort(leftPointsTab, 0, leftP.size() - 1);
    quicksort(rightPointsTab, 0, rightP.size() - 1);

    for(int i = 0; i < leftP.size(); i++){
        tmp = new Point2D(leftPointsTab[i].getX(), leftPointsTab[i].getY(), leftPointsTab[i].groupNumber);
        result.push_back(tmp);
    }
    for(int i = 0; i < rightP.size(); i++){
        tmp = new Point2D(rightPointsTab[i].getX(), rightPointsTab[i].getY(), rightPointsTab[i].groupNumber);
        result.push_back(tmp);
    }
    delete leftPointsTab;
    delete rightPointsTab;
    return result;
}
