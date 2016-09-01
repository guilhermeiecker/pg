#include <time.h>
#include <fstream>
#include "Network.h"
#include "Algorithm1.h"
#include "Algorithm2.h"
#include "Algorithm3.h"
#include "Algorithm4.h"
#include "Algorithm5.h"
#include "Algorithm6.h"

int main(int argc, char** argv) {
	ofstream f;
	f.open("results.txt");
	
	Network* n = new Network(argv[1], argv[2], argv[3]);
	Algorithm1 a1(n);
	Algorithm2 a2(n);
	Algorithm3 a3(n);
	Algorithm4 a4(n);
	Algorithm5 a5(n);
	Algorithm6 a6(n);
	
	int nodes, links, algorithm, round;
	double time[4][5][6][10];
	double area[4][5] = {{2000.0,  1750.0,  1570.0,  940.0,  574.75},
						 {4500.0,  3000.0,  2440.0,  1925.0, 1440.0},
						 {10500.0, 9000.0,  7000.0,  4700.0, 3190.0},
						 {35000.0, 24000.0, 18000.0, 8880.0, 6210.0}};
	
	clock_t t1, t2;
	
	for (int i = 0; i < 3; i++)
	{
		nodes = (int)pow(2,i+4);
		for (int j = 0; j < 4; j++)
		{
			links = (int)pow(2,j+2);
			n = new Network(nodes, area[i][j], 300.0);
			for (int k = 0; k< 10; k++)
			{
				cout << "calculating execution time #" << k+1 << " for network with n=" << nodes << ", m=" << links << "..." << endl;
				round = 0;
				
				t1 = clock();
				a1 = new Algorithm1(n);
				t2 = clock();
				time[i][j][round++][k] = ((double)(t2 - t1))/CLOCKS_PER_SEC; 
				delete a1;
				
				t1 = clock();
				a2 = new Algorithm2(n);
				t2 = clock();
				time[i][j][round++][k] = ((double)(t2 - t1))/CLOCKS_PER_SEC;
				delete a2;
							
				t1 = clock();
				a3 = new Algorithm3(n);
				t2 = clock();
				time[i][j][round++][k] = ((double)(t2 - t1))/CLOCKS_PER_SEC; 
				delete a3;
				
				t1 = clock();
				a4 = new Algorithm4(n);
				t2 = clock();
				time[i][j][round++][k] = ((double)(t2 - t1))/CLOCKS_PER_SEC; 
				delete a4;
				
				t1 = clock();
				a5 = new Algorithm5(n);
				t2 = clock();
				time[i][j][round++][k] = ((double)(t2 - t1))/CLOCKS_PER_SEC; 
				delete a5;
				
				t1 = clock();
				a6 = new Algorithm6(n);
				t2 = clock();
				time[i][j][round++][k] = ((double)(t2 - t1))/CLOCKS_PER_SEC; 
				delete a6;
			}
		}
	}

	for (int i = 0; i < 3; i++)
	{
		nodes = (int)pow(2,i+4);
		for (int j = 0; j < 4; j++)
		{
			links = (int)pow(2,j+2);
			for (int h = 0; h < 6; h++)	
			{
				algorithm = h + 1; 
				f << nodes << "\t" << links << "\t" << area[i][j] << "\t" << algorithm;
				for (int k = 0; k < 10; k++)
				{
					f << "\t" << time[i][j][h][k];
				}
				f << endl;
			}
		}
	}
	
	f.close();
	
	return 0;
}
