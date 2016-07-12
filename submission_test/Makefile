CC=g++
CFLAGS=-O3 -std=c++11 -funroll-loops -c
LDFLAGS=-O2 -std=c++11 -lm
SOURCES=Bot.cc MyBot.cc Role.cc MyState.cc State.cc Gather.cc Pathfinder.cc Hunter.cc
OBJECTS=$(addsuffix .o, $(basename ${SOURCES}))
EXECUTABLE=MyBot

#Uncomment the following to enable debugging
#CFLAGS+=-g -DDEBUG

all: $(OBJECTS) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cc.o: *.h
	$(CC) $(CFLAGS) $< -o $@

clean: 
	-rm -f ${EXECUTABLE} ${OBJECTS} *.d
	-rm -f debug.txt

.PHONY: all clean

