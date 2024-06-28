#include "Population.h"
#include <algorithm>


Population::Population(double down, double up, int countIndivids, int countStep, double probMutation) {
        this->countIndivids = countIndivids;
        for (int i = 0; i < countIndivids; i++) {
            Chromosome new_chromosome = Chromosome(countStep, probMutation, down, up, i + 1);
            this->chromosomes.push_back(new_chromosome);
        }
}

void Population::updatePopulation(std::vector<Chromosome> chromosomes) {
    this->chromosomes = {};
    for (int i = 0; i < chromosomes.size(); i++) {
        this->chromosomes.push_back(chromosomes[i]);
    }
    this->countIndivids = this->chromosomes.size();
}

void Population::elite_selection(Polynomial &polynom, double criterion) {
    std::vector<Chromosome> children;
    std::vector<Chromosome> next_population;
    std::vector<double> differences;
    for (int i = 0; i < this->countIndivids; i++) {
        double difference = polynom.Evaluation(this->chromosomes[i]);
        differences.push_back(difference);
        this->chromosomes[i].estimate = difference;
        if (difference <= criterion) {
            int j = i;
            while (j = i) {
                j = rand() % (countIndivids);
            }
            std::vector<Chromosome> pair_children = this->chromosomes[i].recombination(this->chromosomes[i], this->chromosomes[j]);
            difference = polynom.Evaluation(pair_children[0]);
            pair_children[0].estimate = difference;
            differences.push_back(difference);
            difference = polynom.Evaluation(pair_children[1]);
            pair_children[1].estimate = difference;
            differences.push_back(difference);
            children.push_back(pair_children[0]);
            children.push_back(pair_children[1]);
        }
    }
    std::sort(begin(differences), end(differences));
    double threshold  = differences[this->chromosomes.size()];
    for (int i = 0; i < this->countIndivids; i++) {
        if (this->chromosomes[i].estimate <= threshold)
            next_population.push_back(this->chromosomes[i]);
    }
    for (int i = 0; i < children.size(); i++) {
        if (children[i].estimate <= threshold)
            next_population.push_back(children[i]);
    }
    this->updatePopulation(next_population);
}


