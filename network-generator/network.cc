#include <iostream>
#include <fstream>

#include "Network.h"

using namespace std;

int main()
{
	Network* n;
	int lastm;
	float side;
	float area[4][65][30];
	ofstream f;
			
	const int nodes[4] = {16, 32, 64, 128};
	const float initial_sides[4] = {3000.0, 4500.0, 10500.0, 35000.0};

	for(int i = 0; i < 4; i++)
	{
		for(int seed = 0; seed < 30; seed++)
		{
			//cout << "i=" << i << " seed=" << seed << "..." << endl;
			side = initial_sides[i];
			lastm = 0;
			while((side>0)&&(lastm<65))
			{
				n = new Network(nodes[i], side, 350.0, seed);
				lastm = n->get_links().size();
				if((lastm>3)&&(lastm<65))
					area[i][lastm][seed] = side;
				side = side - 1.0;
				delete n;
			}
		}
	}
	
	f.open("network.txt");
	for(int i = 0; i < 4; i++)
	{
		f << nodes[i] << endl;
		for(int j = 0; j < 65; j++)
		{
			f << j << "\t";
			for(int k = 0; k < 30; k++)
			{
				f << area[i][j][k] << "\t";
			}
			f << endl;
		}
		f << endl;
	}
	f.close();	
}
