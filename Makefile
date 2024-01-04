CC=g++
PROGNAME=6502Emulator

all: instructionCycle.o memory.o processor.o codeLoad.o dataView.o main.o $(PROGNAME) clean

instructionCycle.o: src/instructionCycle.cpp src/instructionCycle.hpp src/processor.hpp src/memory.hpp src/dataView.hpp
	$(CC) $(CFLAGS) -c src/instructionCycle.cpp
memory.o: src/memory.cpp src/memory.hpp
	$(CC) $(CFLAGS) -c src/memory.cpp
processor.o: src/processor.cpp src/processor.hpp src/memory.hpp src/codeLoad.hpp
	$(CC) $(CFLAGS) -c src/processor.cpp
codeLoad.o: src/codeLoad.cpp src/codeLoad.hpp
	$(CC) $(CFLAGS) -c src/codeLoad.cpp
dataView.o: src/dataView.cpp src/dataView.hpp src/processor.hpp
	$(CC) $(CFLAGS) -c src/dataView.cpp
main.o: src/main.cpp src/memory.hpp src/processor.hpp src/instructionCycle.hpp src/dataView.hpp
	$(CC) $(CFLAGS) -c src/main.cpp

$(PROGNAME): instructionCycle.o memory.o processor.o codeLoad.o dataView.o main.o 
	$(CC) instructionCycle.o memory.o processor.o codeLoad.o dataView.o main.o -o $(PROGNAME)

clean: 
	rm *.o