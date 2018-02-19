COMPILER = g++
CCFLAGS = -g -ansi
LIBFLAGS = lib/cppunitlite.a

%.o : %.cpp
	$(COMPILER) $(CCFLAGS) -c $<

objects = main.o card_test.o ../src/card_compare.o

all: cppunitlite test

cppunitlite:
	cd lib; make all

test: $(objects) 
	${COMPILER} -o test $(objects) ${LIBFLAGS} 
    
main.o: main.cpp
card_test.o: card_test.cpp

clean:
	cd lib; make clean
	rm *.o test