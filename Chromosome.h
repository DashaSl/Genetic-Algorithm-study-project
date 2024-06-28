#include <iostream>
#include <vector>


class Chromosome {
    public:
        double probMutation;
        int number;
        std::vector<double> genes;
        
        Chromosome(double probMutation, double down, double up, int number);
       // void updateChromosome(std::vector<double>);
       // Chromosome mutation();
       // Chromosome recombination();
       // void addNumber();
};

