#include "Population.h"
#include <algorithm>


Population::Population(Polynomial &polynom, double down, double up, int count, int countStep, double probMutation, double probReproduction) {
    if (count == 0) {
        return;
    }
    double difference;
    this->countIndivids = count;
    std::vector<double> differences;
    for (int i = 0; i < count; i++) {
        Chromosome new_chromosome = Chromosome(probMutation, down, up, i + 1, countStep, 0);
        difference = polynom.Evaluation(new_chromosome);
        new_chromosome.estimate = difference;
        this->chromosomes.push_back(new_chromosome);
        differences.push_back(difference);
    }
    this->countBestIndivids = countIndivids / 4 * 3;
    this->threshold = differences[this->countBestIndivids];
    this->probReproduction = probReproduction;
}


bool compare(const Chromosome& left, const  Chromosome& right){
    double a = left.estimate;
    double b = right.estimate;
    return a < b;
}

void Population::sortPopulation() {
    std::sort(begin(this->chromosomes), end(this->chromosomes), compare);
}

void Population::updatePopulation(std::vector<Chromosome> chroms) {
    this->chromosomes = {};
    for (int i = 0; i < chroms.size(); i++) {
        this->chromosomes.push_back(chroms[i]);
    }
    this->sortPopulation();
    this->countIndivids = this->chromosomes.size();
}


void Population::addChildren(std::vector<Chromosome> &children, Polynomial &polynom, int count, int time) {
    double difference;
    for (int i = 0; i < count; i++) {
        int j = i;
        while (j == i) {
            j = rand() % (this->countIndivids);
        }
        std::vector<Chromosome> pair_children = this->chromosomes[i].recombination(this->chromosomes[i], this->chromosomes[j]);
        difference = polynom.Evaluation(pair_children[0]);
        pair_children[0].estimate = difference;

        pair_children[0].birthDate = time;
        pair_children[1].birthDate = time;
        pair_children[0].age = -1;
        pair_children[1].age = -1;
        difference = polynom.Evaluation(pair_children[1]);
        pair_children[1].estimate = difference;
        children.push_back(pair_children[0]);
        children.push_back(pair_children[1]);
    }
    this->countIndivids = this->chromosomes.size();
}

void Population::elite_selection(Polynomial &polynom, int time) {
    std::vector<Chromosome> cutPopulation;
    std::vector<Chromosome> newPopulation;
    for (int i = 0; i < this->countBestIndivids; i++) {
        cutPopulation.push_back(this->chromosomes[i]);
    }
    this->updatePopulation(cutPopulation);

    this->addChildren(cutPopulation, polynom, this->countIndivids, time);

    this->updatePopulation(cutPopulation);
    for (int i = 0; i < cutPopulation.size(); i++) {
        newPopulation.push_back(this->chromosomes[i]);
    }
    this->updatePopulation(newPopulation);
}


//void Population:: truncation_selection(Polynomial &polynom, int count) {
//    std::vector<Chromosome> newPopulation;
//    if (this->countIndivids < count) {
//        count = countIndivids;
//    }
//    for (int i = 0; i < count, i++) {
//        newPopulation.push_back(this->chromosomes[i]);
//    }
//    int j;
//    while (newPopulation.size() < this->countIndivids) {
//        j = rand() % (this->count);
//        newPopulation.push_back(this->chromosomes[j]);
//    }
//    this->updatePopulation(newPopulation);
//}


void Population:: mutationPopulation() {
    for (int i = 0; i < this->countIndivids; i++) {
        this->chromosomes[i].mutate();
    }
}

void Population :: cutOldIndivids(int time) {
    //в this->chromosomes оставить только те хромосомы, чей возраст + дата рождения не больше чем curIteration
    auto iter = chromosomes.cbegin(); // указатель на первый элемент
    for (int i = 0; i < chromosomes.size(); i++) {
        //std::cout  << chromosomes[i].birthDate << ' ' <<  chromosomes[i].age << "\n";
        if (chromosomes[i].age + chromosomes[i].birthDate >= time) {
            //std::cout << "DELETE\n";
            chromosomes.erase(iter + i);
        }
    }
    this->countIndivids = chromosomes.size();
}

void Population :: addAge(int maxAge) {
    int age;
    for (int i = 0; i < this->countIndivids; i++) {
        if (this->chromosomes[i].age == -1) {
            age = maxAge - int(double(i) / countIndivids * maxAge);
            this->chromosomes[i].age = age;
        }
    }
}
