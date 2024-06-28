#include "Algorithm.h"


Algorithm::Algorithm(Population population, std::vector<double> coefs_polynom, int iteration, double criterion, double left, double right) {
    Polynomial polynom = Polynomial(coefs_polynom, left, right);
    this->polynom = polynom;
    this->population = population;
    this->iteration = iteration;
    this->criterion = criterion;
};
