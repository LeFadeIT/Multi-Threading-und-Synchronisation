EXE=./prosumer

GPP=g++

OSTYPE := $(shell uname)

FLAGS=-std=c++20
ifeq ($(OSTYPE), Linux)
FLAGS=$(FLAGS)+ " -pthread"
endif


all: $(EXE)

$(EXE): prosumer.o 
	$(GPP) -o prosumer $(FLAGS)  prosumer.o

prosumer.o: prosumer.cpp
	$(GPP) $(FLAGS) -c prosumer.cpp

run: $(EXE) 
	$(EXE)

clean:
	$(RM) $(EXE) *.o
