CXX=g++
CXXFLAGS=-O3
LDFLAGS=-lsfml-graphics -lsfml-window -lsfml-system

SRCDIR=./src
EXE=game_of_lag

all: $(EXE)

$(EXE): $(SRCDIR)/main.cpp
	@echo Building...
	$(CXX) -o $(EXE) $(CXXFLAGS) $(SRCDIR)/main.cpp $(LDFLAGS)
	@echo OK!

clean:
	rm -vf $(EXE)