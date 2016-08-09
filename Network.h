#pragma once

#include <stdint.h>		// uint64_t
#include <iostream>		// cout
#include <vector>
#include <math.h>		// pow, log10

#include "Link.h"
#include "Node.h"

//int __builtin_popcount(unsigned int x);	//elegant way to get the number of links in the combination x - demands GCC (maybe it works on linux)

using namespace std;

class Network {
private:
	uint64_t num_nodes;
	double area_side;
	double tpower;

	vector<Node> nodes;		// array of nodes
	vector<Link> links;		// array of links
	
public:
	const double bandwidth = 20e06;																	// Bandwidth (MHz)
	const double noise_mW = 1380e-23 * 290 * bandwidth;												// Noise-floor (mW)
	const double noise_dBm = 10 * log10(noise_mW);												// Noise-floor (dBm)
	const double d0 = 1.0;																			// Reference distance of Log-distance propagation model (m)
	const double l0_dB = 0.0;																		// Loss at the reference distance (dB)   
	const double alpha = 4.0;																		// Path loss exponent of Log-distance propagation model (Default: 4.0)
	const double beta_dB = 25.0;																	// Minimum SINR needed to decode a transmission (dB) (Default: 25.0)
	const double beta_mW = pow(10, beta_dB / 10.0);														// Minimum SINR needed to decode a transmission (mW)
	const double tpower_dBm = 10 * log10(tpower);													// Transmission power (dBm)
	const double max_range = d0*pow(10, (tpower_dBm - noise_dBm - beta_dB - l0_dB) / (10 * alpha));	// Maximum communication range (m) (considering only noise-floor)
	
	Network(uint64_t _n = 100, double _a = 3000.0, double _p = 300.0) : num_nodes(_n), area_side(_a), tpower(_p)
	{
		cout << "Initializing network..." << endl;
		cout << "\tmaxRange=\t" << max_range << endl << 
				"\tnoiseFloor=\t" << noise_mW << endl <<
				"\tnoiseFloordBm=\t" << noise_dBm << endl <<
				"\tPtdBm=\t\t" << tpower_dBm << endl <<
				"\tbeta=\t\t" << beta_mW << endl << endl;
		set_nodes();
		set_links();
	}
	
	vector<Node> get_nodes();	// Nodes getter
	vector<Link> get_links();	// Links getter

	void set_nodes();			// Nodes setter
	void set_links();			// Links setter
	
	Link* get_link(uint64_t);
	void print_links();
};
