#include <iostream>
#include <string>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <ctime>
#include "DataService.h"
#include "FileIOException.h"
#include "Point2D.h"
#include "Algorithms.h"
#include "ezdib.h"
#include "SetOfSegments.h"
#include "Segment.h"
#include <sstream>

#define SSTR( x ) static_cast< std::ostringstream & >( \
        ( std::ostringstream() << std::dec << x ) ).str()

#define RADIUS 6
#define BLUE 0x0000ff
#define RED 0xff0000
#define WHITE 0xffffff
#define BLACK 0x000000
#define MAX_VERT_COUNT 7    // maksymalna liczba wierzcholkow dla algorytmu brutal force
#define MAX_M_COUNT 1       // maksymalna liczba pomiarow do wyciagniecia sredniej

/**
*   Wojciech Janaszek 273689 ISI
*   T11 - rozpl¹tywanie odcinków
*/

using namespace std;

typedef vector<Point2D> points;

// Image for brutal force algorithm
HEZDIMAGE hDib_BF;
// Image for algorithm
HEZDIMAGE hDib_CN;
// Vector of input points
vector<points> input;

// Forward functions definitions:
bool checkParam(string input, char paramName);
int getParam(string input, char paramName);
void secondTypeWithParametrization(int argc, char ** argv, char * arg, int * N, int * seed);
void secondTypeWithoutParametrization(int argc, char ** argv, char * arg, int * N);
void brutalForce(vector<points> v);
float brutalForceTest(vector<points> v);
void optAlgorithm(vector<points> v);
float optAlgorithmTest(vector<points> v);
char * getCurrentDateToString();
void myPrintLine(int N, float averageTime, float q);
float average(float *table, int tableSize);

// Function to draw to specified imagefile
void drawToFile(HEZDIMAGE * image, SetOfSegments * s);

