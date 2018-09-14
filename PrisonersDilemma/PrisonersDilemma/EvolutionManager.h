#include "GeneticOperator.h"
#include <memory>

typedef std::pair<int, int> scoreOfComparison;

class EvolutionManager{
private:
	int numberOfCycles;
	int reward;
	int sucker;
	int temptation;
	int penalty;
	int numberOfIndividuals;
	int numberOfMoves;
	double chanceOfCrossover;
	double chanceOfMutation;
	vector<Chromosome> population;
	int roundOfTournament(int numberOfIndividual);
	scoreOfComparison compareStrategies(string strategy1, string strategy2);
	int historyToNumber(string history);
	double calculateFitness(int minRawScore, int avgRawScore, int rawScore);
	bool chance(double prob);

public:
	EvolutionManager();
	EvolutionManager(int _numberOfCycles, int _numberOfIndividuals, int _numberOfMoves = 30, double _chanceOfCrossover = 0.95, double _chanceOfMutation = 0.1, int _reward = 3, int _sucker = 0, 
		int _temptation = 5, int _penalty = 1);
	void display();
	void writeToFile(fstream &file);
	vector<Chromosome> operate();	
	~EvolutionManager();
};