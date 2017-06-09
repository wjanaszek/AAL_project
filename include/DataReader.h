#ifndef DATAREADER_H
#define DATAREADER_H

/**
*   Wojciech Janaszek 273689 ISI
*   T11 - rozpl¹tywanie odcinków
*/

#include <vector>
#include <string>
#include "Point2D.h"

typedef vector<Point2D> points;

using namespace std;

class DataReader
{
public:
	DataReader();
	~DataReader();
	vector<points> readFromKeyboard();
	vector<points> readFromFile(string fileName);
private:
    static vector<string> split(const string & text, char sep);
	static bool checkBounds(string input, vector<points> & result);
};

#endif // DATAREADER_H
