#include "Algorithm6.h"

void Algorithm6::find_fset(uint64_t x)
{
	it = x;
	uint64_t limit;
	if (x == 0)
	{
		limit = m;
		for (uint64_t i = 0; i < limit; i++)
			find_fset(x + (uint64_t)pow(2, i));
	}
	else
	{
		limit = (uint64_t)log2(x & ~(x - 1));
		add_link(limit);
		if (is_feasible()) 
		{
			fset.push_back(x);
			for (uint64_t i = 0; i < limit; i++)
				find_fset(x + (uint64_t)pow(2, i));
		}
		del_link(limit);
	}
}

void Algorithm6::add_link(uint64_t index)
{
	if (!cset.empty()) {
		double interfAB, interfBA;
		for (vector<Link*>::iterator i = cset.begin(); i != cset.end(); ++i) 
		{
			interfAB = calculate_interference((*i)->get_sender(), network->get_link(index)->get_recver());
			interfBA = calculate_interference(network->get_link(index)->get_sender(), (*i)->get_recver());
			network->get_link(index)->add_interf(interfAB);
			(*i)->add_interf(interfBA);
		}
	}
	network->get_link(index)->get_sender()->inc_degree();
	network->get_link(index)->get_recver()->inc_degree();     
	cset.push_back(network->get_link(index));
}

double Algorithm6::calculate_interference(Node* a, Node* b)
{
  double dist = a->distance(*b);
  if (dist > network->d0)
  	return pow(10.0, ((network->tpower_dBm - network->l0_dB - 10 * network->alpha*log10(dist / network->d0)) / 10.0));
  else
 		return pow(10.0, network->tpower_dBm - network->l0_dB / 10.0);
}

bool Algorithm6::is_feasible()
{
	if(cset.size() < 2)
		return true;
	if(cset.size() > n/2)
		return false;
	
	mtest_val = true;
	ptest_val = true;
	stest_val = true;
	stop = false;
	/*
	#pragma omp parallel num_threads(3)
	{
		int num = omp_get_thread_num();
		switch(num)
		{
			case 0:
				masks_test();
				break;
			case 1:
				primary_test();
				break;
			case 2:
				secondary_test();
				break;
		}
	}
	*/
	//#pragma omp parallel sections num_threads(3)	// checar se funciona em um pc mais potente
	#pragma omp sections nowait
	{
		#pragma omp section 
		{ 	
			masks_test();
		}
		#pragma omp section
		{
			primary_test();
		}
		#pragma omp section
		{
			secondary_test();
		}
	}

	if((mtest_val)&&(ptest_val)&&(stest_val))
		return true;
		
	return false;
}

void Algorithm6::masks_test()
{
	for(vector<uint64_t>::iterator i = mset.begin(); i != mset.end(); ++i)
	{
		if(stop)
			return;
		if((it & *i) == *i)
		{
			mtest_val = false;
			stop = true;
			return;
		}
	}
  mtest_val = true;	
	return;
}

void Algorithm6::primary_test()
{
	for (vector<Link*>::iterator i = cset.begin(); i != cset.end(); ++i)
	{
		if(stop)
			return;
		if(((*i)->get_sender()->get_degree() > 1)||((*i)->get_recver()->get_degree() > 1))
		{
			mset.push_back(it);				
			ptest_val = false;
			stop = true;
			return;
    }
	}
	ptest_val = true;
	return;
}

void Algorithm6::secondary_test()
{
	double sinr;
	for(vector<Link*>::iterator i = cset.begin(); i != cset.end(); ++i)
	{
		if(stop)
			return;
		sinr = calculate_sinr(*i);
		if(sinr < network->beta_mW)
		{
			mset.push_back(it);
			stest_val = false;
			stop = true;
			return;
		}	
	}
	stest_val = true;
	return;
}

double Algorithm6::calculate_sinr(Link* l)
{
  return l->get_rpower() / (network->noise_mW + l->clc_interf());
}

void Algorithm6::del_link(uint64_t index)
{
	cset.pop_back();
	network->get_link(index)->get_sender()->dec_degree();
	network->get_link(index)->get_recver()->dec_degree();
	network->get_link(index)->clr_interf();
	for (vector<Link*>::iterator i = cset.begin(); i != cset.end(); ++i)
		    (*i)->del_interf();
}

Algorithm6::Algorithm6(Network* g): n(g->get_nodes().size()), m(g->get_links().size()), network(g) {}

vector<uint64_t> Algorithm6::get_fset()
{
	return fset;
}

void Algorithm6::print_fset()
{
	cout << "Printing fset for Algorithm 6..." << endl;
	for (vector<uint64_t>::iterator i = fset.begin(); i != fset.end(); ++i)
		cout << *i << " ";
	cout << endl;
}

void Algorithm6::clear_fset() 
{ 
	fset.clear(); 
	mset.clear();
}
