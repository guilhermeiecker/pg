#include "Algorithm3.h"

// private member functions

void Algorithm3::find_fset()
{
	for(it = 1; it <= limit; it++)
	{
		index = 0;
		decode(it);
		if (is_feasible())
		{
			inc = 0;
			fset.push_back(it);
		}
		else 
			inc = ((it&~(it-1)) - 1);
		if(it + inc < it) 
			return;
		it = it + inc;
		clear_cset();
	}
}

void Algorithm3::decode(uint64_t x)
{
	uint64_t q = x / 2;
	uint64_t r = x % 2;

	if(r==0)
	{
		if(q==0)
		{
			//cout << endl << "ERROR: Impossible combination of q and r!" << endl;
			return;
		}
		else
		{
			index++;
			decode(q);
		}
	}
	else
	{
		cset.push_back(network->get_link(index));	//add link to current set
		cset.back()->get_sender()->inc_degree();		//update sender degree
		cset.back()->get_recver()->inc_degree();		//update recver degree 
		if(q==0)
		{
			return;
		}
		else
		{
			index++;
			decode(q);
		}
	}
}

void Algorithm3::update_interference()
{
	for (vector<Link*>::iterator i = cset.begin(); i != cset.end(); ++i)
	{
		for (vector<Link*>::iterator j = cset.begin(); j != cset.end(); ++j)
		{
			if(i!=j)
				(*i)->add_interf(calculate_interference((*j)->get_sender(), (*i)->get_recver()));
		}
	}
		
}

double Algorithm3::calculate_interference(Node* a, Node* b)
{
    double dist = a->distance(*b);
    if (dist > network->d0)
            return pow(10.0, ((network->tpower_dBm - network->l0_dB - 10 * network->alpha*log10(dist / network->d0)) / 10.0));
    else
            return pow(10.0, network->tpower_dBm - network->l0_dB / 10.0);
}

bool Algorithm3::is_feasible()
{
	if(cset.size() < 2)
		return true;
	if(cset.size() > n/2)
		return false;
	update_interference();
	
	mtest_val = true;
	ptest_val = true;
	stest_val = true;
	stop = false;
	
	#pragma omp parallel num_threads(2)
	{
		int num = omp_get_thread_num();
		switch(num)
		{
			case 0:
				masks_test();
				break;
			case 1:
				primary_test();
				secondary_test();
				break;
		}
	}
	/*
	#pragma omp parallel sections num_threads(2)	// checar se funciona em um pc mais potente
	//#pragma omp sections nowait
	{
		#pragma omp section 
		{ 	
			masks_test();
		}
		#pragma omp section
		{
			primary_test();
			secondary_test();
		}
	}
*/
	if((!mtest_val)||(!ptest_val)||(!stest_val))
		return false;
	else
		return true;
}

void Algorithm3::masks_test()
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

void Algorithm3::primary_test()
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

void Algorithm3::secondary_test()
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

double Algorithm3::calculate_sinr(Link* l)
{
    return l->get_rpower() / (network->noise_mW + l->clc_interf());
}

void Algorithm3::clear_cset()
{
	for (vector<Link*>::iterator i = cset.begin(); i != cset.end(); ++i)
	{
		(*i)->get_sender()->dec_degree(); 
		(*i)->get_recver()->dec_degree();
		(*i)->clr_interf();
	}
	cset.clear();
}

void Algorithm3::print_cset()
{
	cout << "(";
	for (vector<Link*>::iterator i = cset.begin(); i != cset.end(); ++i)
		cout << " " << (*i)->get_id();
	cout << " )" << endl;
}


Algorithm3::Algorithm3(Network* g): n(g->get_nodes().size()), m(g->get_links().size()), network(g)
{
	limit = (m < 64) ? ((uint64_t)pow(2,m) - 1) : (numeric_limits<uint64_t>::max());
}

vector<uint64_t> Algorithm3::get_fset()
{
	return fset;
}

void Algorithm3::print_fset()
{
	cout << "Printing fset for Algorithm 3..." << endl;
	for (vector<uint64_t>::iterator i = fset.begin(); i != fset.end(); ++i)
		cout << *i << " ";
	cout << endl;
}

void Algorithm3::clear_fset() 
{ 
	fset.clear(); mset.clear();
}