// Main
int main(int argc, char ** argv) {
    // Input arguments
	char *arg1, *arg2, *arg3, *arg4, *arg5;
	int seed;
	int N;
	string tmp;
	DataService ds;

    //srand(time(NULL));

    // For polish signs
    setlocale(LC_ALL,"");

	// Different parameters service
	if (argc > 1) {
		arg1 = argv[1];
		// pierwszy tryb - wczytanie danych z pliku lub z klawiatury
		// wczytanie danych z klawiatury:
		if (strcmp(arg1, "-1k") == 0) {
			input = ds.readFromKeyboard();			// wczytaj dane
			arg2 = argv[2];
			int alg_type = stoi(string(arg2));
			if(input[0].size() < MAX_VERT_COUNT && alg_type == 0){
                brutalForce(input);
                return 0;
			}
			else if(input[0].size() >= MAX_VERT_COUNT && alg_type == 0){
                    cout << "Rozmiar problemu przekracza ograniczenia dla tego algorytmu. Problem dla zadanej wielkosci zostanie rozwiazany przy pomocy algorytmu nr 2" << endl;
            }
			optAlgorithm(input);
			return 0;
		}
		// wczytanie danych z pliku (konieczne podane nazwy pliku jako kolejny parametr):
		else if (strcmp(arg1, "-1f") == 0) {
			if (argc > 1) {
				arg2 = argv[2];
				arg3 = argv[3];
				int alg_type = stoi(string(arg3));
				input = ds.readFromFile(string(arg2));
				if(input[0].size() < MAX_VERT_COUNT && alg_type == 0){
                    brutalForce(input);
                    return 0;
				}
				else if(input[0].size() >= MAX_VERT_COUNT && alg_type == 0){
                    cout << "Rozmiar problemu przekracza ograniczenia dla tego algorytmu. Problem dla zadanej wielkosci zostanie rozwiazany przy pomocy algorytmu nr 2" << endl;
				}
				optAlgorithm(input);
				return 0;
			}
			else {
				cout << "Brak nazwy pliku do wczytania!" << endl;
				exit(1);
			}
		}
		// drugi tryb - wygenerowanie potrzebnych danych losowo, z mozliwoscia parametryzacji losowosci
		// z parametryzacja:
		else if (strcmp(arg1, "-2g") == 0) {
            arg3 = argv[4];
            int alg_type = stoi(string(arg3));
			secondTypeWithParametrization(argc, argv, arg1, &N, &seed);
			cout << "seed = " << seed << endl;
			input = ds.generateData(N, seed);			// wygeneruj dane
			if(input[0].size() < MAX_VERT_COUNT && alg_type == 0){
                brutalForce(input);
                return 0;
            }
            else if(input[0].size() >= MAX_VERT_COUNT && alg_type == 0){
                cout << "Rozmiar problemu przekracza ograniczenia dla tego algorytmu. Problem dla zadanej wielkosci zostanie rozwiazany przy pomocy algorytmu nr 2" << endl;
            }
            optAlgorithm(input);
            return 0;
		}
		// bez parametryzacji:
		else if (strcmp(arg1, "-2gwout") == 0) {
			secondTypeWithoutParametrization(argc, argv, arg1, &N);
            arg3 = argv[3];
            int alg_type = stoi(string(arg3));      // 'T'
			input = ds.generateData(N);
			if(input[0].size() < MAX_VERT_COUNT && alg_type == 0){
                brutalForce(input);
                return 0;
            }
            else if(input[0].size() >= MAX_VERT_COUNT && alg_type == 0){
                cout << "Rozmiar problemu przekracza ograniczenia dla tego algorytmu. Pomiary zostana przerwane" << endl;
                    return 0;
            }
            optAlgorithm(input);
            return 0;
		}
		// trzeci tryb - wykonanie z generacja danych, pomiarem czasu i prezentacja wynikow
		// z parametryzacja:
		else if (strcmp(arg1, "-3g") == 0) {
			secondTypeWithParametrization(argc, argv, arg1, &N, &seed);
			arg3 = argv[4];
			arg4 = argv[5];
			arg5 = argv[6];
			int alg_type, R, mCount;
			int median;
			float T_n, T_n_median;
			float tmp, t_n_median, averageTime, q = 1.0f;
			float measureTable[MAX_M_COUNT];
			if(arg3 != nullptr){
                alg_type = stoi(string(arg3));
                if(alg_type == 0){
                    T_n = Algorithms::newton(N*N, N) * N*N*N;
                }
                else {
                    T_n = N*N*N;
                }
			}
			else {
                cout << "Nie wybrano zadnego algorytmu!" << endl;
                exit(1);
			}
			if(arg4 != nullptr){
                R = stoi(string(arg4));
			}
			else {
                cout << "Nie podano kroku!" << endl;
                exit(1);
			}
			if(arg5 != nullptr){
                mCount = stoi(string(arg5));        // liczba pomiarow
			}
			else {
                cout << "Nie podano ilosci pomiarow!" << endl;
                exit(1);
			}
			int tmp1 = N, tmp2 = N, mC1;
			if(mCount % 2 == 0){
                mC1 = mCount / 2 - 1;
                for(int i = 0; i < mCount; i++){
                    if(i < mC1){
                        tmp1 += R;
                    }
                    else {
                        tmp2 = tmp1;
                        tmp2 += R;
                        break;
                    }
                }
                median = (tmp1 + tmp2)/2;
			}
			else {
                mC1 = mCount / 2;
                for(int i = 0; i < mCount; i++){
                    if(i < mC1){
                        tmp1 += R;
                    }
                    else {
                        break;
                    }
                }
                median = tmp1;
			}
			if(alg_type == 0){
                T_n_median = Algorithms::newton(median * median, median) * median*median*median;
			}
			else {
                T_n_median = median * median * median;
			}
			cout << "mediana = " << median << ", N = " << N <<  endl;
			cout << "Rozpoczynam pomiary" << endl;
			alg_type == 0 ? cout << "brutal force" << endl : cout << "optimal" << endl;
			vector<points> tmpVec = ds.generateData(median, seed);
			if(alg_type == 0){
                t_n_median = brutalForceTest(tmpVec);
			}
			else {
                t_n_median = optAlgorithmTest(tmpVec);
			}
			cout << "| n      | t(n) [ms]      | q(n)" << endl;
			cout << "--------------------------------" << endl;
			q = (float)(t_n_median * T_n_median)/(t_n_median * T_n);
			myPrintLine(median, t_n_median * 1000.0f, q);
			for(int i = 0; i < mCount; i++){
                if(alg_type == 0){
                    T_n = Algorithms::newton(N*N, N) * N*N*N;
                }
                else {
                    T_n = N*N*N;
                }
                input = ds.generateData(N, seed);
                if(input[0].size() < MAX_VERT_COUNT && alg_type == 0){      // 'T' = 0
                    for(int j = 0; j < MAX_M_COUNT; j++){
                        tmp = brutalForceTest(input);
                        measureTable[j] = tmp;
                    }
                    q = (float)(measureTable[0] * T_n_median)/(float)(t_n_median * T_n);
                    averageTime = average(measureTable, MAX_M_COUNT);
                    myPrintLine(N, averageTime * 1000.0f, q);
                    N += R;
                }
                else if(input[0].size() >= MAX_VERT_COUNT && alg_type == 0){
                    cout << "Rozmiar problemu przekracza ograniczenia dla tego algorytmu. Pomiary zostana przerwane" << endl;
                    return 0;
                }
                if(alg_type == 1){
                    for(int j = 0; j < MAX_M_COUNT; j++){                       // 'T' = 1
                        tmp = optAlgorithmTest(input);
                        measureTable[j] = tmp;
                        input = ds.generateData(N, seed);
                    }
                    q = (float)(measureTable[0] * T_n_median)/(t_n_median * T_n);
                    averageTime = average(measureTable, MAX_M_COUNT);
                    myPrintLine(N, averageTime * 1000.0f, q);
                    N += R;
                }
			}
            return 0;
		}
		// bez parametryzacji:
		else if (strcmp(arg1, "-3gwout") == 0) {
			secondTypeWithoutParametrization(argc, argv, arg1, &N);
			input = ds.generateData(N);
			arg3 = argv[3];
			arg4 = argv[4];
			arg5 = argv[5];
			int alg_type, R, mCount;
			int median;
			float T_n, T_n_median;
			float tmp, t_n_median, averageTime, q = 1.0f;
			float measureTable[MAX_M_COUNT];
			if(arg3 != nullptr){
                alg_type = stoi(string(arg3));
                if(alg_type == 0){
                    T_n = Algorithms::newton(N*N, N) * N*N*N;
                }
                else {
                    T_n = N*N*N;
                }
			}
			else {
                cout << "Nie wybrano zadnego algorytmu!" << endl;
                exit(1);
			}
			if(arg4 != nullptr){
                R = stoi(string(arg4));
			}
			else {
                cout << "Nie podano kroku!" << endl;
                exit(1);
			}
			if(arg5 != nullptr){
                mCount = stoi(string(arg5));
			}
			else {
                cout << "Nie podano ilosci pomiarow!" << endl;
                exit(1);
			}
			int tmp1 = N, tmp2 = N, mC1;
			if(mCount % 2 == 0){
                mC1 = mCount / 2 - 1;
                for(int i = 0; i < mCount; i++){
                    if(i < mC1){
                        tmp1 += R;
                    }
                    else {
                        tmp2 = tmp1;
                        tmp2 += R;
                        break;
                    }
                }
                median = (tmp1 + tmp2)/2;
			}
			else {
                mC1 = mCount / 2;
                for(int i = 0; i < mCount; i++){
                    if(i < mC1){
                        tmp1 += R;
                    }
                    else {
                        break;
                    }
                }
                median = tmp1;
			}
			if(alg_type == 0){
                T_n_median = Algorithms::newton(median * median, median) * median*median*median;
			}
			else {
                T_n_median = median * median * median;
			}
			cout << "mediana = " << median << ", N = " << N <<  endl;
			cout << "Rozpoczynam pomiary" << endl;
			alg_type == 0 ? cout << "brutal force" << endl : cout << "optimal" << endl;
			vector<points> tmpVec = ds.generateData(median, seed);
			if(alg_type == 0){
                t_n_median = brutalForceTest(tmpVec);
			}
			else {
                t_n_median = optAlgorithmTest(tmpVec);
			}
			cout << "| n      | t(n) [ms]      | q(n)" << endl;
			cout << "--------------------------------" << endl;
			q = (float)(t_n_median * T_n_median)/(t_n_median * T_n);
			myPrintLine(median, t_n_median * 1000.0f, q);
			for(int i = 0; i < mCount; i++){
                if(alg_type == 0){
                    T_n = Algorithms::newton(N*N, N) * N*N*N;
                }
                else {
                    T_n = N*N*N;
                }
                input = ds.generateData(N);
                if(input[0].size() < MAX_VERT_COUNT && alg_type == 0){      // 'T' = 0
                    for(int j = 0; j < MAX_M_COUNT; j++){
                        tmp = brutalForceTest(input);
                        measureTable[j] = tmp;
                    }
                    averageTime = average(measureTable, MAX_M_COUNT);
                    q = (float)(measureTable[0] * T_n_median)/(t_n_median * T_n);
                    myPrintLine(N, averageTime * 1000.0f, q);
                    N += R;
                }
                else if(input[0].size() >= MAX_VERT_COUNT && alg_type == 0){
                    cout << "Rozmiar problemu przekracza ograniczenia dla tego algorytmu. Pomiary zostana przerwane" << endl;
                    return 0;
                }
                if(alg_type == 1){
                    for(int j = 0; j < MAX_M_COUNT; j++){                       // 'T' = 1
                        tmp = optAlgorithmTest(input);
                        measureTable[j] = tmp;
                        input = ds.generateData(N);
                    }
                    averageTime = average(measureTable, MAX_M_COUNT);
                    q = (float)(measureTable[0] * T_n_median)/(t_n_median * T_n);
                    myPrintLine(N, averageTime * 1000.0f, q);
                    N += R;
                }
			}
            return 0;
		}
		else {
			cout << "Niepoprawne polecenie. Instrukcja znajduje się w pliku readme.txt" << endl;
			exit(1);
		}
	}
	else {
        cout << "Niepoprawne polecenie. Instrukcja znajduje się w pliku readme.txt" << endl;
        exit(1);
	}
	return 0;
}

