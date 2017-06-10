#include "Algorithms.h"
#include <iostream>
#include <math.h>
#include <climits>
#include <vector>

/**
*   Wojciech Janaszek 273689 ISI
*   T11 - rozplątywanie odcinków
*/

#define FIRST_GROUP 0
#define SECOND_GROUP 1

using namespace std;

Algorithms::Algorithms()
{
    //ctor
}

Algorithms::~Algorithms()
{
    //dtor
}

int Algorithms::min(int xi, int xj)
{
	if (xi < xj) {
		return xi;
	}
	else {
		return xj;
	}
}

int Algorithms::max(int xi, int xj)
{
	if (xi > xj) {
		return xi;
	}
	else {
		return xj;
	}
}

vector<string> Algorithms::split(const string & text, char sep)
{
    vector<string> tokens;
	size_t start = 0, end = 0;
	while ((end = text.find(sep, start)) != string::npos) {
		tokens.push_back(text.substr(start, end - start));
		start = end + 1;
	}
	tokens.push_back(text.substr(start));
	return tokens;
}

vector<subset> Algorithms::generateIndexes(int N, int K)
{
    bool onGoing = true;
    int i = 0;
    int resSize = newton(N, K);
    vector<subset> resVec(resSize);
    while(onGoing){
        int *A = new int[K + 1];
        for(int j = 1; j <= K; ++j){
            A[j] = j;
        }
        int p = K;
        while(p >= 1){
            for(int j = 1; j <= K; ++j){
                resVec[i].push_back(A[j]);
            }
            if(A[K] == N){
                --p;
            }
            else {
                p = K;
            }
            if(p >= 1){
                for(int j = K; j >= p; --j){
                    A[j] = A[p] + j - p + 1;
                }
            }
            if(i < resSize - 1){
                i++;
            }
            else {
                onGoing = false;
            }
        }
        delete[] A;
    }
    return resVec;
}

/*
*   Algorytm ze strony http://www.algorytm.org/algorytmy-arytmetyczne/symbol-newtona/newton-symbol-2-c.html
*/
unsigned long long Algorithms::newton(unsigned int n, unsigned int k)
{
    double result = 1;

    for(unsigned int i = 1; i <= k; i++){
        result = result * (n - i + 1) / i;
    }

    return (unsigned long long) result;
}

int Algorithms::NtoN(int N)
{
    const int nCounter = N;
    for(int i = 0; i < nCounter - 1; i++){
        N = N * nCounter;
    }
    return N;
}

void Algorithms::brutalForceAdd(vector<points> points1, SetOfSegments * s)
{
    int pointsQuanity = points1.at(0).size();
    int segmentIndex = 1;
    Segment * tmp;
    Point2D * tab = new Point2D[points1.at(0).size()];

    // Najpierw posortuj punkty rosnaca wedlug x
    for(int i = 0; i < points1.at(0).size(); i++){
        tab[i] = points1.at(0)[i];
    }
    points1.at(0).clear();
    SetOfSegments::quicksort(tab, 0, pointsQuanity - 1);
    for(int i = 0; i < pointsQuanity; i++){
        points1.at(0).push_back(tab[i]);
    }
    delete tab;
    tab = new Point2D[points1.at(1).size()];
    for(int i = 0; i < points1.at(1).size(); i++){
        tab[i] = points1.at(1)[i];
    }
    points1.at(1).clear();
    SetOfSegments::quicksort(tab, 0, pointsQuanity - 1);
    for(int i = 0; i < pointsQuanity; i++){
        points1.at(1).push_back(tab[i]);
    }
    delete tab;
    for(int i = 0; i < points1.at(0).size(); i++){
        for(int j = 0; j < points1.at(1).size(); j++){
            tmp = new Segment(points1.at(0)[i], points1.at(1)[j], segmentIndex);
            segmentIndex++;
            s->addSegment(tmp);
        }
    }
}

int Algorithms::det(Point2D p1, Point2D p2, Point2D p3)
{
    int a11, a12, a13, a21, a22, a23, a31, a32, a33;
    a11 = p1.getX();
    a12 = p1.getY();
    a13 = 1;

    a21 = p2.getX();
    a22 = p2.getY();
    a23 = 1;

    a31 = p3.getX();
    a32 = p3.getY();
    a33 = 1;
    return a11*a22*a33 + a12*a23*a31 + a13*a21*a32 - a13*a22*a31 - a11*a23*a32 - a12*a21*a33;
}

