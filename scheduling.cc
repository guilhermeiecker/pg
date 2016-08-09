#include "Network.h"
#include "Algorithm1.h"
#include "Algorithm2.h"

int main() {
	Network n(16, 2000.0, 300.0);
	n.print_links();
	
	//Algorithm1 a1(&n);
	Algorithm2 a2(&n);
	
	//a1.print_fsets();
	a2.print_fsets();
	return 0;
}
