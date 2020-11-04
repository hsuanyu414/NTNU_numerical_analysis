.PHONY:all
all:
	g++ horner.cpp -o horner
	g++ bisection.cpp -o bisection
	g++ newton.cpp -o newton
	g++ gaussian.cpp -o gaussian
	g++ PALU.cpp -o PALU
	g++ jacobi.cpp -o jacobi
clear:
	rm horner
	rm bisection
	rm newton
	rm gaussian
	rm PALU
	rm jacobi