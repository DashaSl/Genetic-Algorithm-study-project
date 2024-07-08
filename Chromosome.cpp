#include "Chromosome.h"

//done
Chromosome::Chromosome(double probMutation, double down, double up, int number, int len) {
        this->estimate = DBL_MAX;
        this->number = number;
        this->probMutation = probMutation;
        this->length = len; 
        std::uniform_real_distribution<> dis(down, up);
        this->genes = {};
        this->down_border = down;
        this->up_border = up;
        this->max_mutation_step = MAX_MUT_STP;
        std::random_device rd;  // Will be used to obtain a seed for the random number engine
        std::mt19937_64 gen(rd());//генерирует случайное целое 
        for(int i = 0; i <this->length; i++){
                this->genes.push_back(dis(gen));
        }
};  

//done
void Chromosome::print_test(){
        std::cout << "-------------------\nChromosome data\n";
        std::cout << number << " " << probMutation << " " << length << '\n';
        std::cout << this->estimate <<' ' << this->max_mutation_step << '\n';
        std::cout << this->down_border <<' ' << this->up_border << '\n';
        for(auto val : this->genes) std::cout << val << ' ';
        std::cout << "-------------------\n";        
}

//done
std::vector<Chromosome> Chromosome::recombination(Chromosome parent1, Chromosome parent2, int method){
        std::vector<Chromosome> answer;
        if(method == 0){
                discr_recomb(parent1, parent2, answer);
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


//New recombination and mutation methods

//double random_double(double a, double b){
    
//}