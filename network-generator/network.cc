#include "Network.h"

using namespace std;

int main()
{
	Network* n;
	int lastm;
	float side;
	float area[4][65][30];
			
	const int nodes[4] = {16, 32, 64, 128};
	const float initial_sides[4] = {2000.0, 4500.0, 10500.0, 35000.0};

	for(int i = 0; i < 4; i++)
	{
		cout << "Testing for n=" << nodes[i] << " and initial_side=" << initial_sides[i] << "..." << endl;
		for(int seed = 0; seed < 30; seed++)
		{
			cout << "\tTesting for seed=" << seed << "..." << endl;
			side = initial_sides[i];
			lastm = 0;
			while((side>0)&&(lastm<65))
			{
				n = new Network(nodes[i], side, 350.0, seed);
				lastm = n->get_links().size();
				if(lastm<65)
					area[nodes[i]][lastm][seed] = side;
				cout << "\t\tside=" << side << " has " << lastm << " links." << endl; 
				side = side - 0.25;
			}
		}
	}
}
