CC=g++
LDFLAGS=-pthread
CXXFLAGS=-c -Wall -Wextra -std=c++2a -O3
SOURCES=$(wildcard src/*.cpp)
OBJECTS=$(SOURCES:.cpp=.o)
EXE=mt

$(EXE): $(SOURCES) $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

.cpp.o:
	$(CC) $(CXXFLAGS) $< -o $@

clean:
	rm -rf $(OBJECTS) $(EXE)
