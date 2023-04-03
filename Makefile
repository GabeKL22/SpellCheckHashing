a.out:  QuadraticProbing.h QuadraticProbing.cpp project2.cpp
	g++ project2.cpp QuadraticProbing.cpp

test: QuadraticProbing.h QuadraticProbing.cpp TestQuadraticProbing.cpp
	g++ TestQuadraticProbing.cpp QuadraticProbing.cpp -o test

clean:
	rm a.out test *.o *~
