#ifndef Algorithm_h
#define Algorithm_h

#include <iostream>
#include "Population.h"
#include <vector>


class Algorithm{
    public:
        Population population = Population();
        Polynomial polynom = Polynomial();
        int iteration;
        double criterion;
        Algorithm(double down, double up, int count_individs, int count_steps, double probMutation, std::vector<double> coefs_polynom, int iteration, double criterion, double left, double right);
        void start();
        void methodGA();
};

#endif
