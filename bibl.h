#include "Algorithm.h"
#include <cstdlib> 
extern "C" {


    Algorithm* init_alg(int count_individs, int count_steps, double probMutation, double* mass_coefs_polynom, int size, int iteration, double criterion, double left, double right);
    void del_alg(Algorithm* alg);

    Chromosome* init_crm(double probMutation =0.1, double down = 0, double up = 7, int number = 1, int len = 1);
    void del_crm(Chromosome* instance);


    Chromosome** stepHybridAlgorithm(Algorithm* alg);

    double* chromosome_genes(Chromosome* instance);

    double chromosome_esteem(Chromosome* instance);

    int chromosome_len(Chromosome* instance);
}