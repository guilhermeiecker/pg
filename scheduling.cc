#include <time.h>
#include "Network.h"
#include "Algorithm1.h"
#include "Algorithm2.h"
#include "Algorithm3.h"
#include "Algorithm4.h"
#include "Algorithm5.h"
#include "Algorithm6.h"

int main(int argc, char** argv) {
	Network n(atoi(argv[1]), strtod(argv[2], NULL), strtod(argv[3], NULL));
	
	Algorithm1 a1(&n);
	Algorithm2 a2(&n);
	Algorithm3 a3(&n);
	Algorithm4 a4(&n);
	Algorithm5 a5(&n);
	Algorithm6 a6(&n);
	
	clock_t t1, t2, t3, t4, t5, t6, t7;
	

	t1 = clock();	cout << "alg1" << endl;
	a1.find_fset();
	t2 = clock();	cout << "alg2" << endl;
	a2.find_fset();
	t3 = clock();	cout << "alg3" << endl;
	a3.find_fset();
	t4 = clock();	cout << "alg4" << endl;
	a4.find_fset(0);
	t5 = clock();	cout << "alg5" << endl;
	a5.find_fset(0);
	t6 = clock();	cout << "alg6" << endl;
	a6.find_fset(0);
	t7 = clock();
	
	cout << "Algorithm 1 Time Elapse: " << ((double)(t2 - t1))/CLOCKS_PER_SEC << " seconds" << endl;
	cout << "Algorithm 2 Time Elapse: " << ((double)(t3 - t2))/CLOCKS_PER_SEC << " seconds" << endl;
	cout << "Algorithm 3 Time Elapse: " << ((double)(t4 - t3))/CLOCKS_PER_SEC << " seconds" << endl;
	cout << "Algorithm 4 Time Elapse: " << ((double)(t5 - t4))/CLOCKS_PER_SEC << " seconds" << endl;
	cout << "Algorithm 5 Time Elapse: " << ((double)(t6 - t5))/CLOCKS_PER_SEC << " seconds" << endl;
	cout << "Algorithm 6 Time Elapse: " << ((double)(t7 - t6))/CLOCKS_PER_SEC << " seconds" << endl;
	
	
	a1.print_fset();
	a2.print_fset();
	a3.print_fset();
	a4.print_fset();
	a5.print_fset();
	a6.print_fset();
	
	return 0;
}
