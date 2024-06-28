#include "Population.h"


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

void Population::selection(Polynomial *polynom, double criterion) {
    std::vector<Chromosome> children;
    for (int i = 0; i < this->countIndivids; i++) {
        double difference = polynom->Evaluation(this->chromosomes[i]);
        if (difference <= criterion) {
            int j = i;
            while (j = i) {
                j = rand() % (countIndivids);
            }
            std::pair<Chromosome> pair_children = this->chromosomes[i]->recombination(this->chromosomes[i], this->chromosomes[j]);
            children.push_back(pair_children[0]);
            children.push_back(pair_children[1]);
        }
    }
}
