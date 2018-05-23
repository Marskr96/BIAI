#include "Chromosome.h"

Chromosome::Chromosome()
{
	srand(time(0));
	char c;
	strategy = "";
	int tmp1, tmp2, tmp3;
	for (int i = 0; i < 70; i++)
	{
		tmp1 = (rand() % 1028) + 1;
		Sleep(2);
		tmp2 = (rand() % 100) * (rand() % 200);
		Sleep(2);
		tmp3 = (((rand() % 2048) * tmp2) + tmp1) % 2;
		if (tmp3 == 0)
			c = 'C';
		else
			c = 'D';
		strategy = strategy + c;
	}
	timesReproduced = 0;
	rawScore = 0;
	fitness = 0;
}

Chromosome::Chromosome(string _strategy)
{
	strategy = _strategy;
	timesReproduced = 0;
	rawScore = 0;
	fitness = 0;
}

char & Chromosome::operator[](int index)
{
	return strategy[index];
}

void Chromosome::setFitness(double _fitness)
{
	fitness = _fitness;
}

double Chromosome::getFitness() const
{
	return fitness;
}

string Chromosome::getStrategy()
{
	return strategy;
}

void Chromosome::display()
{
	for (int i = 0; i < 6; i++)
	{
		cout << strategy[i];
	}
	cout << "\t";
	for (int i = 6; i < 70; i++)
	{
		cout << strategy[i];
	}
	cout << "\t" << rawScore << "\t" << fitness;
	cout << "\n";
}

void Chromosome::writeToFile(fstream &file)
{
	for (int i = 0; i < 6; i++)
	{
		file << strategy[i];
	}
	file << "\t";
	for (int i = 6; i < 70; i++)
	{
		file << strategy[i];
	}
	file << "\n";
}

void Chromosome::reproduced()
{
	timesReproduced++;
}

int Chromosome::getTimesReproduced()
{
	return timesReproduced;
}

void Chromosome::addToRawScore(int score)
{
	rawScore += score;
}

int Chromosome::getRawScore()
{
	return rawScore;
}

Chromosome::~Chromosome()
{
	
}