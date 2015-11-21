#include <iostream>
#include <algorithm>
#include "obj_func.hpp"
#include "pso.hpp"
using namespace std;

void print (double& val) { cout << val << "\t\t"; }
int main () {
//	Swarm mySwarm (6, pso_sphere);
	Swarm mySwarm (6, pso_griewank);
//	Swarm mySwarm (6, pso_styb_tang);
//	Swarm mySwarm (6, pso_rastrigin);
//	Swarm mySwarm (6, pso_rosenbrock);
	

	vector< double > best;

	mySwarm.set_strategy_social (pso::STRATEGY_GLOBAL);
	mySwarm.set_strategy_halt (true, true, false);
	mySwarm.set_strategy_weight (pso::STRATEGY_W_LIN_DEC);

	mySwarm.set_storage (true);
	mySwarm.set_db_details ("root", "Ninja19f", "PSO");

	mySwarm.set_iterations (10000);
	mySwarm.set_err_thresh (1e-8);

	mySwarm.set_iw_bounds (0.3, 0.9);

	mySwarm.set_swarm_size (15);
	mySwarm.set_dim_bounds (-9e3, 9e3);

	best = mySwarm.find_food ();
	for_each (best.begin (), best.end (), print);
	cout << endl << "Minimum Point Reached: " << pso_griewank (best, NULL) << endl;
	cout << endl;
	return (0);
}
