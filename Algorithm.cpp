#include "Algorithm.h"


Algorithm::Algorithm(int count_individs, int count_steps, double probMutation, std::vector<double> coefs_polynom, int iteration, double criterion, double left, double right) {
    Polynomial polynom = Polynomial(coefs_polynom, left, right);
    double down = fmin(polynom.getValue(left), polynom.getValue(right)) / 2;
    double up = fmax(polynom.getValue(left), polynom.getValue(right)) * 2;
    Population population(down, up, count_individs, count_steps, probMutation);
    this->polynom = polynom;
    this->population = population;
    this->iteration = iteration;
    this->criterion = criterion;
};

void Algorithm:: start() {
    int i = 0;
    while (i < this->iteration) {
        this->population.elite_selection(this->polynom, this->criterion);
        //this->population.mutation_population();
    }
};

