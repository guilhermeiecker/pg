#include <iomanip>

#include "Network.h"
#include "Algorithm6.h"

#define TPOWER 300.0

int main(int argc, char** argv) {
	uint64_t n, m;
	double tp, s;
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
	tp= TPOWER;
	s = A[(uint64_t)log2(n) - 2][(uint64_t)log2(m) - 2];
	
	if(s != 0.0)
	{
		Network* g = new Network(n, s, tp);
		Algorithm6* a = new Algorithm6(g);
	
		t = clock();
		a->find_fset(0);
		tt = clock();
			
		cout << fixed << setprecision(6) << ((double)(tt - t))/CLOCKS_PER_SEC;
	}
	else
	{
		cout << "-";
	}
	
	return 0;
}
