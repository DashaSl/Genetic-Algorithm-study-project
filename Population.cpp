#include "Population.h"
#include <algorithm>


Population::Population(Polynomial &polynom, double down, double up, int count, int countStep, double probMutation, double probReproduction, int method_mut, int method_recomb) {
    if (count == 0) {
        return;
    }
    double difference;
    this->countIndivids = count;
    std::vector<double> differences;
    for (int i = 0; i < count; i++) {
        Chromosome new_chromosome = Chromosome(probMutation, down, up, i + 1, countStep, method_mut, method_recomb);
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


void Population::addChildren(std::vector<Chromosome> &children, Polynomial &polynom) {
    double difference;
    for (int i = 0; i < this->countIndivids; i++) {
        std::random_device rd;  // Will be used to obtain a seed for the random number engine
        std::mt19937_64 gen(rd());//генерирует случайное целое
        std::uniform_real_distribution<> dis(0, 1);
        int crossing_done = dis(gen);
        if (crossing_done > this-> probReproduction) {
            continue;
        }
        int j = i;
        while (j == i) {
            j = rand() % (this->countIndivids);
        }
        std::vector<Chromosome> pair_children = this->chromosomes[i].recombination(this->chromosomes[i], this->chromosomes[j]);
        difference = polynom.Evaluation(pair_children[0]);
        pair_children[0].estimate = difference;
        pair_children[0].mutate();
        pair_children[1].mutate();
        difference = polynom.Evaluation(pair_children[1]);
        pair_children[1].estimate = difference;
        children.push_back(pair_children[0]);
        children.push_back(pair_children[1]);
    }
    this->countIndivids = this->chromosomes.size();
}


void Population::updateNonfixed(Polynomial &polynom, int time) {
    double difference;
    double count = this->probReproduction * this->countIndivids;
    std::cout << count << ' ' <<  this->probReproduction  << ' ' <<  this->countIndivids;
    for (int k = 0; k < count; k++) {
        int i = rand() % (this->countIndivids);
        int j = i;
        while (j == i) {
            j = rand() % (this->countIndivids);
        }
        std::vector<Chromosome> pair_children = this->chromosomes[i].recombination(this->chromosomes[i], this->chromosomes[j]);
        pair_children[0].estimate = polynom.Evaluation(pair_children[0]);
        pair_children[0].birthDate = time;
        pair_children[0].age = -1;
        pair_children[0].mutate();
        this->chromosomes.push_back(pair_children[0]);
    }
    this->countIndivids = this->chromosomes.size();
}

void Population::elite_selection(Polynomial &polynom) {
    std::vector<Chromosome> cutPopulation;
    std::vector<Chromosome> newPopulation;
    for (int i = 0; i < this->countBestIndivids; i++) {
        cutPopulation.push_back(this->chromosomes[i]);
    }
    this->updatePopulation(cutPopulation);

    this->addChildren(cutPopulation, polynom);

    this->updatePopulation(cutPopulation);
    for (int i = 0; i < cutPopulation.size(); i++) {
        newPopulation.push_back(this->chromosomes[i]);
    }
    this->updatePopulation(newPopulation);
}

void Population :: cutOldIndivids(int time) {
    auto iter = chromosomes.cbegin(); // указатель на первый элемент
    for (int i = 0; i < chromosomes.size(); i++) {
        if (chromosomes[i].age + chromosomes[i].birthDate < time) {
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
