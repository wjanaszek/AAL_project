#include "DataGenerator.h"
#include <ctime>

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
#define RECT_BOUND 100

/**
*   Wojciech Janaszek 273689 ISI
*   T11 - rozpl¹tywanie odcinków
*/

DataGenerator::DataGenerator()
{
    //ctor
}

DataGenerator::~DataGenerator()
{
    //dtor
}

vector<points> DataGenerator::generateData(const int N)
{
    return generateData(N, time(NULL));
}

vector<points> DataGenerator::generateData(const int N, const int SEED)
{
    int i = 0, j = 0, k = 0;
	int groupNumber = 0;
	vector<points> result(2);
	result[0][62000000];
	srand(SEED);
	Point2D * p;
	for (groupNumber = 0; groupNumber < 2; groupNumber++)
	{
		i = 0;
		while (i < N) {
			p = new Point2D(rand() % SCREEN_WIDTH, rand() % SCREEN_HEIGHT, groupNumber);
			for (j = 0; j < result[0].size(); j++) {
				if (result.at(0).at(j).getX() == p->getX() && result.at(0).at(j).getY() == p->getY()) {
					continue;
				}
			}
			for (k = 0; k < result[1].size(); k++) {
				if (result.at(1).at(k).getX() == p->getX() && result.at(1).at(k).getY() == p->getY()) {
					continue;
				}
			}
			if (j != result[0].size() || k != result[1].size()) {
				continue;
			}
			else {
				j = 0;
				k = 0;
				result[groupNumber].push_back(*p);
				i++;
			}
		}
	}
	return result;
}