void myPrintLine(int N, float averageTime, float q) {
    int i = 0;
    string tmp = SSTR(N);
    cout << "| " << N;
    i = 7 - tmp.length();
    for(int j = 0; j < i; j++){
        cout << " ";
    }
    cout << "| " << averageTime;
    tmp = SSTR(averageTime);
    i = 15 - tmp.length();
    for(int j = 0; j < i; j++){
        cout << " ";
    }
    cout << "| " << q << endl;
}

float average(float *table, int tableSize) {
    float tmp = 0.0f;
    for(int i = 0; i < tableSize; i++){
        tmp += table[i];
    }
    return tmp / (float)tableSize;
}

bool checkParam(string input, char paramName) {
	bool wasParamName = false;
	bool wasNumbers = true;
	if (input.length() <= 1) {
		return false;
	}
	if (input.c_str()[0] != '-') {
		return false;
	}
	if (input.c_str()[1] != paramName) {
		return false;
	}
	else {
		wasParamName = true;
	}
	if (input.length() <= 2) {
		return false;
	}
	for (int i = 2; i < input.length(); i++) {
		if (isdigit(input.c_str()[i]) == 0) {
			wasNumbers = false;
			break;
		}
	}
	return wasParamName && wasNumbers;
}

int getParam(string input, char paramName) {
	input.erase(0, 2);
	int result = atoi(input.c_str());
	return result;
}

