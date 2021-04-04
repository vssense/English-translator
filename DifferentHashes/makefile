options = -Wall -Wextra -pedantic

src = ../HashTable

main: bin/main.o bin/hashtable.o
	g++ bin/main.o bin/hashtable.o bin/dynamic_array.o -o main

bin/main.o: main.cpp $(src)/hashtable.h $(src)/dictionary.cpp
	g++ -c main.cpp -o bin/main.o $(options)

bin/hashtable.o: $(src)/hashtable.cpp $(src)/hashtable.h bin/dynamic_array.o
	g++ -c $(src)/hashtable.cpp -o bin/hashtable.o $(options)

bin/dynamic_array.o: $(src)/dynamic_array.cpp $(src)/dynamic_array.h
	g++ -c $(src)/dynamic_array.cpp -o bin/dynamic_array.o $(options)
