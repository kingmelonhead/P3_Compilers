CC=gcc
CFLAGS=-g -lstdc++ -std=c++11
all : statSem

statSem: main.cpp scanner.cpp scanner.hpp token.hpp testScanner.cpp testScanner.hpp parser.cpp parser.hpp node.hpp tree.cpp tree.hpp semantics.cpp semantics.hpp
	$(CC) -o $@ $^ $(CFLAGS) 

clean:
	rm statSem
