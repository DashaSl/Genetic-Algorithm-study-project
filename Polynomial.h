#ifndef Polynomial_h
#define Polynomial_h
#include "Chromosome.h"
#include <iostream>
#include <vector>
#define STEPS 1000

class Polynomial {
    private:
        std::vector<double> coeficients;
    public:
        double left;
        double right;
        Polynomial(std::vector<double> = {}, double left = 0, double right = 100);
        double getValue(double x);
        double Evaluation(Chromosome& chromosome);
        void print();
};


#endif
