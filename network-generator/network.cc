#include "Network.h"

using namespace std;

int main(int argc, char** argv)
{
  int n = (int)atoi(argv[1]);
  double s = (double)atof(argv[2]);

  Network* g = new Network(n, s, 300.0);

  cout << g->get_links().size();
}
