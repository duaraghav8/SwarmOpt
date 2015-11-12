#include <iostream>
#include <algorithm>
#include "obj_func.hpp"
#include "pso.hpp"
using namespace std;

/*
	The Custom Objective Function is meant to evaluate a particle in the following manner: Given a Particle, take the sum of all values in it. Since the target sum is 120.0, return the absolute difference between 120 and the obtained sum. This difference is what must be minimized. The global minimum of this function exists at all positions whose difference with target (120) is 0.
*/

double custom_objective_func (vector< double > particle, void *params) {
	double target (120.), sum (0.);
	for (auto dim : particle) {
		sum += dim;
	}
	return (abs (sum - target));
}

void print (double& val) { cout << val << "\t\t"; }
int main () {
	Swarm mySwarm (6, custom_objective_func);
	

	vector< double > best;

	mySwarm.set_strategy_social (pso::STRATEGY_GLOBAL);
	mySwarm.set_strategy_halt (true, true, false);	//order: Error Threshold, Limit on Iterations, No Improvement over several iterations
	mySwarm.set_strategy_weight (pso::STRATEGY_W_LIN_DEC);

	mySwarm.set_iterations (5000);
	mySwarm.set_err_thresh (1e-10);

	mySwarm.set_iw_bounds (0.3, 0.9);

	mySwarm.set_swarm_size (15);
	mySwarm.set_dim_bounds (-900., 900.);

	best = mySwarm.find_food ();
	for_each (best.begin (), best.end (), print);
	cout << endl << "Minimum Point Reached: " << custom_objective_func (best, NULL) << endl;
	cout << endl;
	return (0);
}
