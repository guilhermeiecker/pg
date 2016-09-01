#include "Algorithm5.h"

void Algorithm5::find_fset(uint64_t x)
{
	it = x;
	uint64_t limit;
	if (x == 0)
	{
		limit = m;
		for (uint64_t i = 0; i < limit; i++)
			find_fset(x + (uint64_t)pow(2, i));
		
		cout << "MT=" << mt_total << "\t";
		cout << "PT=" << pt_total << "\t";
		cout << "ST=" << st_total << "\t";
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

void Algorithm5::add_link(uint64_t index)
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

double Algorithm5::calculate_interference(Node* a, Node* b)
{
    double dist = a->distance(*b);
    if (dist > network->d0)
            return pow(10.0, ((network->tpower_dBm - network->l0_dB - 10 * network->alpha*log10(dist / network->d0)) / 10.0));
    else
            return pow(10.0, network->tpower_dBm - network->l0_dB / 10.0);
}

bool Algorithm5::is_feasible()
{
	if(cset.size() < 2)
		return true;
	if(cset.size() > n/2)
		return false;

	mt_t1 = clock();
	masks_test();
	mt_t2 = clock();

	pt_t1 = clock();
	primary_test();
	pt_t2 = clock();
	
	st_t1 = clock();
	secondary_test();
	st_t2 = clock();

	mt_total = mt_total + (double)(mt_t2 - mt_t1)/CLOCKS_PER_SEC;
	pt_total = pt_total + (double)(pt_t2 - pt_t1)/CLOCKS_PER_SEC;
	st_total = st_total + (double)(st_t2 - st_t1)/CLOCKS_PER_SEC;

	if(mt_val&&pt_val&&st_val)
		return true;
	return false;
}

void Algorithm5::masks_test()
{
	for(vector<uint64_t>::iterator i = mset.begin(); i != mset.end(); ++i)
	{
		if((it & *i) == *i)
		{
			mt_val = false;
			return;
		}
	}
	mt_val = true;
}

void Algorithm5::primary_test()
{
	for (vector<Link*>::iterator i = cset.begin(); i != cset.end(); ++i)
	{
		if(((*i)->get_sender()->get_degree() > 1)||((*i)->get_recver()->get_degree() > 1))
		{
			mset.push_back(it);
			pt_val = false;
	    return;
		}
	}
	pt_val = true;
}

void Algorithm5::secondary_test()
{
	double sinr;
	for(vector<Link*>::iterator i = cset.begin(); i != cset.end(); ++i)
	{
		sinr = calculate_sinr(*i);
		if(sinr < network->beta_mW)
		{
			mset.push_back(it);
			st_val = false;
			return;
		}
	}
	st_val = true;
}

double Algorithm5::calculate_sinr(Link* l)
{
    return l->get_rpower() / (network->noise_mW + l->clc_interf());
}

void Algorithm5::del_link(uint64_t index)
{
	cset.pop_back();
	network->get_link(index)->get_sender()->dec_degree();
	network->get_link(index)->get_recver()->dec_degree();
	network->get_link(index)->clr_interf();
	for (vector<Link*>::iterator i = cset.begin(); i != cset.end(); ++i)
		    (*i)->del_interf();
}


Algorithm5::Algorithm5(Network* g): n(g->get_nodes().size()), m(g->get_links().size()), network(g) {}

vector<uint64_t> Algorithm5::get_fset()
{
	return fset;
}

void Algorithm5::print_fset()
{
	cout << "Printing fset for Algorithm 5..." << endl;
	for (vector<uint64_t>::iterator i = fset.begin(); i != fset.end(); ++i)
		cout << *i << " ";
	cout << endl;
}

void Algorithm5::clear_fset() 
{ 
	fset.clear(); 
	mset.clear();
}
