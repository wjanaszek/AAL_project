#include "DataReader.h"
#include <fstream>
#include <iostream>
#include "WrongNumberOfElementsException.h"
#include "FileIOException.h"

/**
*   Wojciech Janaszek 273689 ISI
*   T11 - rozpl¹tywanie odcinków
*/

DataReader::DataReader(){}

DataReader::~DataReader(){}

vector<points> DataReader::readFromKeyboard()
{
	vector<points> result(2);
	string input = "-";
	int N;
	int groupNumber = 0;
	cout << "---> Dodajesz punkty do grupy pierwszej" << endl;
	cout << "Podawaj punkty wedlug wzoru: \"<X>,<Y>\", zatwierdz klawiszem ENTER." << endl;
	cout << "Jesli chcesz przerwac wczytywanie punktow, wpisz \"quit\"" << endl;
	cout << "Jesli chcesz dodac punkty do drugiej grupy, wpisz \"gchange\"" << endl;
	cout << "(po zmianie grupy nie bedzie juz mozliwe dodawanie punktow do pierwszej grupy)" << endl;
	while (true) {
		if (input.length() > 0) {
			input.clear();
		}
		cin >> input;
		if (input.compare("gchange") == 0 && groupNumber == 0) {
			groupNumber = 1;
			N = result[0].size();
			cout << "--> pomyslnie zmieniono numer grupy na 2" << endl;
			continue;
		}
		else if (input.compare("gchange") == 0 && groupNumber == 1) {
			cout << "niemozliwa operacja (group change)!" << endl;
			continue;
		}
		else if (input.compare("quit") == 0) {
			if (groupNumber == 1) {
				if (result[groupNumber].size() != N) {
					throw new WrongNumberOfElementsException();
				}
			}
			else {
				throw new WrongNumberOfElementsException();
			}
			break;
		}
		if (isalpha(input.c_str()[0]) != 0) {
			cout << "Podaj cyfry, nie litery!" << endl;
			continue;
		}
		if (checkBounds(input, result)) {
			Point2D * p = new Point2D(input, groupNumber);
			result[groupNumber].push_back(*p);
			cout << "--> pomyslnie dodano" << endl;
		}
		else {
			cout << "Podaj inna wartosc, niepowtarzajaca sie!" << endl;
		}
	}
	return result;
}

vector<points> DataReader::readFromFile(string fileName)
{
	fstream f;
	int N;
	int groupNumber = 0;
	vector<points> result(2);
	string inputLine;
	f.open(fileName.c_str(), ios::in);
	if (!f.good()) {
		throw new FileIOException();
	}
	else {
		while (!f.eof()) {
			getline(f, inputLine);
			if (inputLine.compare("gchange") == 0) {
				inputLine.clear();
				N = result[groupNumber].size();
				groupNumber = 1;
				continue;
			}
			if (inputLine.compare("end") == 0) {
				break;
			}
			Point2D * p = new Point2D(inputLine, groupNumber);
			result[groupNumber].push_back(*p);
			inputLine.clear();
		}
		if (groupNumber == 1) {
			if (result[groupNumber].size() != N) {
				throw new WrongNumberOfElementsException();
			}
		}
		else {
			throw new WrongNumberOfElementsException();
		}
	}
	f.close();
	return result;
}

bool DataReader::checkBounds(string input, vector<points> & result)
{
	int x, y;
	vector<string> inputSplited;
	inputSplited = split(input, ',');
	x = stoi(inputSplited[0]);
	y = stoi(inputSplited[1]);
	for (int i = 0; i < result.size(); i++) {
		for (int j = 0; j < result[i].size(); j++) {
			if (x == result[i].at(j).getX() && y == result[i].at(j).getY()) {
				cout << "Powtorzono: " << x << "," << y << ". ";
				return false;
			}
		}
	}
	return true;
}

vector<string> DataReader::split(const string & text, char sep)
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

