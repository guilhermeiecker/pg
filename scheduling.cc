#include <time.h>
#include "Network.h"
#include "Algorithm1.h"
#include "Algorithm2.h"
#include "Algorithm3.h"
#include "Algorithm4.h"
#include "Algorithm5.h"
#include "Algorithm6.h"

int main() {
	Network n(32, 2440, 300.0);
	
	clock_t t1, t2, t3, t4;
	
	t1 = clock();
	Algorithm4 a4(&n);
	t2 = clock();
	Algorithm5 a5(&n);
	t3 = clock();
	Algorithm6 a6(&n);
	t4 = clock();

	cout << "Algorithm 4 Time Elapse: " << ((double)(t2 - t1))/CLOCKS_PER_SEC << " seconds" << endl;
	cout << "Algorithm 5 Time Elapse: " << ((double)(t3 - t2))/CLOCKS_PER_SEC << " seconds" << endl;
	cout << "Algorithm 6 Time Elapse: " << ((double)(t4 - t3))/CLOCKS_PER_SEC << " seconds" << endl;
	//a1.print_fsets();
	//a2.print_fsets();
	//a3.print_fsets();
	//a3.print_masks();
	//a4.print_fsets();
	//a5.print_fsets();
	//a6.print_fsets();
	
	return 0;
}
