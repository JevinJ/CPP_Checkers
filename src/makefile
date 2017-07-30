CXX = g++
CXXFLAGS = -Wall -std=c++11
TARGET = Checkers
	
all: $(TARGET)

main.o:
	$(CXX) $(CXXFLAGS) -c main.cpp
	
ai.o: ai.h misc.h
	$(CXX) $(CXXFLAGS) -c ai.cpp
	
board.o: board.h
	$(CXX) $(CXXFLAGS) -c board.cpp
	
misc.o: misc.h board.h
	$(CXX) $(CXXFLAGS) -c misc.cpp
	
node.o: node.h board.h
	$(CXX) $(CXXFLAGS) -c node.cpp
	
player.o: player.h board.h misc.h player.h
	$(CXX) $(CXXFLAGS) -c player.cpp
	

$(TARGET): main.o ai.o board.o misc.o node.o player.o
	$(CXX) -o $(TARGET) main.o ai.o board.o misc.o node.o player.o