void secondTypeWithParametrization(int argc, char ** argv, char * arg1, int * N, int * seed) {
	char * arg2, * arg3;
	if (argc > 2) {
		arg2 = argv[2];
		if (checkParam(string(arg2), 'N')) {
			*N = getParam(string(arg2), 'N');
			if (argc > 3) {
				arg3 = argv[3];
				if (checkParam(string(arg3), 'S')) {
					*seed = getParam(string(arg3), 'S');
				}
				else {
					cout << "Podano nieprawidlowy parametr: seed \"-S<value>\"! Moze chodzi o brak cyfr?" << endl;
					exit(1);
				}
			}
			else {
				cout << "Nie podano parametru: seed \"-S<value>\"!" << endl;
				exit(1);
			}

		}
		else {
			cout << "Podano nieprawidlowy parametr: N \"-N<value>\"! Moze chodzi o brak cyfr?" << endl;
			exit(1);
		}
	}
	else {
		cout << "Nie podano parametru: N \"-N<value>\"!" << endl;
		exit(1);
	}
}

void secondTypeWithoutParametrization(int argc, char ** argv, char * arg1, int * N) {
	char * arg2;
	if (argc > 2) {
		arg2 = argv[2];
		if (checkParam(string(arg2), 'N')) {
			*N = getParam(string(arg2), 'N');
		}
		else {
			cout << "Podano nieprawidlowy parametr: N \"-N<value>\"! Moze chodzi o brak cyfr?" << endl;
			exit(1);
		}
	}
	else {
		cout << "Nie podano parametru: N \"-N<value>\"!" << endl;
		exit(1);
	}
}

