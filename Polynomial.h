#ifndef Polynomial_h
#define Polynomial_h
#include <iostream>
#include <vector>


class Polynomial {
    private:
        std::vector<double> coeficients;
    public:
        double left;
        double right;
        Polynomial(std::vector<double>, double left, double right);
        double getValue(double x);
        void print();
};


#endif
