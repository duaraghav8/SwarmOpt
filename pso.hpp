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
		unsigned int iter, no_improve, swarm_size;

		const unsigned int dim;
		double inert_weight, err_threshold, c1, c2;
		bool verbose, db_store;

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

	public:
		Swarm (int dimension, unsigned int social, unsigned int str_weight, unsigned int halt, unsigned int it, unsigned int im, unsigned int size, double weight, double thresh, double c_1, double c_2, bool verb, bool store) : dim (dimension) {
			this->init (social, str_weight, halt, it, im, this->calc_swarm_size (dim), weight, thresh, c1, c2, verb, store);
		}

		Swarm (int dimension) : dim (dimension) {
			this->init (pso::STRATEGY_GLOBAL, pso::STRATEGY_W_CONST, pso::STRATEGY_FITNESS_THRESHOLD, pso::DEFAULT_ITERATIONS, pso::DEFAULT_NO_IMPROVE_ITER, this->calc_swarm_size (dim), pso::DEFAULT_W, pso::DEFAULT_ERR_THRESHOLD, pso::C, pso::C, pso::VERBOSE_OFF, pso::DB_STORE_OFF);
		}

		std::vector< double > find_food (void) {
			/*
				Logic for convergence
			*/
		}
};
