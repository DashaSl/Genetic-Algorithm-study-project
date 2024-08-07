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
        int time = 0;
        int method;
        double criterion;
        Algorithm(int count_individs, int count_steps, double probMutation, std::vector<double> coefs_polynom, int iteration, double criterion, double left, double right, int method, int method_mut, int method_recomb, double probReproduction);
        std::vector<Chromosome> stepAlgorithm();
        std::vector<Chromosome> top();
        void printStep();
};

#endif
