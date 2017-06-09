AAL: 
	g++ -std=c++11 -o AAL main.o Algorithms.o DataService.o DataGenerator.o DataReader.o FileIOException.o WrongNumberOfElementsException.o SetOfSegments.o Segment.o Point2D.o Sweeper.o 
main.o: main.cpp
	g++ -Wall -g -std=c++11 main.cpp 
Algorithms.o: Algorithms.cpp
	g++ -Wall -g -std=c++11 Algorithms.cpp
DataService.o: DataService.cpp
	g++ -Wall -g -std=c++11 DataService.cpp
DataGenerator.o: DataGenerator.cpp
	g++ -Wall -g -std=c++11 DataGenerator.cpp
DataReader.o: DataReader.cpp
	g++ -Wall -g -std=c++11 DataReader.cpp
FileIOException.o: FileIOException.cpp
	g++ -Wall -g -std=c++11 FileIOException.cpp
WrongNumberOfElementsException.o: WrongNumberOfElementsException.cpp
	g++ -Wall -g -std=c++11 WrongNumberOfElementsException.cpp
SetOfSegments.o: SetOfSegments.cpp
	g++ -Wall -g -std=c++11 SetOfSegments.cpp
Segment.o: Segment.cpp
	g++ -Wall -g -std=c++11 Segment.cpp
Point2D.o: Point2D.cpp
	g++ -Wall -g -std=c++11 Point2D.cpp
Sweeper.o: Sweeper.cpp
	g++ -Wall -g -std=c++11 Sweeper.cpp

