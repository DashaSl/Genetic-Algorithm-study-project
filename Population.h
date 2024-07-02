#ifndef Population_h
#define Population_h
#include <iostream>
#include <vector>
#include <random>
#include "Polynomial.h"

class Population{
    public:
        int countIndivids = 0;
        std::vector<Chromosome> chromosomes = {};
        double threshold;
        int countBestIndivids;
        
        Population(Polynomial &polynom, double down = 0, double up = 100, int countIndivids = 50, int countSteps = 10, double probMutation = 0.2); // генерируется популяция из count_individs особей 
        void updatePopulation(std::vector<Chromosome> chromosomes);
        //реализовать ЭЛИТАРНЫЙ ОТБОР
        void elite_selection(Polynomial &polynom); // элитарный отбор
        void sortPopulation();
        void addChildren(std::vector<Chromosome> &children, Polynomial &polynom);
};

#endif
