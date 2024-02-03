CC=g++
PROGNAME=6502Emulator

all: instructionCycle.o memory.o processor.o codeLoad.o dataView.o ui_render.o main.o $(PROGNAME) clean

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
ui_render.o: src/ui_render.cpp src/ui_render.hpp src/instructionCycle.hpp
	$(CC) `pkg-config --cflags gtk+-3.0` -c src/ui_render.cpp `pkg-config --libs gtk+-3.0`
main.o: src/main.cpp src/ui_render.hpp src/memory.hpp src/processor.hpp src/instructionCycle.hpp src/dataView.hpp
	$(CC) `pkg-config --cflags gtk+-3.0` -c src/main.cpp `pkg-config --libs gtk+-3.0`

$(PROGNAME): instructionCycle.o memory.o processor.o codeLoad.o dataView.o ui_render.o main.o
	$(CC) `pkg-config --cflags gtk+-3.0` instructionCycle.o memory.o processor.o codeLoad.o dataView.o ui_render.o main.o `pkg-config --libs gtk+-3.0` -o $(PROGNAME)

clean: 
	rm *.o

exec:
	./$(PROGNAME)