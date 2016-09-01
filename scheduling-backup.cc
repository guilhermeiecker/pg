#include "Network.h"
#include "Algorithm2.h"

int main(int argc, char** argv) {
	uint64_t n, m, r;
	double pt, s;
	clock_t t, tt;

	const double A[6][5] = {
		{530.0,   0.0,     0.0,     0.0,    0.0},
		{1600.0,  1000.0,  590.0,   0.0,    0.0},
		{2000.0,  1750.0,  1570.0,  940.0,  574.75},
		{4500.0,  3000.0,  2440.0,  1925.0, 1440.0},
		{10500.0, 9000.0,  7000.0,  4700.0, 3190.0},
		{35000.0, 24000.0, 18000.0, 8880.0, 6210.0}
	};
	
	n = (uint64_t)atoi(argv[1]);
	m = (uint64_t)atoi(argv[2]);
	r = (uint64_t)atoi(argv[3]);
	pt= (double)atof(argv[4]);
	s = A[(uint64_t)log2(n) - 2][(uint64_t)log2(m) - 2];
	
	Network* g = new Network(n, s, pt);
	Algorithm2* a2 = new Algorithm2(g);
	
	if(n==4)
	{
		cout << "A\tn\tm\t";
		for (int i = 1; i <= 30; i++)
			cout << "TM" << i << "\tTP" << i << "\tTS" << i << "\tTT" << i << "\t";
		cout << endl;

	}

	if(r==1)
		cout << "1\t" << n << "\t" << m;

	cout << "\t0.0\t0.0\t0.0";
	t = clock();
	a2->find_fset();
	tt = clock();

	cout << "\t" << ((double)(tt - t))/CLOCKS_PER_SEC;

	if(r==30)
		cout << endl;

	return 0;
}
