#pragma once

#include "Node.h"
#include "Link.h"
#include "Network.h"

class Algorithm2
{
private:
	bool mt_val, pt_val, st_val;
	clock_t mt_t1, mt_t2, pt_t1, pt_t2, st_t1, st_t2;
	double mt_total, pt_total, st_total;
	uint64_t it, inc, limit, index, n, m;
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
	Algorithm2(Network*);
	void find_fset();
	vector<uint64_t> get_fset();
	void print_fset();
	void clear_fset();
};

