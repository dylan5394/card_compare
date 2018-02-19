COMPILER = g++
CCFLAGS = -g -ansi
LIBFLAGS = lib/cppunitlite.a

%.o : %.cpp
	$(COMPILER) $(CCFLAGS) -c $<

objects = main.o card_test.o card_compare.o

all: cppunitlite test

cppunitlite:
	cd lib; make all

test: $(objects) 
	${COMPILER} -o test $(objects) ${LIBFLAGS} 

random_compare:
	g++ -g -ansi -c random_compare.cpp
	g++ -g -ansi -c card_compare.cpp
	${COMPILER} -o random_compare random_compare.o card_compare.o
    
main.o: main.cpp
card_test.o: card_test.cpp
card_compare.o: card_compare.cpp

clean:
	cd lib; make clean
	rm *.o test random_compare