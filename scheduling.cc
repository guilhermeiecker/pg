#include "Network.h"
#include "Algorithm1.h"
#include "Algorithm2.h"
#include "Algorithm3.h"

int main() {
	Network n(16, 2000.0, 350.0);
	
	//Algorithm1 a1(&n);
	//Algorithm2 a2(&n);
	Algorithm3 a3(&n);
	
	//a1.print_fsets();
	//a2.print_fsets();
	a3.print_fsets();
	a3.print_masks();
	return 0;
}
