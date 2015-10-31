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
		unsigned int strategy_social, strategy_weight;
		unsigned int iter_max, no_improve, swarm_size, neighbours;

		const unsigned int dim;
		double inert_weight, err_threshold, c1, c2, x_hi, x_lo, w_hi, w_lo;
		bool verbose, db_store, halt_iter_l, halt_no_imp, halt_err_thresh;

		/* Objective Function setting */
		double (*objective_func) (std::vector< double >, void*);

		/* Functions for internal use */
		double drand (double lo, double hi) const {
			double result = static_cast< double > (rand ()) / RAND_MAX;
			return (lo + (result * (hi - lo)));
		}

		int calc_swarm_size (int dim) const {
			int result (10. + 2. * sqrt (dim));
			return (result < pso::SWARM_SIZE_MAX ? result : pso::SWARM_SIZE_MAX);
		}

		std::vector< std::vector< double > > init_swarm (void) const {
			std::vector< std::vector< double > > s (swarm_size);

			for (int i = 0; i < swarm_size; i++) {
				std::vector< double > particle (dim);
				for (int j = 0; j < dim; j++) {
					particle [j] = drand (x_lo, x_hi);
				}
				s [i] = particle;
			}
			return (s);
		}

		std::vector< std::vector< double > > init_velocity (void) const {
			std::vector< std::vector< double > > v (swarm_size);
			for (int i = 0; i < swarm_size; i++) {
				std::vector< double > particle (dim, 0.);
				v [i] = particle;
			}
			return (v);
		}

		double update_inert_weight (const unsigned int& iter, const unsigned int& iter_max, const double& w_lo, const double& w_hi) {
			int dec (3 * (iter_max / 4));
			if (iter <= dec) {
				return ( w_lo + ( (w_hi - w_lo) * ( static_cast< double >(dec - iter) / dec)) );
			}
			return (w_lo);
		}

		void update_gbest (std::vector< std::vector< double > >& pbests, std::vector< double >& pbest_errors, std::vector< double >& gbest, double& gbest_err) {
			switch (strategy_social) {
				case (pso::STRATEGY_GLOBAL):
					/* logic for Global influnce */
					break;
				case (pso::STRATEGY_KNN):
					/* logic for knn influence*/
					break;
			}
		}
		/* Functions for internal use END */

	public:
		/* The Class has only one constructor. Supplying the object with dimension and objective function is necessary, rest can be initialized to default values. Dimension supplied cannot be changed later, but the objective function can be. */
		Swarm (int dimension, double (*func_name) (std::vector< double >, void*)) : dim (dimension) {
			swarm_size = calc_swarm_size (dim);
			objective_func = func_name;

			x_hi = DBL_MAX;
			x_lo = DBL_MIN;

			strategy_social = pso::STRATEGY_GLOBAL;
			strategy_weight = pso::STRATEGY_W_CONST;

			iter_max = pso::DEFAULT_ITERATIONS;
			no_improve = pso::DEFAULT_NO_IMPROVE_ITER;

			inert_weight = pso::DEFAULT_W;
			err_threshold = pso::DEFAULT_ERR_THRESHOLD;
			c1 = c2 = pso::C;

			verbose = pso::VERBOSE_OFF;
			db_store = pso::DB_STORE_OFF;
			halt_iter_l = true;
			halt_err_thresh = true;
			halt_no_imp = false;

			srand (static_cast< unsigned int > (time (NULL)));
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
			if (s == pso::STRATEGY_W_LIN_DEC) {
				inert_weight = w_hi = 0.9;
				w_lo = 0.4;
			}
		}
		void set_iw_bounds (double lo, double hi) {
			w_hi = hi;
			w_lo = lo;
		}
		void set_err_thresh (double t) { err_threshold = t; }
		void set_iter (unsigned int i) { iter_max = i; }
		void set_no_improve_count (unsigned int c) { no_improve = c; }

		void set_strategy_halt (bool err_th, bool it, bool no_impr) {
			halt_iter_l = err_th;
			halt_err_thresh = it;
			halt_no_imp = no_impr;
		}

		void set_swarm_size (unsigned int s) {
			if (s <= pso::SWARM_SIZE_MAX) {
				swarm_size = s;
			}
		}
		void set_verbose (bool v) { verbose = v; }
		void set_storage (bool s) { db_store = s; }
		void set_c1c2 (double a, double b) {
			c1 = a;
			c2 = b;
		}
		void set_dim_bounds (double lo, double hi) {
			x_lo = lo;
			x_hi = hi;
		}
		/* Setters END */

		/* PSO Algorithm */
		std::vector< double > find_food (void) {
			std::vector< std::vector< double > > swarm (init_swarm ()), velocities (init_velocity ()), pbests (swarm.begin (), swarm.end ());
			std::vector< double > pbest_errors (swarm_size, pso::MAX_ERR), gbest (dim, DBL_MAX);
			double gbest_err (pso::MAX_ERR);
			unsigned int limit (halt_iter_l == true ? iter_max : INT_MAX);

			for (int iter = 0; iter < limit; iter++) {
				for (int i = 0; i < swarm_size; i++) {
					double err = objective_func (swarm [i], NULL);
					if (err < pbest_errors [i]) {
						pbests [i] = swarm [i];
						pbest_errors [i] = err;
					}
				}

				update_gbest (pbests, pbest_errors, gbest, gbest_err);
				for (int i = 0; i < swarm_size; i++) {
					for (int j = 0; j < dim; j++) {
						velocities [i] [dim] = 
							(inert_weight * velocities [i] [dim]) + 
							(c1 * drand (0, 1) * (pbests [i] [dim] - swarm [i] [dim]))+ 
							(c2 * drand (0, 1) * (gbest [dim] - swarm [i] [dim]));
						swarm [i] [dim] += velocities [i] [dim];
					}
				}

				if (halt_err_thresh && gbest_err < err_threshold) { break; }
				if (strategy_weight == pso::STRATEGY_W_LIN_DEC) {
					inert_weight = update_inert_weight (iter, iter_max, w_lo, w_hi);
				}
			}

			return (gbest);
		}
		/* PSO Algorithm ENDS */
};
