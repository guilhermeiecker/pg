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

class Algorithm5
{
private:
	bool mt_val, pt_val, st_val;
	clock_t mt_t1, mt_t2, pt_t1, pt_t2, st_t1, st_t2;
	double mt_total, pt_total, st_total;
	uint64_t it, index, n, m;
	vector<Link*> cset;
	vector<uint64_t> fset;
	vector<uint64_t> mset;
	Network* network;
	
	void add_link(uint64_t);
	double calculate_interference(Node*, Node*);
	bool is_feasible();
	void masks_test();
	void primary_test();
	void secondary_test();
	double calculate_sinr(Link*);
	void del_link(uint64_t);
	
public:
	Algorithm5(Network*);
	void find_fset(uint64_t);
	vector<uint64_t> get_fset();
	void print_fset();
	void clear_fset();
};
