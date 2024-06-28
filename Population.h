#ifndef Population_h
#define Population_h
#include <iostream>
#include <vector>
#include "Polynomial.h"

class Population{
    public:
        int count_individs;
        std::vector<Chromosome> chromosomes;
        
        Population(double down = 0, double up = 100, int count_individs = 50, int count_steps = 10, double probMutation = 0.1); // генерируется популяция из count_individs особей 
        //Population updatePopulation();
        //Population selection();
};

#endif
