/*
** Algorithm 6: Recursive + Parallel masks test without interruption
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

class Algorithm6
{
private:
	bool prima_test_end, prima_test_val,
		 secon_test_end, secon_test_val,
		 masks_test_end, masks_test_val;
	uint64_t it, index, n, m;
	vector<Link*> current_set;
	vector<uint64_t> fsets;
	vector<uint64_t> masks; // or patterns?
	Network* network;
	
	void find_fsets(uint64_t);
	void add_link(uint64_t);
	double calculate_interference(Node*, Node*);
	void print_interf();
	bool is_feasible();
	void masks_test();
	void primary_test();
	void secondary_test();
	double calculate_sinr(Link*);
	void del_link(uint64_t);
	
public:
	Algorithm6(Network*);
	vector<uint64_t> get_fsets();
	void print_fsets();
	void print_masks();
};
