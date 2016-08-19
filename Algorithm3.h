/*
** Algorithm 2: Iterative + Sequential masks test
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
	bool prima_test_end, prima_test_val,
		 secon_test_end, secon_test_val,
		 masks_test_end, masks_test_val;
	uint64_t it, index, n, m;
	vector<Link*> current_set;
	vector<uint64_t> feasible_sets;
	vector<uint64_t> masks;
	Network* network;
	
	void decode_int(uint64_t);
	void update_interference();	
	double calculate_interference(Node*, Node*);
	bool is_feasible();
	void masks_test();
	void primary_test();
	void secondary_test();
	double calculate_sinr(Link*);				
	void clr_currset();
	void print_currset();
		
public:
	Algorithm3(Network*);
	void find_fsets();
	vector<uint64_t> get_fsets();
	void print_fsets();
	void clear_fsets();
};

