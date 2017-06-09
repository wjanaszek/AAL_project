#ifndef ALGORITHMS_H
#define ALGORITHMS_H

/**
*   Wojciech Janaszek 273689 ISI
*   T11 - rozplątywanie odcinków
*/

#include <vector>
#include <string>
#include "Segment.h"
#include "SetOfSegments.h"
#include "Point2D.h"

using namespace std;

typedef vector<int> subset;
typedef vector<Point2D> points;

class Algorithms
{
    public:
        Algorithms();
        ~Algorithms();

        static int min(int xi, int xj);
        static int max(int xi, int xj);
        static vector<string> split(const string & text, char sep);

        // Ze zbioru N indeksów utwórz K-elementowy podzbiór
        static vector<subset> generateIndexes(int N, int K);
        static unsigned long long newton(unsigned int n, unsigned int k);
        // Oblicz N^N
        static int NtoN(int N);
        static int det(Point2D p1, Point2D p2, Point2D p3);
        static SetOfSegments * executeBrutalForce(vector<points> v);
        static SetOfSegments * executeAlgorithm(vector<points> v);
        // TEST ONLY - powinno byc w private
        // SetOfSegments bedzie rozmiaru duzo wiekszego niz N - bedzie zawieral wszystkie mozliwosci polaczenia punktow w odcinki
        static void brutalForceAdd(vector<points> points, SetOfSegments * s);
    private:
        // SetOfSegments bedzie rozmiaru duzo wiekszego niz N - bedzie zawieral wszystkie mozliwosci polaczenia punktow w odcinki
        //static void brutalForceAdd(vector<points> points, SetOfSegments * s);
};

#endif // ALGORITHMS_H
