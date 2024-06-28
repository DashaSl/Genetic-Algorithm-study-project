#include "Polynomial.h"
#include <math.h>

Polynomial::Polynomial(std::vector<double> coefs, double left, double right) {
        this->left = left;
        this->right = right;
	for (int i = 0; i < coefs.size(); i++) {
	    this->coeficients.push_back(coefs[i]);
	}
};  

double Polynomial:: getValue(double x) {
        double value = 0;
        for (int i = coeficients.size() - 1; i >= 0; i--) {  //coefs from greater to lower
            value += coeficients[i] * pow(x, i);    //calculating value in point x
        }
        return value;
}

void Polynomial::print() {
        for (int i = 0; i < this->coeficients.size(); i++){
            std::cout << this->coeficients[i] << ' ';
        }
        std::cout << '\n';
}
