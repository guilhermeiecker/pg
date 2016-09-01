#pragma once

#include "Node.h"
#include "Link.h"
#include "Network.h"

class Algorithm2
{
private:
	uint64_t it, inc, limit, index, n, m;
	vector<Link*> cset;
	vector<uint64_t> fset;
	vector<uint64_t> mset;
	Network* network;
	
	void decode(uint64_t);
	void update_interference();	
	double calculate_interference(Node*, Node*);
	bool is_feasible();
	bool masks_test();
	bool primary_test();
	bool secondary_test();
	double calculate_sinr(Link*);				
	void clear_cset();
	void print_cset();
		
public:
	Algorithm2(Network*);
	void find_fset();
	vector<uint64_t> get_fset();
	void print_fset();
	void clear_fset();
};

