/*
** Algorithm 1: Simple Iterative
**
*/

#pragma once

#include <stdint.h>
#include <vector>
#include <math.h>
#include "Node.h"
#include "Link.h"
#include "Network.h"

class Algorithm1
{
private:
	uint64_t it, index, n, m;
	vector<Link*> current_set;
	vector<uint64_t> feasible_sets;
	Network* network;
	
	void find_fsets();
	void decode_int(uint64_t);
	void update_interference();	
	double calculate_interference(Node*, Node*);
	bool is_feasible();	
	bool primary_test();
	bool secondary_test();
	double calculate_sinr(Link*);				
	void clr_currset();
	void print_currset();
		
public:
	Algorithm1(Network*);
	vector<uint64_t> get_fsets();
	void print_fsets();
};

