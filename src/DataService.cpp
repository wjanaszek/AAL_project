#include "DataService.h"

DataService::DataService()
{}

DataService::~DataService()
{}

vector<points> DataService::readFromKeyboard()
{
	return dr.readFromKeyboard();
}

vector<points> DataService::readFromFile(string fileName)
{
	return dr.readFromFile(fileName);
}

vector<points> DataService::generateData(const int N)
{
	return dg.generateData(N);
}

vector<points> DataService::generateData(const int N, const int SEED)
{
	return dg.generateData(N, SEED);
}

void DataService::generateDataToFile(const int N, string fileName)
{
	//dg.generateDataToFile(N, fileName);
}

void DataService::generateDataToFile(const int N, const int SEED, string fileName)
{
	//dg.generateDataToFile(N, SEED, fileName);
}
