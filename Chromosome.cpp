#include "Chromosome.h"


//done

Chromosome::Chromosome(double probMutation, double down, double up, int number, int len, int methodmut, int methodrecomb, int age, int birthdate) {
        this->metodRecomb = methodrecomb;
        this->methodMut = methodmut; 
        this->age = age;
        this->birthDate = birthdate;
        this->estimate = DBL_MAX;
        this->number = number;
        this->probMutation = probMutation;
        this->length = len; 
        std::uniform_real_distribution<> dis(down, up);
        this->genes = {};
        this->down_border = down;
        this->up_border = up;
        this->max_mutation_step = (up - down)/10;
        this->birthDate = birthDate;
        this->age = age;
        std::random_device rd;  // Will be used to obtain a seed for the random number engine
        std::mt19937_64 gen(rd());//генерирует случайное целое 
        for(int i = 0; i <this->length; i++){
                this->genes.push_back(dis(gen));
        }
};  

//done
std::vector<Chromosome> Chromosome::recombination(Chromosome parent1, Chromosome parent2, int method){
        std::vector<Chromosome> answer;
        if(method == 0){
                discr_recomb(parent1, parent2, answer);
        }else{
                inter_recomb(parent1, parent2, answer);
        }
        return answer;
}

//done
double Chromosome::new_gene(double old_gene){
        std::random_device rd;  // Will be used to obtain a seed for the random number engine
        std::mt19937_64 gen(rd());//генерирует случайное целое
        std::uniform_real_distribution<> dis(old_gene - max_mutation_step, old_gene + max_mutation_step);

        double answer = dis(gen);

        return answer;

}

void Chromosome::mutate(int method){
        if(method == 0){
                this->mutate_dumb(); 
        }else{
                this->mutate_better();
        }
}

void Chromosome::mutate_dumb(){
        std::random_device rd;  // Will be used to obtain a seed for the random number engine
        std::mt19937_64 gen(rd());//генерирует случайное целое
        std::uniform_real_distribution<> dis(0, 1);
        for(auto& val: this->genes){
                if(dis(gen) < probMutation){
                        val = new_gene(val);
                }
        }
}

//done
void Chromosome::discr_recomb(Chromosome parent1, Chromosome parent2, std::vector<Chromosome> &answer){

        Chromosome kid1 = parent1;
        Chromosome kid2 = parent2;
        kid1.genes = {};
        kid2.genes = {};
        for(int i = 0; i < parent1.genes.size(); i++){
                int probability = std::rand()%2;
                if(probability){
                        kid1.genes.push_back(parent1.genes[i]);
                }else{
                        kid1.genes.push_back(parent2.genes[i]);
                }


                probability = std::rand()%2;
                if(probability){
                        kid2.genes.push_back(parent1.genes[i]);
                }else{
                        kid2.genes.push_back(parent2.genes[i]);
                }
        }

        answer.push_back(kid1);
        answer.push_back(kid2);
        //number - обновляется в популяции
                //вероятность мутации тоже одинаковая
}


//Нововведения

double random_number(double a, double b){
        std::random_device rd;  // Will be used to obtain a seed for the random number engine
        std::mt19937_64 gen(rd());//генерирует случайное целое
        std::uniform_real_distribution<> dis(a, b);

        double answer = dis(gen);

        return answer;        
}

void Chromosome::inter_recomb(Chromosome parent1, Chromosome parent2, std::vector<Chromosome> &answer){
        Chromosome kid1 = parent1;
        Chromosome kid2 = parent2;
        kid1.genes = {};
        kid2.genes = {};
        for(int i = 0; i < parent1.genes.size(); i++){
                double a = random_number(-0.25, 1.25);
                double new_val = parent1.genes[i] + a*(parent2.genes[i] - parent1.genes[i]);
                kid1.genes.push_back(new_val);
                a = random_number(-0.25, 1.25);
                new_val = parent1.genes[i] + a*(parent2.genes[i] - parent1.genes[i]);
                kid2.genes.push_back(new_val);
        }

        answer.push_back(kid1);
        answer.push_back(kid2);        
}

double calc_d(){
        double ans = 0;
        double a;
        int m = 20;
        for(int i = 0; i < m; i++){
                if(random_number(0, 1) < 0.05) a = 1; else a = 0;
                ans += a*pow(2, -i);
        }
        return ans;
}

void Chromosome::mutate_better(){
        std::random_device rd;  // Will be used to obtain a seed for the random number engine
        std::mt19937_64 gen(rd());//генерирует случайное целое
        std::uniform_real_distribution<> dis(0, 1);
        double a = (this->up_border - this->down_border)/2;
        for(auto& val: this->genes){
                if(dis(gen) < probMutation){
                        int sign = 1;
                        if(floor(random_number(0, 2)) < 1) sign = -1;
                        val += sign*a*calc_d();
                }
        }
}