#include <stdio.h>
#include "Network.h"

int main(int argc, char** argv)
{
	double a = strtod(argv[1], NULL);
	Network n(128, a, 300.0);
	return 0;
}
