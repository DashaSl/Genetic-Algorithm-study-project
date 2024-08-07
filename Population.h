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
        double probReproduction;
        int countBestIndivids;
        
        Population(Polynomial &polynom, double down = 0, double up = 100, int countIndivids = 50, int countSteps = 10, double probMutation = 0.2, double probReproduction = 0.6, int method_mut = 0, int method_recomb = 0); // генерируется популяция из count_individs особей 
        void updatePopulation(std::vector<Chromosome> chromosomes);
        //реализовать ЭЛИТАРНЫЙ ОТБОР
        void elite_selection(Polynomial &polynom); // элитарный отбор
        //void truncation_selection(Polynomial &polynom);
        void sortPopulation();
        void addChildren(std::vector<Chromosome> &children, Polynomial &polynom);
        void updateNonfixed(Polynomial &polynom, int count);
        void cutOldIndivids(int curIteration);
        void addAge(int maxAge);
};

#endif
