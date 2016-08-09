#pragma once

#include <stdint.h>
#include <vector>
#include "Node.h"
#include "Link.h"
#include "Network.h"

vector<Link*>    ccomb;	// current link combination
vector<uint64_t> fsets;	// array of feasible sets of links (every integer represents a specific set)

void Network::setFsets(uint64_t n)
{
	uint64_t limit;	// iteration limit; index of the link to be added
	
	if (n == 0)	// this is necessary because uint64_t holds positive integers only and it will return underflow when n-1, for n=0, is computed
	{
		limit = links.size();					// in the first case there are links.size() calls
		for (uint64_t i = 0; i < limit; i++)
			setFsets(n + (uint64_t)pow(2, i));	// calls setFsets for all kids, if there's any
	}
	else
	{
		//cout << "Testing combination " << n << "... ";
		limit = log2(n & ~(n - 1));					// n&~(n-1) gives the closest power of 2 that is less than n - to get the index, use log2
		addLink(limit);
		//cout << "link " << limit << " added" << endl;
		if (isFeasible()) {							// if combination n is feasible
			fsets.push_back(n);						// if this iteration is called, then n is feasible and needs to be pushed into fsets
			cout << n << endl;						// prints n
			for (uint64_t i = 0; i < limit; i++)
				setFsets(n + (uint64_t)pow(2, i));	// calls setFsets for all kids, if there's any
		}
		//cout << "link " << limit << " removed" << endl;
		delLink(limit);
	}
}

bool Network::isFeasible() 
{
	if (primaryTest() && secondaryTest())
		return true;
	return false;
}

bool Network::primaryTest()
{
	if (ccomb.size() < 2)
	{
		//cout << "passed primary test because has only one link and ";
		return true;
	}

	if (ccomb.size() > nodes.size() / 2)
	{
		//cout << "failed primary test because m'>n/2" << endl;
		return false;
	}

	
	for (vector<Link*>::iterator i = ccomb.begin(); i != ccomb.end(); ++i)
	{
		if(((*i)->get_sender()->get_degree() > 1)||((*i)->get_recver()->get_degree() > 1))
			return false;
	}

	/** Old test
	for (vector<Link*>::iterator i = ccomb.begin(); i != ccomb.end(); ++i) {
		for (vector<Link*>::iterator j = i + 1; j != ccomb.end(); ++j) {
			if (((*i)->get_sender()->get_id() == (*j)->get_sender()->get_id()) ||
				((*i)->get_sender()->get_id() == (*j)->get_recver()->get_id()) ||
				((*i)->get_recver()->get_id() == (*j)->get_sender()->get_id()) ||
				((*i)->get_recver()->get_id() == (*j)->get_recver()->get_id()))
			{
				//cout << "failed primary test because link " << (*i)->get_id() << " shares a node with " << (*j)->get_id() << endl;
				return false;
			}
		}
	}
	*/
	//cout << "passed primary test because no links shares a node with each other and ";
	return true;
}

double Network::sinr(Link* l)
{
	double interference = 0.0;
	for (vector<double>::iterator i = l->get_interf().begin(); i != l->get_interf().end(); ++i) {
		interference = interference + *i;
	}

	return l->get_rpower() / (noiseFloordBm + interference);
}

bool Network::secondaryTest()
{
	if (ccomb.size() < 2)
	{
		//cout << "passed secondary test because has only one link" << endl;
		return true;
	}
	for (vector<Link*>::iterator i = ccomb.begin(); i != ccomb.end(); ++i) {
		double s = sinr(*i);
		if (s < beta)
		{
			//cout << "failed secondary test because sinr=" << s << "<beta=" << beta << endl;
			return false;
		}
	}
	//cout << "passed secondary test because no link has sinr<beta" << endl;
	return true;
}

double Network::calculateInterference(Node a, Node b)
{
	double dist = a.distance(b);
	if (dist > d0)
		return pow(10.0, PtdBm - L0dB - 10 * alpha*log10(dist / d0) / 10.0);
	else
		return pow(10.0, PtdBm - L0dB / 10.0);
}

void Network::addLink(uint64_t index)
{
	if (!ccomb.empty()) {
		double interfAB, interfBA;
		for (vector<Link*>::iterator i = ccomb.begin(); i != ccomb.end(); ++i) {

			interfAB = calculateInterference(*((*i)->get_sender()), *(links[index].get_recver())); // interf from node (*i)->get_sender() to node links[index].get_recver()
			interfBA = calculateInterference(*(links[index].get_sender()), *((*i)->get_recver())); // interf from node links[index].get_sender() to node (*i)->get_recver()
			
			links[index].add_interf(interfAB);	// updates links[index] interference
			(*i)->add_interf(interfBA);			// updates *i interference
		}
	}
	links[index].get_sender()->inc_degree();	// increments sender degree
	links[index].get_recver()->inc_degree();	// increments recver degree
	ccomb.push_back(&links[index]);
}

void Network::delLink(uint64_t index)
{
	links[index].get_sender()->dec_degree();	// increments sender degree
	links[index].get_recver()->dec_degree();	// increments recver degree
	ccomb.pop_back();
	links[index].clr_interf();
	for (vector<Link*>::iterator i = ccomb.begin(); i != ccomb.end(); ++i)
		(*i)->del_interf();
}
