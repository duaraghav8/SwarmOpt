#include <iostream>
#include <algorithm>
#include "obj_func.hpp"
#include "pso_best.hpp"
using namespace std;

void print (double& val) { cout << val << "\t\t"; }
int main () {
	Swarm mySwarm (5, pso_sphere);
	vector< double > best;

	mySwarm.set_strategy_social (pso::STRATEGY_GLOBAL);
	mySwarm.set_strategy_halt (true, true, false);
	mySwarm.set_strategy_weight (pso::STRATEGY_W_LIN_DEC);

	mySwarm.set_iterations (500);
	mySwarm.set_err_thresh (1e-4);

	mySwarm.set_iw_bounds (0.3, 0.9);

	mySwarm.set_swarm_size (15);
	mySwarm.set_dim_bounds (0., 50.);

	best = mySwarm.find_food ();
	for_each (best.begin (), best.end (), print);
	
	cout << endl << "Error: " << pso_sphere (best, NULL) << endl;
	cout << endl;
	return (0);
}
