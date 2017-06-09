#ifndef DATASERVICE_H
#define DATASERVICE_H

#include "DataGenerator.h"
#include "DataReader.h"

class DataService
{
public:
    DataService();
	~DataService();
	vector<points> readFromKeyboard();
	vector<points> readFromFile(string fileName);
	vector<points> generateData(const int N);
	vector<points> generateData(const int N, const int SEED);
	void generateDataToFile(const int N, string fileName);
	void generateDataToFile(const int N, const int SEED, string fileName);
private:
	DataGenerator dg;
	DataReader dr;
};

#endif // DATASERVICE_H
