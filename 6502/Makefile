CXX=gcc
CXXFLAGS=-g -std=c++11 -Wall -pedantic -D_DEBUG
BIN=6502
LIBS=-lstdc++

SRC=$(wildcard *.cpp)
OBJ=$(SRC:%.cpp=%.o)

all: $(OBJ)
	$(CXX) -o $(BIN) $(LIBS) $^

%.o: %.c
	$(CXX) $@ -c $<

clean:
	rm -f *.o
	rm $(BIN)	
