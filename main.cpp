#include "Starter.h"


int main() {
    //std::srand(std::time(nullptr));
    Starter starter = Starter();
    starter.input();
    //std::cout << "-----testing initialisation\n";
    //Chromosome mom = Chromosome(0.001, 0, 20, 2, 10);
    //Chromosome dad = Chromosome(0.001, 0, 20, 3, 10);

    //mom.print_test();
    //dad.print_test();

    //std::cout << "\n\n-----testing recombination\n\n";
    //std::vector<Chromosome> kids = Chromosome::recombination(mom, dad, 0);
    //kids[0].print_test();
    //kids[1].print_test();

    //std::cout << "\n\n-----testing mutation\n\n";
    //mom.print_test();
    //mom.mutate();
    //mom.print_test();


    //std::cout << "\n\nПроверка множественных мутаций на отце\n\n";
    //for(int i = 0; i < 10; i++){
        //dad.print_test();
        //dad.mutate();

    //}
    //std::vector<double> s = {1.25, 1.78, 1.99};
    //Polynomial polynom(s, 19.4, 45);
    //polynom.print();
    return 0;
}
