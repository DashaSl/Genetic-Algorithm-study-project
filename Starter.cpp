#include "Starter.h"



Starter::Starter() {
};


void Starter::input() {
    int degree, count_steps, iteration, count_individs;
    double left, right, up, down, criterion, probMutation;
    std::cout << "Введите степень полинома\n";
    std::cin >> degree;
    std::cout << "Введите через пробел коэффициенты полинома\n";
    std::vector<double> coefs(degree);
    for (int i = 0; i < degree; i++) {
        std::cin >> coefs[i];
    }
    std::cout << "Введите через пробел границы интервала, на котором определен полином\n";
    std::cin >> left >> right;
    std::cout << "Введите количество ступеней\n";
    std::cin >> count_steps;
    std::cout << "Введите количество индивидов в начальной популяции\n";
    std::cin >> count_individs;                                                                                  
    std::cout << "Введите нижнюю и верхнюю границу, в которых находятся высоты функции g\n";
    std::cin >> down >> up;                                                      
    std::cout << "Введите количество поколений и критерий (положительное число) через пробел\n";
    std::cin >> iteration >> criterion;
    std::cout << "Введите вероятность мутации каждого гена\n";
    std::cin >> probMutation;
    Algorithm algorithm = Algorithm(down, up, count_individs, count_steps, probMutation, coefs, iteration, criterion, left, right);
    this->execution(algorithm, iteration);
}

void Starter::execution(Algorithm &algorithm, int iteration) {
    std::vector<Chromosome> top;
    for (int i = 0; i < iteration; i++) {
        std::cout<< "итерация " << i + 1 << ":\n";
        top = algorithm.stepHybridAlgorithm();
        this->print(top);
    }
}


void Starter::print(std::vector<Chromosome> &top) {
    std::cout << top.size() << '\n';
    for (int i = 0; i < top.size(); i++) {
        std::cout << "Экземпляр " << i + 1 << ": ";
        //for (int j = 0; j < top[i].length; j++) {
        //    std::cout << top[i].genes[j] << ' ';
        //}
        top[i].print_test();
    }
    std::cout << "\n\n";
}
