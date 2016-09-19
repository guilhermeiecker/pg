#include <iomanip>			// std::setprecision
#include <fstream>      // std::ifstream

#include "Network.h"
#include "Recursive.h"

int main(int argc, char** argv) {
	ifstream f(argv[4]);
	uint64_t n, m, r;
	clock_t t, tt;
	double s;
	double area[61][4];

	for (int i = 0; i < 61; i++)
		for (int j = 0; j < 4; j++)
			f >> area[i][j];

	n = (uint64_t)atoi(argv[1]);
	m = (uint64_t)atoi(argv[2]);
	r = (uint64_t)atoi(argv[3]);
	s = area[m-4][(uint64_t)log2(n) - 4];
	
	if(s!=0)
        {
                Network* g = new Network(n, s, 350.0, r);
                Recursive* a = new Recursive(g);

                t = clock();
                a->find_fset(0);
                tt = clock();

                cout << fixed << setprecision(6) << ((double)(tt - t))/CLOCKS_PER_SEC;
        }
        else
        {
                cout << 0.0;
        }

	f.close();

	return 0;
}
