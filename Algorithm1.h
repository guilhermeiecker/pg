/*
** Algorithm 1: 
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
	
	void print_currset();
	void clr_currset();
	void decode_int(uint64_t);
	double calculate_sinr(Link*);
	bool primary_test();
	bool secondary_test();
	bool is_feasible();
	void find_fsets();
	void update_interference();
	double calculate_interference(Node*, Node*);
	
public:
	Algorithm1(Network*);
	vector<uint64_t> get_fsets();
	void print_fsets();
};

