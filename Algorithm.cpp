#include "Algorithm.h"


Algorithm::Algorithm(double down, double up, int count_individs, int count_steps, double probMutation, std::vector<double> coefs_polynom, int iteration, double criterion, double left, double right) {
    Population population(down, up, count_individs, count_steps, probMutation);
    Polynomial polynom = Polynomial(coefs_polynom, left, right);
    this->polynom = polynom;
    this->population = population;
    this->iteration = iteration;
    this->criterion = criterion;
};
