#include <iomanip>			// std::setprecision
#include <fstream>      // std::ifstream

#include "Network.h"
#include "Iterative.h"

int main(int argc, char** argv) {
	ifstream f("networks.txt");
	uint64_t n, m;
	clock_t t, tt;
	double s;
	double area[61][4];

	for (int i = 0; i < 61; i++)
		for (int j = 0; j < 4; j++)
			f >> area[i][j];

	n = (uint64_t)atoi(argv[1]);
	m = (uint64_t)atoi(argv[2]);

	s = area[m-4][(uint64_t)log2(n) - 4];

	Network* g = new Network(n, s, 300.0);
	Iterative* a = new Iterative(g);

	t = clock();
	a->find_fset();
	tt = clock();

	cout << fixed << setprecision(6) << ((double)(tt - t))/CLOCKS_PER_SEC;

	f.close();

	return 0;
}
