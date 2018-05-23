#pragma once
#include <string>
#include <fstream>
#include <random>
#include <ctime>
#include <functional>
#include <cstdlib>
#include <iostream>
#include <Windows.h>

using namespace std;

class Chromosome{
private:
	string strategy;
	int rawScore;
	double fitness;
	int timesReproduced;

public:
	Chromosome();
	Chromosome(string _strategy);
	~Chromosome();
	char& operator[](int index);
	void setFitness(double _fitness);
	double getFitness() const;
	string getStrategy();
	void display();
	void writeToFile(fstream &file);
	void reproduced();
	void addToRawScore(int score);
	int getRawScore();
	int getTimesReproduced();
};

struct Better
{
	inline bool operator() (const Chromosome& struct1, const Chromosome& struct2)
	{
		return (struct1.getFitness() > struct2.getFitness());
	}
};