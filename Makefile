CC=gcc
CFLAGS=-g -lstdc++ -std=c++11
all : Parser

Parser: main.cpp scanner.cpp scanner.hpp token.hpp testScanner.cpp testScanner.hpp parser.cpp parser.hpp node.hpp tree.cpp tree.hpp
	$(CC) -o $@ $^ $(CFLAGS) 

clean:
	rm Parser
