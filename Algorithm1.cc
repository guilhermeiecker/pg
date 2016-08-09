#include "Algorithm1.h"

Algorithm1::Algorithm1(Network* g): n(g->get_nodes().size()), m(g->get_links().size()), network(g)
{
	cout << "Initializing..." << endl;
	find_fsets();
	cout << "Feasible sets found." << endl;
}

vector<uint64_t> Algorithm1::get_fsets()
{
	return feasible_sets;
}

void Algorithm1::clr_currset()
{
	for (vector<Link*>::iterator i = current_set.begin(); i != current_set.end(); ++i)
	{
		(*i)->get_sender()->dec_degree(); 
		(*i)->get_recver()->dec_degree();
		(*i)->clr_interf();
	}
	current_set.clear();
}

void Algorithm1::print_currset()
{
	cout << "(";
	for (vector<Link*>::iterator i = current_set.begin(); i != current_set.end(); ++i)
		cout << " " << (*i)->get_id();
	cout << " )" << endl;
}

void Algorithm1::decode_int(uint64_t x)
{
	uint64_t q = x / 2;
	uint64_t r = x % 2;

	if(r==0)
	{
		if(q==0)
		{
			cout << endl << "ERROR: Impossible combination of q and r!" << endl;
			return;
		}
		else
		{
			index++;
			decode_int(q);
		}
	}
	else
	{
		current_set.push_back(network->get_link(index));	//add link to current set
		current_set.back()->get_sender()->inc_degree();		//update sender degree
		current_set.back()->get_recver()->inc_degree();		//update recver degree 
		if(q==0)
		{
			return;
		}
		else
		{
			index++;
			decode_int(q);
		}
	}
}

double Algorithm1::calculate_sinr(Link* l)
{
	double interference = 0.0;
    for (vector<double>::iterator i = l->get_interf().begin(); i != l->get_interf().end(); ++i) 
    {
    	interference = interference + *i;
    }
    return l->get_rpower() / (network->noise_dBm + interference);
}

bool Algorithm1::primary_test()
{
	cout << "Testing primary interference... ";
	for(vector<Link*>::iterator i = current_set.begin(); i != current_set.end(); ++i)
	{
		if (((*i)->get_sender()->get_degree() > 1) || ((*i)->get_recver()->get_degree() > 1))
		{
			cout << "Failed!" << endl;
			return false;
		}
	}
	cout << "OK!" << endl;
	return true;
}

bool Algorithm1::secondary_test()
{
	cout << "Testing secondary interference..." << endl;
	double sinr;
	for(vector<Link*>::iterator i = current_set.begin(); i != current_set.end(); ++i)
	{
		sinr = calculate_sinr(*i);
		cout << "SINR(" << (*i)->get_id() << "," << it << ")=" << sinr << endl;
		if(sinr < network->beta_dB)
			return false;
	}
	cout << "OK!" << endl;
	return true;
}

bool Algorithm1::is_feasible()
{
	if((primary_test())&&(secondary_test()))
		return true;
	else
		return false;
}

void Algorithm1::find_fsets()
{
	cout << "Finding feasible sets..." << endl;
	uint64_t inc;
	uint64_t limit = (uint64_t)pow(2, m);
	for(it = 1; it < limit; it++)
	{
		index = 0;
		cout << "Decoding integer " << it << endl;
		decode_int(it);
		update_interference();
		cout << "Checking feasibility..." << endl;
		if ((current_set.size() < 2)||(is_feasible()))
		{
			inc = 0;
			feasible_sets.push_back(it);
		}
		else
			inc = ((it&~(it-1)) - 1);
		it = it + inc;
		cout << "Clearing current set..." << endl << endl;
		clr_currset();
	}
}

void Algorithm1::print_fsets()
{
	cout << "Printing feasible sets of links..." << endl;
	for (vector<uint64_t>::iterator i = feasible_sets.begin(); i != feasible_sets.end(); ++i)
	{
		index = 0;
		decode_int(*i);
		print_currset();
		clr_currset();
	}
}

void Algorithm1::update_interference()
{
	if(current_set.size()<2)
		return;
	for (vector<Link*>::iterator i = current_set.begin(); i != current_set.end(); ++i)
	{
		for (vector<Link*>::iterator j = current_set.begin(); j != current_set.end(); ++j)
		{
			if(i!=j)
			{
				(*i)->add_interf(calculate_interference((*j)->get_sender(), (*i)->get_recver()));
				(*j)->add_interf(calculate_interference((*i)->get_sender(), (*j)->get_recver()));
			}
		}
	}
		
}

double Algorithm1::calculate_interference(Node* a, Node* b)
{
        double dist = a->distance(*b);
        if (dist > network->d0)
                return pow(10.0, network->tpower_dBm - network->l0_dB - 10 * network->alpha*log10(dist / network->d0) / 10.0);
        else
                return pow(10.0, network->tpower_dBm - network->l0_dB / 10.0);
}
