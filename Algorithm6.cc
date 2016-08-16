#include "Algorithm6.h"

// private member functions
void Algorithm6::find_fsets(uint64_t x)
{
	it = x;
	uint64_t limit;	// iteration limit; index of the link to be added
	if (x == 0)	// this is necessary because uint64_t holds positive integers only and it will return underflow when n-1, for n=0, is computed
	{
		limit = m;					// in the first case there are links.size() calls
		for (uint64_t i = 0; i < limit; i++)
			find_fsets(x + (uint64_t)pow(2, i));	// calls setFsets for all kids, if there's any
	}
	else
	{
		//cout << "Testing combination " << x << "... " << endl;
		limit = (uint64_t)log2(x & ~(x - 1));					// n&~(n-1) gives the closest power of 2 that is less than n - to get the index, use log2
		add_link(limit);
		if (is_feasible()) {							// if combination n is feasible
			fsets.push_back(x);						// if this iteration is called, then n is feasible and needs to be pushed into fsets
			for (uint64_t i = 0; i < limit; i++)
				find_fsets(x + (uint64_t)pow(2, i));	// calls setFsets for all kids, if there's any
		}
		del_link(limit);
	}
}

void Algorithm6::add_link(uint64_t index)
{
	////cout << "Adding link " << index << endl;
	if (!current_set.empty()) {
		double interfAB, interfBA;
		for (vector<Link*>::iterator i = current_set.begin(); i != current_set.end(); ++i) 
		{
			interfAB = calculate_interference((*i)->get_sender(), network->get_link(index)->get_recver());
			interfBA = calculate_interference(network->get_link(index)->get_sender(), (*i)->get_recver());
			
			////cout << "I(" << index << "," << (*i)->get_id() << ")=" << interfAB << "\t";
			////cout << "I(" << (*i)->get_id() << "," << index << ")=" << interfBA << endl;
			network->get_link(index)->add_interf(interfAB);
			(*i)->add_interf(interfBA);
		}
	}
	network->get_link(index)->get_sender()->inc_degree();       // increments sender degree
	network->get_link(index)->get_recver()->inc_degree();       // increments recver degree
	current_set.push_back(network->get_link(index));
	//print_interf();
}

double Algorithm6::calculate_interference(Node* a, Node* b)
{
    double dist = a->distance(*b);
    ////cout << "distance from d(" << a->get_id() << "," << b->get_id() << ")=" << dist << endl; 
    if (dist > network->d0)
            return pow(10.0, ((network->tpower_dBm - network->l0_dB - 10 * network->alpha*log10(dist / network->d0)) / 10.0));
    else
            return pow(10.0, network->tpower_dBm - network->l0_dB / 10.0);
}

void Algorithm6::print_interf()
{
	//cout << "Printing interference vector for set " << it << "..." << endl;
	for (vector<Link*>::iterator i = current_set.begin(); i != current_set.end(); ++i)
		(*i)->prt_interf();
	//cout << endl;
}

bool Algorithm6::is_feasible()
{
	if(current_set.size() < 2)
	{
		//cout << "Single link... OK!" << endl;
		return true;
	}
	
	#pragma omp sections
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

	masks_test_end = false;
	prima_test_end = false;
	secon_test_end = false;

	if((masks_test_val == false)||(prima_test_val == false)||(secon_test_val == false))
	{
		masks_test_val = true;
		prima_test_val = true;
		secon_test_val = true;
		return false;
	}
	else
	{
		masks_test_val = true;
		prima_test_val = true;
		secon_test_val = true;
		return true;
	}
}

void Algorithm6::masks_test()
{
	//cout << "Testing masks patterns...";
	for(vector<uint64_t>::iterator i = masks.begin(); i != masks.end(); ++i)
	{
		if((!prima_test_end)||(!secon_test_end))
		{
			if((it & *i) == *i)
			{
				//cout << "Failed! (Found " << *i << " in " << it << ")" << endl;
				masks_test_end = true;
				masks_test_val = false;
				return;
			}
		}
		else
		{
			//cout << "Interference test has finished first" << endl;
		    masks_test_end = true;
   			masks_test_val = true;
			return;
		}

	}
	//cout << "OK!" << endl;
    masks_test_end = true;
    masks_test_val = true;	
	return;
}

void Algorithm6::primary_test()
{
	//cout << "Testing primary interference...";
	if (current_set.size() > n / 2)
	{
		//cout << "Failed!" << endl;
		prima_test_val = false;
		prima_test_end = true;
		return;
	}
	for (vector<Link*>::iterator i = current_set.begin(); i != current_set.end(); ++i)
	{
		if((masks_test_end==true)&&(masks_test_val==false))
		{
			//cout << "Masks test has finished first" << endl;
			prima_test_val = true;
			prima_test_end = true;
			return;
		}
		else
		{
			if(((*i)->get_sender()->get_degree() > 1)||((*i)->get_recver()->get_degree() > 1))
			{
				//cout << "Failed!" << endl;
				prima_test_val = false;
				prima_test_end = true;
		        return;
		    }
		}
	}
	//cout << "OK!" << endl;
	prima_test_val = true;
	prima_test_end = true;
	return;
}

void Algorithm6::secondary_test()
{
	//cout << "Testing secondary interference...";
	double sinr;
	for(vector<Link*>::iterator i = current_set.begin(); i != current_set.end(); ++i)
	{
		if(((masks_test_end==true)&&(masks_test_val==false))||
		   ((prima_test_end==true)&&(prima_test_val==false)))
		{
			//cout << "Masks test has finished first" << endl;
			secon_test_val = true;
			secon_test_end = true;
			return;
		}
		else
		{
			sinr = calculate_sinr(*i);
			if(sinr < network->beta_mW)
			{
				//cout << "Failed!" << endl;
				secon_test_val = false;
				secon_test_end = true;
				return;
			}	
		}	
	}
	//cout << "OK!" << endl;
	secon_test_val = true;
	secon_test_end = true;
	return;
}

double Algorithm6::calculate_sinr(Link* l)
{
    return l->get_rpower() / (network->noise_mW + l->clc_interf());
}

void Algorithm6::del_link(uint64_t index)
{
	////cout << "Deleting link " << index << endl;
	current_set.pop_back();
	network->get_link(index)->get_sender()->dec_degree();       // increments sender degree
	network->get_link(index)->get_recver()->dec_degree();       // increments recver degree
	network->get_link(index)->clr_interf();
	for (vector<Link*>::iterator i = current_set.begin(); i != current_set.end(); ++i)
		    (*i)->del_interf();
}

// public member functions
Algorithm6::Algorithm6(Network* g): n(g->get_nodes().size()), m(g->get_links().size()), network(g)
{
	cout << "Initializing Algorithm 6..." << endl;
	find_fsets(0);
	cout << "Feasible sets found." << endl;
}

vector<uint64_t> Algorithm6::get_fsets()
{
	return fsets;
}

void Algorithm6::print_fsets()
{
	cout << "Printing fsets for Algorithm 6..." << endl;
	for (vector<uint64_t>::iterator i = fsets.begin(); i != fsets.end(); ++i)
		cout << *i << " ";
	cout << endl;
}

void Algorithm6::print_masks()
{
	cout << "Printing masks..." << endl;
	for (vector<uint64_t>::iterator i = masks.begin(); i != masks.end(); ++i)
		cout << *i << "\t";
	cout << endl;
}
