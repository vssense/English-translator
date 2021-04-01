options = -Wall -Wextra -pedantic

main: bin/main.o bin/hashtable.o
	g++ bin/main.o bin/hashtable.o bin/dynamic_array.o -o main

bin/main.o: main.cpp hashtable.h dictionary.cpp
	g++ -c main.cpp -o bin/main.o $(options)

bin/hashtable.o: hashtable.cpp hashtable.h bin/dynamic_array.o
	g++ -c hashtable.cpp -o bin/hashtable.o $(options)

bin/dynamic_array.o: dynamic_array.cpp dynamic_array.h
	g++ -c dynamic_array.cpp -o bin/dynamic_array.o $(options)
