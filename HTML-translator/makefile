options = -Wall -Wextra -pedantic -O3

src = ../HashTable

main: bin/translator.o bin/hashtable.o bin/dynamic_array.o bin/main.o
	g++ bin/main.o bin/translator.o bin/hashtable.o bin/dynamic_array.o -o main

bin/main.o: main.cpp translator.h $(src)/hashtable.h
	g++ -c main.cpp -o bin/main.o $(options)

bin/translator.o: translator.cpp translator.h $(src)/hashtable.h $(src)/dictionary.cpp
	g++ -c translator.cpp -o bin/translator.o $(options)

bin/hashtable.o: $(src)/hashtable.cpp $(src)/hashtable.h bin/dynamic_array.o
	g++ -c $(src)/hashtable.cpp -o bin/hashtable.o $(options)

bin/dynamic_array.o: $(src)/dynamic_array.cpp $(src)/dynamic_array.h
	g++ -c $(src)/dynamic_array.cpp -o bin/dynamic_array.o $(options)
