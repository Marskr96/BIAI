#include "EvolutionManager.h"

EvolutionManager::EvolutionManager()
{

}

EvolutionManager::EvolutionManager(int _numberOfCycles, int _numberOfIndividuals, int _numberOfMoves, double _chanceOfCrossover, double _chanceOfMutation, int _reward, int _sucker,
	int _temptation, int _penalty)
{
	numberOfCycles = _numberOfCycles;
	numberOfIndividuals = _numberOfIndividuals;
	chanceOfCrossover = _chanceOfCrossover;
	chanceOfMutation = _chanceOfMutation;
	reward = _reward;
	sucker = _sucker;
	temptation = _temptation;
	penalty = _penalty;
	numberOfMoves = _numberOfMoves;

	for (int i = 0; i < numberOfIndividuals; i++)
	{
		population.push_back(Chromosome());
		Sleep(5);
	}
}

void EvolutionManager::display()
{
	cout << "\nPopulation:\n";
	for (int i = 0; i < population.size(); i++)
		population.at(i).display();
}

void EvolutionManager::writeToFile(fstream &file)
{
	file << "Population:\n";
	for (int i = 0; i < population.size(); i++)
		population.at(i).writeToFile(file);
}

vector<Chromosome> EvolutionManager::operate()
{
	shared_ptr<Crossover> crossingover(new Crossover);
	shared_ptr<Mutation> mutating(new Mutation);
	vector<Chromosome> newPopulation;
	chromosomePair parents;
	chromosomePair offspring;
	int averageRawScore;
	int minRawScore;
	int sumRawScore;
	int partner;
	double fitness;
	double avgFitness;
	for (int i = 0; i < numberOfCycles; i++)
	{
		for (int j = 0; j < population.size(); j++)
		{
			population.at(j).addToRawScore(roundOfTournament(j));
		}
		sumRawScore = population.at(0).getRawScore();
		minRawScore = population.at(0).getRawScore();
		for (int j = 1; j < population.size(); j++)
		{
			sumRawScore += population.at(j).getRawScore();
			if (minRawScore > population.at(j).getRawScore())
				minRawScore = population.at(j).getRawScore();
		}
		averageRawScore = sumRawScore / numberOfIndividuals;
		double tmp = 0;
		for (int j = 0; j < population.size(); j++)
		{
			fitness = calculateFitness(minRawScore, averageRawScore, population.at(j).getRawScore());
			population.at(j).setFitness(fitness);
			tmp += fitness;
		}
		avgFitness = tmp / population.size();
		sort(population.begin(), population.end(), Better());
		cout << "\nCycle " << i + 1;
		this->display();
		population.erase(population.begin() + (int)(numberOfIndividuals*0.75), population.end());
		for (int j = 0; newPopulation.size() < numberOfIndividuals; j++)
		{
			if (j >= population.size())
				j = 0;
			if (population.at(j).getTimesReproduced() < 2)
			{
				if (newPopulation.size() + 1 == numberOfIndividuals)
				{
					newPopulation.push_back(population.at(j));
				}
				else
				{
					int tmp1, tmp2, tmp3;
					do
					{
						tmp1 = (rand() % 1028) + 1;
						Sleep(1);
						tmp2 = (rand() % 100) * (rand() % 200);
						Sleep(1);
						tmp3 = (((rand() % 2048) * tmp2) + tmp1) % population.size();
						partner = tmp3;
					} while (population.at(partner).getStrategy() == population.at(j).getStrategy() || population.at(partner).getTimesReproduced() > 1);
					parents = make_pair(population.at(j), population.at(partner));
					population.at(j).reproduced();
					population.at(partner).reproduced();
					if (chance(chanceOfCrossover))
						offspring = crossingover->crossover(parents);
					else
						offspring = parents;
					if (chance(chanceOfMutation))
						offspring.first = mutating->mutation(offspring.first);
					if (chance(chanceOfMutation))
						offspring.second = mutating->mutation(offspring.second);
					newPopulation.push_back(offspring.first);
					newPopulation.push_back(offspring.second);
				}
			}
		}
		population.clear();
		for (Chromosome c : newPopulation)
		{
			population.push_back(c);
		}
		newPopulation.clear();
	}
	
	return population;
}

bool EvolutionManager::chance(double prob)
{
	int number = prob * 10000;
	int random = rand() % 10000;
	if (random < number)
		return true;
	else
		return false;
}

double EvolutionManager::calculateFitness(int minRawScore, int avgRawScore, int rawScore)
{
	double a, b, fitness;
	if (avgRawScore - minRawScore != 0)
	{
		a = (avgRawScore) / (avgRawScore - minRawScore);
		b = -(minRawScore)*(avgRawScore / (avgRawScore - minRawScore));
	}
	else
	{
		a = (avgRawScore) / (avgRawScore - minRawScore + 0.0001);
		b = -(minRawScore)*(avgRawScore / (avgRawScore - minRawScore + 0.0001));
	}
	fitness = (a*rawScore) + b;

	return fitness;
}

int EvolutionManager::roundOfTournament(int numberOfIndividual)
{
	scoreOfComparison scoreOfBothIndividuals;
	int rawScore = 0;
	for (int i = 0; i < numberOfIndividuals; i++)
	{
		if (i != numberOfIndividual)
		{
			scoreOfBothIndividuals = compareStrategies(population.at(numberOfIndividual).getStrategy(), population.at(i).getStrategy());
			rawScore += scoreOfBothIndividuals.first;
			population.at(i).addToRawScore(scoreOfBothIndividuals.second);
		}
	}
	return rawScore;
}

scoreOfComparison EvolutionManager::compareStrategies(string strategy1, string strategy2)
{
	int move1, move2;
	int score1 = 0, score2 = 0;
	string history1 = "", history2 = "";
	for (int i = 0; i < 6; i++)
	{
		history1 += strategy1[i];
		history2 += strategy2[i];
	}
	for (int i = 0; i < numberOfMoves; i++)
	{
		move1 = historyToNumber(history1) + 6;
		move2 = historyToNumber(history2) + 6;
		if (strategy1[move1] == 'C' && strategy2[move2] == 'C')
		{
			score1 += reward;
			score2 += reward;
		}
		if (strategy1[move1] == 'C' && strategy2[move2] == 'D')
		{
			score1 += sucker;
			score2 += temptation;
		}
		if (strategy1[move1] == 'D' && strategy2[move2] == 'C')
		{
			score1 += temptation;
			score2 += sucker;
		}
		if (strategy1[move1] == 'D' && strategy2[move2] == 'D')
		{
			score1 += penalty;
			score2 += penalty;
		}
		history1.erase(0, 2);
		history2.erase(0, 2);
		history1 = history1 + (char)strategy1[move1] + (char)strategy2[move2];
		history2 = history2 + (char)strategy2[move2] + (char)strategy1[move1];
	}
	return make_pair(score1, score2);
}

int EvolutionManager::historyToNumber(string history)
{
	int number = 0;
	if (history[0] == 'D')
		number += 32;
	if (history[1] == 'D')
		number += 16;
	if (history[2] == 'D')
		number += 8;
	if (history[3] == 'D')
		number += 4;
	if (history[4] == 'D')
		number += 2;
	if (history[5] == 'D')
		number += 1;

	return number;
}

EvolutionManager::~EvolutionManager()
{

}