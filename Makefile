FLAGS= -g -Wall -Wextra
LIB= -lm

all:main

Input.o:Input.cpp
	g++    -c -o Input.o Input.cpp $(CFLAGS) $(LIB)

main.o:main.cpp
	g++    -c -o main.o main.cpp $(CFLAGS) $(LIB)

main:Input.o main.o
	g++ -o main main.o Input.o $(LIB)

clean :
	rm -f *~* *.o  main
