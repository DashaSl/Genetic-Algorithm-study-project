#include "Algorithm.h"
#include <algorithm>


Algorithm::Algorithm(int count_individs, int count_steps, double probMutation, std::vector<double> coefs_polynom, int iteration, double criterion, double left, double right) {
    Polynomial polynom = Polynomial(coefs_polynom, left, right);

    std::vector<double> values;
    for (double x = left; x < right; x += (right - left) / 1000) {
    	values.push_back(polynom.getValue(x));
    }
    double down = *std::min_element(begin(values), end(values));
    double up = *std::max_element(begin(values), end(values));

    Population population = Population(polynom, down, up, count_individs, count_steps, probMutation);
    this->polynom = polynom;
    this->population = population;
    this->iteration = iteration;
    this->criterion = criterion;
};



bool compar(const Chromosome& left, const  Chromosome& right){
    double a = left.estimate;
    double b = right.estimate;
    return a < b;
}


std::vector<Chromosome> Algorithm :: stepHybridAlgorithm() {
    this->population.elite_selection(this->polynom);
    this->population.mutationPopulation();
    return this->top();
};

std::vector<Chromosome> Algorithm::top() {
    std::vector<double> difs;
    std::vector<Chromosome> ans;
    for (int i = 0; i < this->population.countIndivids; i++) {
        difs.push_back(this->population.chromosomes[i].estimate);
    }
    std::sort(begin(difs), end(difs));
    for (int i = 0; i < this->population.countIndivids; i++) {
        if (this->population.chromosomes[i].estimate <= difs[2]) {
            ans.push_back(this->population.chromosomes[i]);
        }
    }
    std::sort(begin(ans), end(ans), compar);
    return ans;
}


//std::vector<Chromosome> stepNonFixedSizeoplationGA(int iteration) {
//    this->population.addChildren();
//    this->population.cutOldIndivids(iteration)
//}

