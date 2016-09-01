#include "Network.h"

vector<Node> Network::get_nodes()
{
	return nodes;
}

vector<Link> Network::get_links()
{
	return links;
}

void Network::set_nodes()
{
	//cout << "Initializing node vector..." << endl;
	for (uint64_t i = 0; i < num_nodes; i++)
	{
		nodes.push_back(Node(i, area_side));
		//cout << "Node id: " << nodes.back().get_id() << ",\t(" << nodes.back().get_x() << "," << nodes.back().get_y() << ")\tdegree=" << nodes.back().get_degree() << endl;
	}
	//cout << endl;
}

void Network::set_links()
{
	srand (time(NULL));
	uint64_t index = 0;
	//cout << "Initializing link vector..." << endl;
	for (vector<Node>::iterator i = nodes.begin(); i != nodes.end(); ++i) {
		for (vector<Node>::iterator j = i + 1; j != nodes.end(); ++j) {
			int coin = ((int) random())%2;
			double pr;
			double dist = i->distance(*j);
			if (dist <= max_range) {
				// choose a reception power for the edge
				if (dist > d0)
					pr = pow(10.0, ((tpower_dBm - l0_dB - 10*alpha*log10(dist / d0))/10.0));
				else 
					pr = pow(10.0, ((tpower_dBm - l0_dB) / 10.0));
				// choose a direction in the selected edge
				//if (coin == 0)
					links.push_back(Link(&(*i), &(*j), index++, dist, pr));
				//else
				//	links.push_back(Link(&(*j), &(*i), index++, dist, pr));
					
				//cout << "link " << links.back().get_id() << "(" << links.back().get_sender()->get_id() << "," << links.back().get_recver()->get_id() << ")\td=" << links.back().get_dist() << "\trpower=" << pr << " mW" << endl;
			}
		}
	}
	//cout << endl;
}

Link* Network::get_link(uint64_t idx)
{
	return &(links[idx]);
}

void Network::print_links()
{
	cout << "Printing links..." << endl;
	for (vector<Link>::iterator i = links.begin(); i != links.end(); ++i)
		cout << "Link id=" << i->get_id() << " sender(id=" << (*i).get_sender()->get_id() << ", deg=" << (*i).get_sender()->get_degree() << ") receiver(id=" << (*i).get_recver()->get_id() << ", deg=" << (*i).get_recver()->get_degree() << ")" << endl;
}
