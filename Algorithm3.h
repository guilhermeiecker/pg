/*
** Algorithm 2: Iterative + Sequential mset test
**
*/

#pragma once

#include <stdint.h>
#include <vector>
#include <math.h>
#include <omp.h>
#include "Node.h"
#include "Link.h"
#include "Network.h"

class Algorithm3
{
private:
	bool ptest_val, stest_val, mtest_val, stop;
	uint64_t it, index, n, m, limit, inc;
	vector<Link*> cset;
	vector<uint64_t> fset;
	vector<uint64_t> mset;
	Network* network;
	
	void decode(uint64_t);
	void update_interference();	
	double calculate_interference(Node*, Node*);
	bool is_feasible();
	void masks_test();
	void primary_test();
	void secondary_test();
	double calculate_sinr(Link*);				
	void clear_cset();
	void print_cset();
		
public:
	Algorithm3(Network*);
	void find_fset();
	vector<uint64_t> get_fset();
	void print_fset();
	void clear_fset();
};

