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
		unsigned int strategy_social, strategy_weight, strategy_halt;
		unsigned int iter, no_improve, swarm_size, neighbours;

		const unsigned int dim;
		double inert_weight, err_threshold, c1, c2;
		bool verbose, db_store;

		double (*objective_func) (std::vector< double >, void*);

		void init (unsigned int social, unsigned int str_weight, unsigned int halt, unsigned int it, unsigned int im, unsigned int size, double weight, double thresh, double c_1, double c_2, bool verb, bool store) {
			strategy_social = social;
			strategy_weight = str_weight;
			strategy_halt = halt;

			iter = it;
			no_improve = im;
			swarm_size = size;

			inert_weight = weight;
			err_threshold = thresh;
			c1 = c_1;
			c2 = c_2;

			verbose = verb;
			db_store = store;
		}

		int calc_swarm_size (int dim) {
			int result (10. + 2. * sqrt (dim));
			return (result < pso::SWARM_SIZE_MAX ? result : pso::SWARM_SIZE_MAX);
		}

		std::vector< std::vector< double > > init_swarm (void) const {
			/* logic for creating swarm with random values and returning */
		}

		std::vector< std::vector< double > > init_velocity (void) const {
			/* logic for creating velocity vectors */
		}

		void set_inert_weight (double& inert_weight) {
			switch (strategy_weight) {
				case (pso::STRATEGY_W_LIN_DEC):
					/* logic for inertia weight linear decrease */
					break;
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
		Swarm (int dimension, unsigned int social, unsigned int str_weight, unsigned int halt, unsigned int it, unsigned int im, unsigned int size, double weight, double thresh, double c_1, double c_2, bool verb, bool store) : dim (dimension) {
			init (social, str_weight, halt, it, im, calc_swarm_size (dim), weight, thresh, c1, c2, verb, store);
		}

		Swarm (int dimension) : dim (dimension) {
			init (pso::STRATEGY_GLOBAL, pso::STRATEGY_W_CONST, pso::STRATEGY_FITNESS_THRESHOLD, pso::DEFAULT_ITERATIONS, pso::DEFAULT_NO_IMPROVE_ITER, this->calc_swarm_size (dim), pso::DEFAULT_W, pso::DEFAULT_ERR_THRESHOLD, pso::C, pso::C, pso::VERBOSE_OFF, pso::DB_STORE_OFF);
		}

		void set_objective_func (double (*func_name) (std::vector< double >, void*)) {
			objective_func = func_name;
		}

		std::vector< double > find_food (void) {
			std::vector< std::vector< double > > swarm (init_swarm ()), velocities (init_velocity ()), pbests (swarm.begin (), swarm.end ());
			std::vector< double > pbest_errors (swarm_size, pso::MAX_ERR), gbest (dim, DBL_MAX);
			double gbest_err (pso::MAX_ERR);

			while (true) {
				for (int i = 0; i < swarm_size; i++) {
					err = objective_func (swarm [i], NULL);
					if (err < pbest_errors [i]) {
						pbests [i] = swarm [i];
						pbest_errors [i] = err;
					}
				}

				get_gbest (pbests, pbest_errors, gbest, gbest_err);

				for (int i = 0; i < swarm_size; i++) {
					for (int j = 0; j < dim; j++) {
						double r1 (static_cast< double > (rand () / (RAND_MAX))), r1 (static_cast< double > (rand () / (RAND_MAX)));
						velocities [i] [dim] = 
							(inert_weight * velocities [i] [dim]) + 
							(c1 * r1 * (pbests [i] [dim] - swarm [i] [dim]))+ 
							(c2 * r2 * (gbest [dim] - swarm [i] [dim]));
						swarm [i] [dim] += velocities [i] [dim];
					}
					set_inert_weight (inert_weight);
				}
			}

			
		}
};