// Wez dzisiejsza date
char * getCurrentDateToString() {
    time_t rawtime;
    struct tm * timeinfo;
    char buffer[80];

    time (&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(buffer,sizeof(buffer),"%d-%m-%Y %I:%M:%S",timeinfo);
    std::string str(buffer);
    char *result = new char[15];
    int j = 0;
    for(int i = 0; i < str.size(); i++){
        if(isdigit(buffer[i])){
            result[j] = buffer[i];
            j++;
        }
    }
    result[14] = '\0';
    return result;
}

// Algorytm brutal force (do uruchomienia w trybie 1 i 2  - z weryfikacja poprawnosci)
void brutalForce(vector<points> v)
{
    const clock_t begin_time = clock();
    int inputSize = v[0].size();
    SetOfSegments * bf;
    char imgFileName[22];
    char *currDate = getCurrentDateToString();
    imgFileName[0] = 'b';
    imgFileName[1] = 'f';
    imgFileName[2] = '_';
    imgFileName[3] = currDate[0];
    imgFileName[4] = currDate[1];
    imgFileName[5] = currDate[2];
    imgFileName[6] = currDate[3];
    imgFileName[7] = currDate[4];
    imgFileName[8] = currDate[5];
    imgFileName[9] = currDate[6];
    imgFileName[10] = currDate[7];
    imgFileName[11] = currDate[8];
    imgFileName[12] = currDate[9];
    imgFileName[13] = currDate[10];
    imgFileName[14] = currDate[11];
    imgFileName[15] = currDate[12];
    imgFileName[16] = currDate[13];
    imgFileName[17] = '.';
    imgFileName[18] = 'b';
    imgFileName[19] = 'm';
    imgFileName[20] = 'p';
    imgFileName[21] = '\0';

    delete currDate;

    hDib_BF = ezd_create( 1920, -1080, 24, 0 );
    // Fill in the background with a dark gray color
    ezd_fill( hDib_BF, 0x606060 );
    bf = Algorithms::executeBrutalForce(v);
    drawToFile(&hDib_BF, bf);
    ezd_save(hDib_BF, imgFileName);
    ezd_destroy(hDib_BF);

    cout << "Algorytm nr 1 wykonal sie w czasie " << float( clock () - begin_time ) /  CLOCKS_PER_SEC << " dla N = " << inputSize << endl;
    cout << "Efekt pracy zapisano do pliku: " << imgFileName << endl;
}

// Zwraca czas wykonania algorytmu dla danego rozmiaru problemu
float brutalForceTest(vector<points> v)
{
    const clock_t begin_time = clock();
    SetOfSegments * bf;
    bf = Algorithms::executeBrutalForce(v);
    return float( clock() - begin_time ) / CLOCKS_PER_SEC;
}

// Algorytm "pomyslowy" (do uruchomienia w trybie 1 i 2 - z weryfikacja poprawnosci)
void optAlgorithm(vector<points> v)
{
    const clock_t begin_time = clock();
    SetOfSegments * opt;
    char imgFileName[22];
    char *currDate = getCurrentDateToString();
    int inputSize = v[0].size();

    // Stworz nazwe pliku z data
    imgFileName[0] = 'o';
    imgFileName[1] = 'p';
    imgFileName[2] = '_';
    imgFileName[3] = currDate[0];
    imgFileName[4] = currDate[1];
    imgFileName[5] = currDate[2];
    imgFileName[6] = currDate[3];
    imgFileName[7] = currDate[4];
    imgFileName[8] = currDate[5];
    imgFileName[9] = currDate[6];
    imgFileName[10] = currDate[7];
    imgFileName[11] = currDate[8];
    imgFileName[12] = currDate[9];
    imgFileName[13] = currDate[10];
    imgFileName[14] = currDate[11];
    imgFileName[15] = currDate[12];
    imgFileName[16] = currDate[13];
    imgFileName[17] = '.';
    imgFileName[18] = 'b';
    imgFileName[19] = 'm';
    imgFileName[20] = 'p';
    imgFileName[21] = '\0';

    delete currDate;

    hDib_CN = ezd_create( 1920, -1080, 24, 0 );
     // Fill in the background with a dark gray color
    ezd_fill( hDib_CN, 0x606060 );
    opt = Algorithms::executeAlgorithm(v);
    drawToFile(&hDib_CN, opt);
        ezd_save(hDib_CN, imgFileName);
    ezd_destroy(hDib_CN);

    cout << "Algorytm nr 2 wykonal sie w czasie " << float( clock () - begin_time ) /  CLOCKS_PER_SEC << " dla N = " << inputSize << endl;
    cout << "Efekt pracy zapisano do pliku: " << imgFileName << endl;
}

// Zwraca czas wykonania algorytmu dla danego rozmiaru problemu
float optAlgorithmTest(vector<points> v)
{
    const clock_t begin_time = clock();
    SetOfSegments * opt;
    opt = Algorithms::executeAlgorithm(v);
    return float( clock() - begin_time ) / CLOCKS_PER_SEC;
}

void drawToFile(HEZDIMAGE * image, SetOfSegments * s)
{
    for(int i = 0; i < s->getSize(); i++)
    {
        ezd_circle(*image, s->getSegments()[i]->getLeft().getX(),
                         s->getSegments()[i]->getLeft().getY(),
                         RADIUS, RED);
        ezd_circle(*image, s->getSegments()[i]->getRight().getX(),
                         s->getSegments()[i]->getRight().getY(),
                         RADIUS, BLUE);
        ezd_line(*image, s->getSegments()[i]->getLeft().getX(), s->getSegments()[i]->getLeft().getY(),
                       s->getSegments()[i]->getRight().getX(), s->getSegments()[i]->getRight().getY(), WHITE);
    }
}
