#include <vector>

class Individ{
public:
    Individ();

    static Individ Crossingover(Individ& mother, Individ& father);

    static Individ Mutation(Individ& mother, Individ& father);

    static int HemmingDist(Individ& mother, Individ& father);

    static 

};


class Population{
private:
    	
    std::vector<int> numbers;
};
