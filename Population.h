#ifndef Population_h
#define Population_h
#include <iostream>
#include <vector>
#include <random>
#include "Polynomial.h"

class Population{
    public:
        int countIndivids = 0;
        std::vector<Chromosome> chromosomes = {};
        
        Population(double down = 0, double up = 100, int countIndivids = 50, int countSteps = 10, double probMutation = 0.1); // генерируется популяция из count_individs особей 
        Population updatePopulation(std::vector<Chromosome> chromosomes);
        //реализовать ЭЛИТАРНЫЙ ОТБОР
        Population selection(Polynomial *polynom, double criterion);
};

#endif
