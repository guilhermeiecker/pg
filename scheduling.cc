#include <time.h>
#include "Network.h"
#include "Algorithm1.h"
#include "Algorithm2.h"
#include "Algorithm3.h"
#include "Algorithm4.h"
#include "Algorithm5.h"
#include "Algorithm6.h"

int main() {
	Network n(16, 1570, 300.0);
	
	clock_t t1, t2, t3, t4, t5, t6, t7;
	
	t1 = clock();
	Algorithm1 a1(&n);
	t2 = clock();
	Algorithm2 a2(&n);
	t3 = clock();
	Algorithm3 a3(&n);
	t4 = clock();
	Algorithm4 a4(&n);
	t5 = clock();
	Algorithm5 a5(&n);
	t6 = clock();
	Algorithm6 a6(&n);
	t7 = clock();
	
	cout << "Algorithm 1 Time Elapse: " << ((double)(t2 - t1))/CLOCKS_PER_SEC << " seconds" << endl;
	cout << "Algorithm 2 Time Elapse: " << ((double)(t3 - t2))/CLOCKS_PER_SEC << " seconds" << endl;
	cout << "Algorithm 3 Time Elapse: " << ((double)(t4 - t3))/CLOCKS_PER_SEC << " seconds" << endl;
	cout << "Algorithm 4 Time Elapse: " << ((double)(t5 - t4))/CLOCKS_PER_SEC << " seconds" << endl;
	cout << "Algorithm 5 Time Elapse: " << ((double)(t6 - t5))/CLOCKS_PER_SEC << " seconds" << endl;
	cout << "Algorithm 6 Time Elapse: " << ((double)(t7 - t6))/CLOCKS_PER_SEC << " seconds" << endl;
	
	a1.print_fsets();
	a2.print_fsets();
	a3.print_fsets();
	a4.print_fsets();
	a5.print_fsets();
	a6.print_fsets();
	
	return 0;
}
