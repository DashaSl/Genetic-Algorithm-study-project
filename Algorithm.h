#ifndef Algorithm_h
#define Algorithm_h

#include <iostream>
#include "Population.h"
#include "Polynomial.h"
#include <vector>


class Algorithm{
    public:
        Population population;
        Polynomial polynom;
        int iteration;
        double criterion;
        
        Algorithm(Population population, std::vector<double> coefs_polynom, int iteration, double criterion, double left, double right);
        void start();
        void methodGA();
};

#endif
