#include "Chromosome.h"
#include <vector>

typedef std::pair<Chromosome, Chromosome> chromosomePair;
typedef std::pair<string, string> brokenChromosome;

class Crossover {
private:
	brokenChromosome breakChromosome(int breakingPoint, string parentsStrategy);
public:
	Crossover();
	chromosomePair crossover(chromosomePair parents);
};

class Mutation {
private:

public:
	Mutation();
	Chromosome mutation(Chromosome individual);
};