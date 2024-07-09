#include "bibl.h"

extern "C" Algorithm* init_alg(int count_individs, int count_steps, double probMutation, double* mass_coefs_polynom, int size, int iteration, double criterion, double left, double right, int method, int method_mut, int method_recomb, double probReproduction){
    //массив double в std::vector<double> coefs_polynom, после коэфф добавляется размер массива
    std::vector<double> coefs_polynom = {};
    for(int i = 0; i < size; i++){
        coefs_polynom.push_back(mass_coefs_polynom[i]);
    }
    return new Algorithm(count_individs, count_steps, probMutation, coefs_polynom, iteration, criterion, left, right, method, method_mut, method_recomb, probReproduction);
}

extern "C" void del_alg(Algorithm* alg){
    delete alg;
}


extern "C" Chromosome* init_crm(double probMutation, double down, double up, int number, int len){
    return new Chromosome(probMutation, down, up, number, len);
}

extern "C" void del_crm(Chromosome* instance){
    delete instance;
}



extern "C" Chromosome** stepHybridAlgorithm(Algorithm* alg){
    std::vector<Chromosome> tmp= alg->stepAlgorithm();
    Chromosome** a = (Chromosome**) malloc(sizeof(Chromosome*)*tmp.size());
    for(int i = 0; i < tmp.size(); i++){
        a[i] = new Chromosome(0, 0, 0, 0, 0);
        *a[i] = tmp[i];
    }
    return a;
}

extern "C" double* chromosome_genes(Chromosome* instance){
    double* a = new double[instance->genes.size()];
    for(int i = 0; i < instance->genes.size(); i++){
        a[i] = instance->genes[i];
    }
    return a;
}

extern "C" double chromosome_esteem(Chromosome* instance){
    return instance->estimate;
}

extern "C" int chromosome_len(Chromosome* instance){
    return instance->length;
}
