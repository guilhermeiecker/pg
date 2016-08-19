#include <time.h>
#include <string>
#include <fstream>
#include <stdlib.h>
#include "Network.h"
#include "Algorithm1.h"
#include "Algorithm2.h"
#include "Algorithm3.h"
#include "Algorithm4.h"
#include "Algorithm5.h"
#include "Algorithm6.h"

int main(int argc, char** argv) {
	ofstream f;
	string name("n");
	name = name + argv[1] + "m" + argv[2] + ".txt";
	f.open(name);
	
	Network n((uint64_t)atoi(argv[1]), (double)atof(argv[3]), 300.0);

	Algorithm1* a1 = new Algorithm1(&n);
	Algorithm2* a2 = new Algorithm2(&n);
	Algorithm3* a3 = new Algorithm3(&n);
	Algorithm4* a4 = new Algorithm4(&n);
	Algorithm5* a5 = new Algorithm5(&n);
	Algorithm6* a6 = new Algorithm6(&n);

	clock_t t1, t2, t3, t4, t5, t6, t7;
	
	f << "round\talorithm1\talgorithm2\talgorithm3\talgorithm4\talgorithm5\talgorithm6" << endl;
	for (int i = 0; i < 30; i++)
	{
		cout << "Round " << i << "..." << endl;
		t1 = clock();
		a1->find_fsets();
		t2 = clock();
		a2->find_fsets();
		t3 = clock();
		a3->find_fsets();
		t4 = clock();
		a4->find_fsets(0);
		t5 = clock();
		a5->find_fsets(0);
		t6 = clock();
		a6->find_fsets(0);
		t7 = clock();
		
		f << i+1 << "\t" << ((double)(t2 - t1))/CLOCKS_PER_SEC << 
					"\t" << ((double)(t3 - t2))/CLOCKS_PER_SEC <<
					"\t" << ((double)(t4 - t3))/CLOCKS_PER_SEC <<
					"\t" << ((double)(t5 - t4))/CLOCKS_PER_SEC <<
					"\t" << ((double)(t6 - t5))/CLOCKS_PER_SEC <<
					"\t" << ((double)(t7 - t6))/CLOCKS_PER_SEC << endl;
		
		a1->clear_fsets();
		a2->clear_fsets();
		a3->clear_fsets();
		a4->clear_fsets();
		a5->clear_fsets();
		a6->clear_fsets();
	}
	
	f.close();
	
	return 0;
}
