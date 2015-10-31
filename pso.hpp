/*
   A Library for Particle Swarm Optimization

   Copyright 2015 Raghav Dua, Mridul Bhambri
   
   This program is free software: you can redistribute it and/or
   modify it under the terms of the GNU General Public License version
   3 as published by the Free Software Foundation.
   This program is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see
   <http://www.gnu.org/licenses/>.
 */

/*
   The implementation of PSO Class and related functions goes here
*/

#include "variables.hpp"

class Swarm {
	private:
		/* Variables for all the settings for PSO */
		unsigned int strategy_social, strategy_weight, strategy_halt;
		unsigned int iter, iter_max, no_improve, swarm_size, neighbours;

		const unsigned int dim;
		double inert_weight, err_threshold, c1, c2;
		bool verbose, db_store;

		/*Objective Function setting */
		double (*objective_func) (std::vector< double >, void*);

		int calc_swarm_size (int dim) {
			int result (10. + 2. * sqrt (dim));
			return (result < pso::SWARM_SIZE_MAX ? result : pso::SWARM_SIZE_MAX);
		}

		std::vector< std::vector< double > > init_swarm (void) const {
			/* logic for creating swarm with random values and returning */
			std::vector< std::vector< double > > x (2);
			return (x);
		}

		std::vector< std::vector< double > > init_velocity (void) const {
			/* logic for creating velocity vectors */
			std::vector< std::vector< double > > x (2);
			return (x);
		}

		void update_inert_weight (double& inert_weight) {
			if (strategy_weight == pso::STRATEGY_W_LIN_DEC) {
				/* logic for inertia weight linear decrease */
			}
		}

		void get_gbest (std::vector< std::vector< double > >& pbests, std::vector< double >& pbest_errors, std::vector< double >& gbest, double& gbest_err) {
			switch (strategy_social) {
				case (pso::STRATEGY_GLOBAL):
					/* logic for Global influnce */
					break;
				case (pso::STRATEGY_KNN):
					/* logic for knn influence*/
					break;
			}
		}

	public:
		/* The Class has only one constructor. Supplying the object with dimension and objective function is necessary, rest can be initialized to default values. Dimension supplied cannot be changed later, but the objective function can be. */
		Swarm (int dimension, double (*func_name) (std::vector< double >, void*)) : dim (dimension) {
			swarm_size = calc_swarm_size (dim);
			objective_func = func_name;

			strategy_social = pso::STRATEGY_GLOBAL;
			strategy_weight = pso::STRATEGY_W_CONST;
			strategy_halt = pso::STRATEGY_FITNESS_THRESHOLD;

			iter_max = pso::DEFAULT_ITERATIONS;
			no_improve = pso::DEFAULT_NO_IMPROVE_ITER;

			inert_weight = pso::DEFAULT_W;
			err_threshold = pso::DEFAULT_ERR_THRESHOLD;
			c1 = c2 = pso::C;

			verbose = pso::VERBOSE_OFF;
			db_store = pso::DB_STORE_OFF;
		}

		/* Setters with appropriate Exception Handling */
		void set_objective_func (double (*func_name) (std::vector< double >, void*)) { objective_func = func_name; }
		void set_strategy_social (unsigned int s) {
			strategy_social = s;
			if (s == pso::STRATEGY_KNN) {
				neighbours = static_cast< int > ( (35. / 100.) * (swarm_size) );
			}
		}
		void set_knn_neighbours (unsigned int n) {
			if (n <= swarm_size) { neighbours = n; }
		}
		void set_strategy_weight (int s) {
			strategy_weight = s;
		}
		void set_err_thresh (double t) { err_threshold = t; }
		void set_iter (unsigned int i) { iter_max = i; }
		void set_no_improve_count (unsigned int c) { no_improve = c; }
		void set_strategy_halt (unsigned int h) { strategy_halt = h; }
		void set_swarm_size (unsigned int s) {
			if (s <= pso::SWARM_SIZE_MAX) {
				swarm_size = s;
			}
		}
		void set_verbose (bool v) { verbose = v; }
		void set_storage (bool s) { db_store = s; }
		/* Setters END */

		/* PSO Algorithm */
		std::vector< double > find_food (void) {
			std::vector< std::vector< double > > swarm (init_swarm ()), velocities (init_velocity ()), pbests (swarm.begin (), swarm.end ());
			std::vector< double > pbest_errors (swarm_size, pso::MAX_ERR), gbest (dim, DBL_MAX);
			double gbest_err (pso::MAX_ERR);

			while (true) {
				for (int i = 0; i < swarm_size; i++) {
					double err = objective_func (swarm [i], NULL);
					if (err < pbest_errors [i]) {
						pbests [i] = swarm [i];
						pbest_errors [i] = err;
					}
				}

				get_gbest (pbests, pbest_errors, gbest, gbest_err);

				for (int i = 0; i < swarm_size; i++) {
					for (int j = 0; j < dim; j++) {
						double r1 (static_cast< double > (rand () / (RAND_MAX))), r2 (static_cast< double > (rand () / (RAND_MAX)));
						velocities [i] [dim] = 
							(inert_weight * velocities [i] [dim]) + 
							(c1 * r1 * (pbests [i] [dim] - swarm [i] [dim]))+ 
							(c2 * r2 * (gbest [dim] - swarm [i] [dim]));
						swarm [i] [dim] += velocities [i] [dim];
					}
					update_inert_weight (inert_weight);
				}
			}

			std::vector< double > x (2);
			return (x);
		}
		/* PSO Algorithm ENDS */
};
