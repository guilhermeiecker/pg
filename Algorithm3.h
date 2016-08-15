/*
** Algorithm 3: Iterative + Parallel masks test
**
*/

#pragma once

#include <stdint.h>
#include <vector>
#include <math.h>
#include <thread>
#include "Node.h"
#include "Link.h"
#include "Network.h"

class Algorithm3
{
private:
	bool intrf_test_end, intrf_test_val,
		 masks_test_end, masks_test_val,
		 result;
	uint64_t it, index, n, m;
	vector<Link*> current_set;
	vector<uint64_t> masks; // or patterns?
	vector<uint64_t> feasible_sets;
	Network* network;
	
	void find_fsets();
	void decode_int(uint64_t);
	void update_interference();	
	double calculate_interference(Node*, Node*);
	bool is_feasible();	
	void intrf_test();
	bool primary_test();
	bool secondary_test();
	void masks_test();
	double calculate_sinr(Link*);				
	void clr_currset();
	void print_currset();
		
public:
	Algorithm3(Network*);
	vector<uint64_t> get_fsets();
	void print_fsets();
};

