#include "EvolutionManager.h"
#include <fstream>

int main()
{
	fstream file;
	file.open("Result.txt", ios::out);
	EvolutionManager manager(40, 100, 20);
	cout << "START\n\n";
	manager.display();
	if (file.good())
	{
		file << "Starting ";
		manager.writeToFile(file);
	}
	vector<Chromosome> result = manager.operate();

	cout << "\n\nFinished Population:\n\n";
	manager.display();
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
