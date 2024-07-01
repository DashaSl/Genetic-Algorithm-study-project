#ifndef Starter_h
#define Starter_h
#include "Algorithm.h"
#include <iostream>
#include <vector>
#include <ctime>
#include <random>
class Starter{
    public:
        Starter();
        void input();
        void execution(Algorithm &algorithm, int iteration);
        void print(std::vector<Chromosome>& top);
};


#endif
