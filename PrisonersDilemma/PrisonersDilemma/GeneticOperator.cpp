#include "GeneticOperator.h"

Crossover::Crossover()
{

}

chromosomePair Crossover::crossover(chromosomePair parents)
{
	int tmp1, tmp2, tmp3;
	tmp1 = (rand() % 1028) + 1;
	Sleep(1);
	tmp2 = (rand() % 100) * (rand() % 200);
	Sleep(1);
	tmp3 = (((rand() % 2048) * tmp2) + tmp1) % 4096;
	int breakingPoint = (tmp3 % 69) + 1;
	brokenChromosome parent1 = breakChromosome(breakingPoint, parents.first.getStrategy());
	brokenChromosome parent2 = breakChromosome(breakingPoint, parents.second.getStrategy());
	string strategyOff1 = parent1.first + parent2.second;
	string strategyOff2 = parent2.first + parent1.second;
	Chromosome child1(strategyOff1);
	Chromosome child2(strategyOff2);
	return make_pair(child1, child2);
}

brokenChromosome Crossover::breakChromosome(int breakingPoint, string parentsStrategy)
{
	brokenChromosome result;
	result.first = "";
	result.second = "";
	for (int i = 0; i < breakingPoint; i++)
		result.first += parentsStrategy[i];
	for (int i = breakingPoint; i < 70; i++)
		result.second += parentsStrategy[i];
	return result;
}

Mutation::Mutation()
{

}

Chromosome Mutation::mutation(Chromosome individual)
{
	string newStrategy = individual.getStrategy();
	bool different = true;
	vector<int> mutatedLocuses;
	int tmp1, tmp2, tmp3;
	tmp1 = (rand() % 1028) + 1;
	Sleep(1);
	tmp2 = (rand() % 100) * (rand() % 200);
	Sleep(1);
	tmp3 = (((rand() % 2048) * tmp2) + tmp1) % 4096;
	int numberOfLocuses = (tmp3 % 3) + 1;
	int mutationLocus;
	for (int i = 0; i < numberOfLocuses; i++)
	{
		do
		{
			mutationLocus = rand() % 70;
			for (int tmp : mutatedLocuses)
			{
				if (tmp == mutationLocus)
				{
					different = false;
					break;
				}
				else
					different = true;
			}
		} while (different == false);
		if (newStrategy[mutationLocus] == 'C')
			newStrategy[mutationLocus] = 'D';
		else
			newStrategy[mutationLocus] = 'C';
		mutatedLocuses.push_back(mutationLocus);
	}
	mutatedLocuses.empty();
	Chromosome mutated(newStrategy);
	return mutated;
}