COMPILER = g++
CCFLAGS = -g -ansi

objects = card_compare.o

all: random_compare

random_compare:
	g++ -g -ansi -c random_compare.cpp
	g++ -g -ansi -c card_compare.cpp
	${COMPILER} -o random_compare random_compare.o card_compare.o

clean:
	rm *.o random_compare