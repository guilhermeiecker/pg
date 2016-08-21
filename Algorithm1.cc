#include "Algorithm1.h"

void Algorithm1::find_fset()
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

void Algorithm1::decode(uint64_t x)
{
	uint64_t q = x / 2;
	uint64_t r = x % 2;

	if(r==0)
	{
		if(q==0)
			return;
		else
		{
			index++;
			decode(q);
		}
	}
	else
	{
		cset.push_back(network->get_link(index));
		cset.back()->get_sender()->inc_degree();
		cset.back()->get_recver()->inc_degree(); 
		if(q==0)
			return;
		else
		{
			index++;
			decode(q);
		}
	}
}

void Algorithm1::update_interference()
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

double Algorithm1::calculate_interference(Node* a, Node* b)
{
    double dist = a->distance(*b);
    if (dist > network->d0)
            return pow(10.0, ((network->tpower_dBm - network->l0_dB - 10 * network->alpha*log10(dist / network->d0)) / 10.0));
    else
            return pow(10.0, network->tpower_dBm - network->l0_dB / 10.0);
}

bool Algorithm1::is_feasible()
{
	if(cset.size() < 2)
		return true;
	if(cset.size() > n/2)
		return false;
	update_interference();
	if(!primary_test()||!secondary_test())
		return false;
	return true;
}

bool Algorithm1::primary_test()
{
	for (vector<Link*>::iterator i = cset.begin(); i != cset.end(); ++i)
	{
		if(((*i)->get_sender()->get_degree() > 1)||((*i)->get_recver()->get_degree() > 1))
	        return false;
	}
	return true;
}

bool Algorithm1::secondary_test()
{
	double sinr;
	for(vector<Link*>::iterator i = cset.begin(); i != cset.end(); ++i)
	{
		sinr = calculate_sinr(*i);
		if(sinr < network->beta_mW)
			return false;
	}
	return true;
}

double Algorithm1::calculate_sinr(Link* l)
{
    return l->get_rpower() / (network->noise_mW + l->clc_interf());
}

void Algorithm1::clear_cset()
{
	for (vector<Link*>::iterator i = cset.begin(); i != cset.end(); ++i)
	{
		(*i)->get_sender()->dec_degree(); 
		(*i)->get_recver()->dec_degree();
		(*i)->clr_interf();
	}
	cset.clear();
}

void Algorithm1::print_cset()
{
	cout << "(";
	for (vector<Link*>::iterator i = cset.begin(); i != cset.end(); ++i)
		cout << " " << (*i)->get_id();
	cout << " )" << endl;
}

Algorithm1::Algorithm1(Network* g): n(g->get_nodes().size()), m(g->get_links().size()), network(g)
{
	limit = (m < 64) ? ((uint64_t)pow(2,m) - 1) : (numeric_limits<uint64_t>::max());
}

vector<uint64_t> Algorithm1::get_fset()
{
	return fset;
}

void Algorithm1::print_fset()
{
	cout << "Printing fset for Algorithm 1..." << endl;
	for (vector<uint64_t>::iterator i = fset.begin(); i != fset.end(); ++i)
		cout << *i << " ";
	cout << endl;
}

void Algorithm1::clear_fset() 
{ 
	fset.clear(); 
}
