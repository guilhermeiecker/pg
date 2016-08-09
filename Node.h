#pragma once

#include <stdint.h>		// uint64_t
#include <random>		// rand()

class Node
{
private:
	uint64_t id, degree;	
	double x, y;

public:
	Node(uint64_t, double);

	uint64_t get_id();
	uint64_t get_degree();
	double get_x();
	double get_y();


	void set_id(uint64_t);
	void set_degree(uint64_t);
	void set_x(double);
	void set_y(double);

	void inc_degree();
	void dec_degree();
	
	double distance(Node);			// Calculates euclidian distance from this node to the parameter node
	void random_position(double);	// Generates random position x,y for the node
};
