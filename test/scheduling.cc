#include <time.h>
#include "Network.h"
#include "Algorithm1.h"
#include "Algorithm2.h"
#include "Algorithm3.h"
#include "Algorithm4.h"
#include "Algorithm5.h"
#include "Algorithm6.h"

bool check_size(vector< vector<uint64_t> > f)
{
	for(vector< vector<uint64_t> >::iterator i = f.begin(); i != f.end(); ++i)
	{
		for(vector< vector<uint64_t> >::iterator j = i + 1; j != f.end(); ++j)
		{
			if ((*i).size() != (*j).size())
				return false;
		}
	}
	return true;
}

bool check_content(vector< vector<uint64_t> > f)
{
	for(vector< vector<uint64_t> >::iterator i = f.begin(); i != f.end(); ++i)
	{
		for(vector< vector<uint64_t> >::iterator j = i + 1; j != f.end(); ++j)
		{
			if ((*i) != (*j))
				return false;
		}
	}
	return true;
}

int main(int argc, char** argv) {
	Network n(atoi(argv[1]), strtod(argv[2], NULL), 300.0);
	
	Algorithm1 a1(&n);
	Algorithm2 a2(&n);
	Algorithm3 a3(&n);
	Algorithm4 a4(&n);
	Algorithm5 a5(&n);
	Algorithm6 a6(&n);

	cout << "finding sets" << endl;
	a1.find_fset();cout << "Algo1 OK" << endl;
	a2.find_fset();cout << "Algo2 OK" << endl;
	a3.find_fset();cout << "Algo3 OK" << endl;
	a4.find_fset(0);cout << "Algo4 OK" << endl;
	a5.find_fset(0);cout << "Algo5 OK" << endl;
	a6.find_fset(0);cout << "Algo6 OK" << endl;
	
	vector< vector<uint64_t> > fs;
	fs.push_back(a1.get_fset()); 
	fs.push_back(a2.get_fset()); 
	fs.push_back(a3.get_fset());
	fs.push_back(a4.get_fset()); 
	fs.push_back(a5.get_fset());
	fs.push_back(a6.get_fset());
	
	/*
	for(vector< vector<uint64_t> >::iterator i = fs.begin(); i != fs.end(); ++i)
		cout << (*i).size() << endl;
	*/
	
	cout << "testing size.. " << endl;
	if(check_size(fs))
		cout << "Size OK!" << endl;
	else
		cout << "Size not OK!" << endl;
	/*
	if(check_content(fs))
		cout << "Content OK!" << endl;
	else
		cout << "Content not OK!" << endl;
	*/
	return 0;
}