SetOfSegments * Algorithms::executeBrutalForce(vector<points> v)
{
    // Wynikowy zbiór nie zawieraj¹cy przecinaj¹cych siê odcinków
    SetOfSegments * resultSet;

    // Tymczasowy zbiór odcinków, do którego dodane zostan¹ wszystkie mo¿liwe odcinki
    SetOfSegments tmp;
    SetOfSegments * tmp2 = new SetOfSegments();

    brutalForceAdd(v, &tmp);

    // Wektor zbioru odcinków, zawieraj¹cy zbiory odcinków do sprawdzenia, czy nie zawieraj¹ odcinków przecinaj¹cych siê
    vector<SetOfSegments*> setsToCheck;
    Segment *s;

    // Podzbiór indeksów zbioru
    vector<subset> indexesSubset = generateIndexes(v[0].size()*v[0].size(), v[0].size());

    int l = 0;
    for(int i = 0; i < indexesSubset.size(); i++){
        for(int j = 0; j < indexesSubset[i].size(); j++){
            for(int k = 0; k < tmp.getSize(); k++){
                if(tmp.getSegmentAt(k).N == indexesSubset[i][j]){
                    s = new Segment(tmp.getSegmentAt(k).getLeft(), tmp.getSegmentAt(k).getRight(), indexesSubset[i][j]);
                    break;
                }
            }
            tmp2->addSegment(s);
        }
        setsToCheck.push_back(tmp2);
        tmp2 = new SetOfSegments();
        l++;
    }
    for(int i = 0; i < setsToCheck.size(); i++){
        if(setsToCheck[i]->anyIntersects()){
            continue;
        }
        else {
            resultSet = setsToCheck[i];
            return resultSet;
        }
    }
    return NULL;        // w przypadku b³êdu
}

