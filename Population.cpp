#include "Population.h"
#include <algorithm>


Population::Population(Polynomial &polynom, double down, double up, int countIndivids, int countStep, double probMutation) {
    double difference;
    this->countIndivids = countIndivids;
    std::vector<double> differences;
    for (int i = 0; i < countIndivids; i++) {
        Chromosome new_chromosome = Chromosome(countStep, probMutation, down, up, i + 1);
        difference = polynom.Evaluation(this->chromosomes[i]);
        new_chromosome.estimate = difference;
        this->chromosomes.push_back(new_chromosome);
        differences.push_back(difference);
    }
    this->countBestIndivids = countIndivids / 3 * 4;
    this->threshold = differences[this->countBestIndivids];
}


bool compare(const Chromosome& left, const  Chromosome& right){
    double a = left.estimate;
    double b = right.estimate;
    return a < b;
}

void Population::sortPopulation() {
    std::sort(begin(this->chromosomes), end(this->chromosomes), compare);
}

void Population::updatePopulation(std::vector<Chromosome> chromosomes) {
    this->chromosomes = {};
    for (int i = 0; i < chromosomes.size(); i++) {
        this->chromosomes.push_back(chromosomes[i]);
    }
    this->sortPopulation();
    this->countIndivids = this->chromosomes.size();
}


void Population::addChildren(std::vector<Chromosome> children, Polynomial &polynom) {
    double difference;
    for (int i = 0; i < this->countIndivids; i++) {
        int j = i;
        while (j = i) {
            j = rand() % (this->countIndivids);
        }
        std::vector<Chromosome> pair_children = this->chromosomes[i].recombination(this->chromosomes[i], this->chromosomes[j]);
        difference = polynom.Evaluation(pair_children[0]);
        pair_children[0].estimate = difference;
        difference = polynom.Evaluation(pair_children[1]);
        pair_children[1].estimate = difference;
        children.push_back(pair_children[0]);
        children.push_back(pair_children[1]);
    }
}

void Population::elite_selection(Polynomial &polynom, int count) {
    std::vector<Chromosome> cutPopulation;
    std::vector<Chromosome> newPopulation;
    for (int i = 0; i < count; i++) {
        cutPopulation.push_back(this->chromosomes[i]);
    }
    this->updatePopulation(cutPopulation);
    this-> addChildren(cutPopulation, polynom);
    this->updatePopulation(cutPopulation);
    for (int i = 0; i < count; i++) {
        newPopulation.push_back(this->chromosomes[i]);
    }
    this->updatePopulation(newPopulation);
}


