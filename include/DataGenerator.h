#ifndef DATAGENERATOR_H
#define DATAGENERATOR_H

#include <vector>
#include "Point2D.h"

/**
*   Wojciech Janaszek 273689 ISI
*   T11 - rozpl¹tywanie odcinków
*/

using namespace std;

typedef vector<Point2D> points;

class DataGenerator
{
    public:
        DataGenerator();
        ~DataGenerator();
        static vector<points> generateData(const int N);
        static vector<points> generateData(const int N, const int SEED);
};

#endif // DATAGENERATOR_H
