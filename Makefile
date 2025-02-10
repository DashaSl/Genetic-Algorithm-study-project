all:
	g++ -shared -o bibl.so -fPIC bibl.cpp Algorithm.cpp Polynomial.cpp Population.cpp Chromosome.cpp
