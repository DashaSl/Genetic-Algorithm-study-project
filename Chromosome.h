#include <iostream>
#include <vector>
#include <random>
#include <limits>
#include <cfloat>

#define MAX_MUT_STP 0.02 //поменять, когда станет понятно

class Chromosome {
    public:
        double probMutation;
        int number;
        std::vector<double> genes;
        int length;
        double max_mutation_step; 
        double down_border;
        double up_border;
        double estimate;

        int metodRecomb;
        int methodMut; 
        int age;
        int birthDate = birthDate;

        Chromosome(double probMutation, double down, double up, int number, int len, int metodmut = 0, int methodrecomb = 0, int age = 1, int birthdate = 0);

        //В других классах и функциях используются только эти две функции
        static std::vector<Chromosome> recombination(Chromosome parent1, Chromosome parent2, int method = 0);
        void mutate(int method = 0);

        void mutate_dumb();
        double new_gene(double old_gene);
        static void discr_recomb(Chromosome parent1, Chromosome parent2, std::vector<Chromosome>& answer);
};
