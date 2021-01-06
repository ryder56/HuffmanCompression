OBJS = main.cpp HuffmanNode.hpp BinaryHeap.h HuffmanCompression.hpp LetterFrequency.hpp
EXE = HuffmanCompression
CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)
#-O0 -v -da -Q
$(EXE):$(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o $(EXE)

clean:
	rm $(EXE) *~
