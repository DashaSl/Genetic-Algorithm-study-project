#include <iostream>
#include <vector>
//#include "Chromosome.h"

class Population{
    public:
        int count_individs;
//        std::vector<Chromosome> chromosomes;
        
        Population(double down, double up, int count_individs, int count_steps, double probMutation); // генерируется популяция из count_individs особей 
        //Population updatePopulation();
        //Population selection();
};

