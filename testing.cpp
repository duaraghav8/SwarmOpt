#include <iostream>
#include <algorithm>
#include "obj_func.hpp"
#include "pso.hpp"
using namespace std;

void print (double& val) { cout << val << '\t'; }
int main () {
	Swarm mySwarm (5, pso_sphere);
	vector< double > best;

	mySwarm.set_strategy_social (pso::STRATEGY_GLOBAL);
	mySwarm.set_strategy_halt (true, true, false);
	mySwarm.set_strategy_weight (pso::STRATEGY_W_LIN_DEC);

	mySwarm.set_iterations (3000);
	mySwarm.set_err_thresh (1e-2);

	mySwarm.set_iw_bounds (0.4, 0.9);

	mySwarm.set_swarm_size (15);
	mySwarm.set_dim_bounds (-500., 500.);

//	best = mySwarm.find_food ();
//	for_each (best.begin (), best.end (), print);
//	cout << endl;
	return (0);
}
