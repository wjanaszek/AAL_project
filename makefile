CC = g++ -std=c++0x
OBJ_DIR = ./obj/Debug
SOURCE_DIR = ./src

default: build

build:
	$(CC) -Wall -c -I./include/ main.cpp -o $(OBJ_DIR)/main.o
	$(CC) -fpermissive -Wall -c ezdib.c -I ezdib.h -o $(OBJ_DIR)/ezdib.o
	$(CC) -Wall -c -I./include/ $(SOURCE_DIR)/DataGenerator.cpp -o $(OBJ_DIR)/src/DataGenerator.o
	$(CC) -Wall -c -I./include/ $(SOURCE_DIR)/DataReader.cpp -o $(OBJ_DIR)/src/DataReader.o
	$(CC) -Wall -c -I./include/ $(SOURCE_DIR)/DataService.cpp -o $(OBJ_DIR)/src/DataService.o
	$(CC) -Wall -c -I./include/ $(SOURCE_DIR)/FileIOException.cpp -o $(OBJ_DIR)/src/FileIOException.o
	$(CC) -Wall -c -I./include/ $(SOURCE_DIR)/WrongNumberOfElementsException.cpp -o $(OBJ_DIR)/src/WrongNumberOfElementsException.o
	$(CC) -Wall -c -I./include/ $(SOURCE_DIR)/Point2D.cpp -o $(OBJ_DIR)/src/Point2D.o
	$(CC) -Wall -c -I./include/ $(SOURCE_DIR)/Segment.cpp -o $(OBJ_DIR)/src/Segment.o
	$(CC) -Wall -c -I./include/ $(SOURCE_DIR)/SetOfSegments.cpp -o $(OBJ_DIR)/src/SetOfSegments.o
	$(CC) -Wall -c -I./include/ $(SOURCE_DIR)/Sweeper.cpp -o $(OBJ_DIR)/src/Sweeper.o
	$(CC) -Wall -c -I./include/ $(SOURCE_DIR)/Algorithms.cpp -o $(OBJ_DIR)/src/Algorithms.o
	$(CC) -Wall $(OBJ_DIR)/src/Algorithms.o $(OBJ_DIR)/src/Sweeper.o $(OBJ_DIR)/src/SetOfSegments.o $(OBJ_DIR)/src/Segment.o $(OBJ_DIR)/src/Point2D.o $(OBJ_DIR)/src/WrongNumberOfElementsException.o $(OBJ_DIR)/src/FileIOException.o $(OBJ_DIR)/src/DataService.o $(OBJ_DIR)/src/DataReader.o $(OBJ_DIR)/src/DataGenerator.o $(OBJ_DIR)/main.o $(OBJ_DIR)/ezdib.o -o proj 

clean:
	rm -f $(OBJ_DIR)/src/*.o
	rm -f $(OBJ_DIR)/*.o 