SetOfSegments * Algorithms::executeAlgorithm(vector<points> v)
{
    SetOfSegments * result = new SetOfSegments();
    int minDistance = INT_MAX;
    int currDistance;
    int indexI, indexJ;
    Point2D * tmpI = nullptr, * tmpJ = nullptr;
    int segmentIndex = 1;

    // Wygeneruj zbior, laczac punkty najmniej oddalone od siebie
    while(true){
        minDistance = INT_MAX;
        currDistance = INT_MAX;
        if(v[0].size() > 1){
            for(int i = 0; i < v[0].size(); i++){
                for(int j = 0; j < v[1].size(); j++){
                    if((currDistance = (int)sqrt(pow(v[0].at(i).getX() - v[1].at(j).getX(), 2) + pow(v[0].at(i).getY() - v[1].at(j).getY(), 2))) <= minDistance){
                        minDistance = currDistance;
                        indexI = i;
                        indexJ = j;
                    }
                }
            }
            tmpI = new Point2D(v[0].at(indexI).getX(), v[0].at(indexI).getY(), v[0].at(indexI).groupNumber);
            tmpJ = new Point2D(v[1].at(indexJ).getX(), v[1].at(indexJ).getY(), v[1].at(indexJ).groupNumber);
            result->addSegment(new Segment(*tmpI, *tmpJ, segmentIndex++));
            delete tmpI;
            delete tmpJ;
            v[0].erase(v[0].begin() + indexI);
            v[1].erase(v[1].begin() + indexJ);
            if(v[0].size() == 1){
                tmpI = new Point2D(v[0].at(0).getX(), v[0].at(0).getY(),v[0].at(0).groupNumber);
                tmpJ = new Point2D(v[1].at(0).getX(), v[1].at(0).getY(), v[1].at(0).groupNumber);
                result->addSegment(new Segment(*tmpI, *tmpJ, segmentIndex++));
                v[0].clear();
                v[1].clear();
                if(tmpI != nullptr){
                    delete tmpI;
                }
                if(tmpJ != nullptr){
                    delete tmpJ;
                }
                break;
            }
        }
        else {
            tmpI = new Point2D(v[0].at(0).getX(), v[0].at(0).getY(),v[0].at(0).groupNumber);
            tmpJ = new Point2D(v[1].at(0).getX(), v[1].at(0).getY(), v[1].at(0).groupNumber);
            result->addSegment(new Segment(*tmpI, *tmpJ, segmentIndex++));
            v[0].clear();
            v[1].clear();
            if(tmpI != nullptr){
                delete tmpI;
            }
            if(tmpJ != nullptr){
                delete tmpJ;
            }
            break;
        }
    }

    Point2D * tmpLeftI, * tmpRightI, * tmpLeftJ, * tmpRightJ;
    Segment *tmpSeg;
    tmpSeg = nullptr;
    vector<Point2D> tmpVecI;
    vector<Point2D> tmpVecJ;
    SetOfSegments * tmp;
    Segment *toCmp1, *toCmp2;
    vector<points> v1;
    bool wasCross = false;
    int id;
    int crossI = -1, crossJ = -1;
    int j = 0;

    // Sprawdzaj pary, czy ktoras z nich sie nie przecina, i jesli tak, to sprobuj polaczyc punkty z tej pary odcinkow na drugi sposob
    while(true){
        for(int i = 0; i < result->getSize(); i++){
            for(int j = i + 1; j < result->getSize(); j++){
                if(Segment::intersects(result->getSegmentAtIndex(i), result->getSegmentAtIndex(j))){
                    tmpLeftI = new Point2D(result->getSegmentAt(i).getLeft().getX(), result->getSegmentAt(i).getLeft().getY(), result->getSegmentAt(i).getLeft().groupNumber);
                    tmpRightI = new Point2D(result->getSegmentAt(i).getRight().getX(), result->getSegmentAt(i).getRight().getY(), result->getSegmentAt(i).getRight().groupNumber);
                    tmpLeftJ = new Point2D(result->getSegmentAt(j).getLeft().getX(), result->getSegmentAt(j).getLeft().getY(), result->getSegmentAt(j).getLeft().groupNumber);
                    tmpRightJ = new Point2D(result->getSegmentAt(j).getRight().getX(), result->getSegmentAt(j).getRight().getY(), result->getSegmentAt(j).getRight().groupNumber);

                    // Sprawdz, z ktorej grupy pochodzi punkt
                    if(tmpLeftI->groupNumber == FIRST_GROUP){
                        tmpVecI.push_back(*tmpLeftI);
                    }
                    else if(tmpLeftI->groupNumber == SECOND_GROUP){
                        tmpVecJ.push_back(*tmpLeftI);
                    }

                    if(tmpLeftJ->groupNumber == FIRST_GROUP){
                        tmpVecI.push_back(*tmpLeftJ);
                    }
                    else if(tmpLeftJ->groupNumber == SECOND_GROUP){
                        tmpVecJ.push_back(*tmpLeftJ);
                    }

                    if(tmpRightI->groupNumber == FIRST_GROUP){
                        tmpVecI.push_back(*tmpRightI);
                    }
                    else if(tmpRightI->groupNumber == SECOND_GROUP){
                        tmpVecJ.push_back(*tmpRightI);
                    }

                    if(tmpRightJ->groupNumber == FIRST_GROUP){
                        tmpVecI.push_back(*tmpRightJ);
                    }
                    else if(tmpRightJ->groupNumber == SECOND_GROUP){
                        tmpVecJ.push_back(*tmpRightJ);
                    }

                    delete tmpLeftI;
                    delete tmpLeftJ;
                    delete tmpRightI;
                    delete tmpRightJ;
                    v1.push_back(tmpVecI);
                    v1.push_back(tmpVecJ);

                    // Nastepnie skorzystaj z brutal force dla znalezienia nieprzecinajacej sie pary odcinkow
                    tmp = executeBrutalForce(v1);

                    id = result->getSegmentAtIndex(i)->N;

                    tmpSeg = new Segment(tmp->getSegmentAt(0).getLeft(), tmp->getSegmentAt(0).getRight(), id);
                    result->getSegmentAt(i) = *tmpSeg;

                    id = result->getSegmentAtIndex(j)->N;

                    tmpSeg = new Segment(tmp->getSegmentAt(1).getLeft(), tmp->getSegmentAt(1).getRight(), id);
                    result->getSegmentAt(j) = *tmpSeg;

                    v1.clear();
                    tmpVecI.clear();
                    tmpVecJ.clear();
                    wasCross = true;
                }
            }
        }
        if(wasCross == true){
            wasCross = false;
            continue;
        }
        else break;
    }
    return result;
}
