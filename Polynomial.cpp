#include "Polynomial.h"
#include <math.h>

Polynomial::Polynomial(std::vector<double> coefs, double left, double right) {
        this->left = left;
        this->right = right;
	for (int i = coefs.size() - 1; i >= 0; i--) {
		this->coeficients.push_back(coefs[i]);
	}
};  

double Polynomial:: getValue(double x) {
        double value = 0;
        for (int i = this->coeficients.size() - 1; i >= 0; i--) {  //coefs from greater to lower
                value += this->coeficients[i] * pow(x, i);    //calculating value in point x
        }
        return value;
}

void Polynomial::print() {
        for (int i = 0; i < this->coeficients.size(); i++){
                std::cout << this->coeficients[i] << ' ';
        }
        std::cout << '\n';
}

double Polynomial::Evaluation(Chromosome& chromosome) {
	double stairLen = (right - left) / chromosome.length;	//length of one stair 
	double h = stairLen / STEPS;	//distance between calculation points
	double difference = 0;	//result
	for (int stairNum = 0; stairNum < chromosome.length; stairNum++) {	//iteration by stairs with difference values
		double x = left + stairNum * stairLen;
		for (int i = 0; i < STEPS; i++) {
			difference += fabs(getValue(x) - chromosome.genes[stairNum]) * h;	//adding absolute difference in point x
			x += h;
		}
	}
	return difference;
}
