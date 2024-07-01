#ifndef Algorithm_h
#define Algorithm_h

#include <iostream>
#include "Population.h"
#include <vector>


class Algorithm{
    public:
        Polynomial polynom = Polynomial({}, 0, 0);
        Population population = Population(polynom);
        int iteration;
        double criterion;
        Algorithm(double down, double up, int count_individs, int count_steps, double probMutation, std::vector<double> coefs_polynom, int iteration, double criterion, double left, double right);
        std::vector<Chromosome> stepHybridAlgorithm();
        std::vector<Chromosome> top();
        void printStep();
};

#endif
