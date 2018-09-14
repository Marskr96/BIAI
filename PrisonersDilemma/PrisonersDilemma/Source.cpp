#include "EvolutionManager.h"
#include <fstream>

int main()
{
	int cycles, individuals;
	fstream file;
	file.open("Results.txt", ios::out);
	cout << "\nProvide number of cycles (20-200):";
	cin >> cycles;
	cout << "\nProvide number of individuals in population (20-100):";
	cin >> individuals;
	EvolutionManager manager(cycles, individuals);
	cout << "\n\nSTART\n\n";
	if (file.good())
	{
		file << "Starting ";
		manager.writeToFile(file);
	}
	vector<Chromosome> result = manager.operate();

	if (file.good())
	{
		file << "Finished ";
		manager.writeToFile(file);
	}
	file.close();
	cout << "END\n\n";
	system("Pause");
	return 0;
}
