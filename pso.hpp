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
#include "priority_queue.hpp"
#include "db_connection.hpp"

class Swarm {
	private:
		/* Variables for all the settings for PSO */
		unsigned int strategy_social, strategy_weight;
		unsigned int iter_max, no_improve, swarm_size, neighbours;
		const unsigned int dim;

		double inert_weight, err_threshold, c1, c2, x_hi, x_lo, w_hi, w_lo;
		bool verbose, db_store, halt_iter_l, halt_no_imp, halt_err_thresh;

		DBObject db_connection;

		/* Objective Function setting */
		double (*objective_func) (std::vector< double >, void*);

		/* Functions for internal use */
		double euclid_dist (const std::vector< double >& x, const std::vector< double >& y) {
			double result (0.);
			for (int i = 0; i < x.size (); i++) {
				result += pow (x [i] - y [i], 2.);
			}
			return (sqrt (result));
		}

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

		void update_gbest_global (std::vector< std::vector< double > >& pbests, std::vector< double >& pbest_errors, std::vector< double >& gbest, double& gbest_err) {
			gbest_err = pbest_errors [0];
			gbest = pbests [0];

			for (int i = 1; i < swarm_size; i++) {
				if (pbest_errors [i] < gbest_err) {
					gbest_err = pbest_errors [i];
					gbest = pbests [i];
				}
			}
		}

		void update_gbest_knn (const std::vector< std::vector< double > >& pbests, const std::vector< double >& pbest_err, std::vector< double >& gbest, double& gbest_err, const std::vector< double >& particle, unsigned int neighbours) {
			pso::priority_queue pq;
			gbest_err = pso::MAX_ERR;

			for (int i = 0; i < pbests.size (); i++) {
				pso::simple_tuple item (euclid_dist (particle, pbests [i]), i);
				pq.push (item);
			}

			while (neighbours--) {
				pso::simple_tuple buffer (pq.top ());
				pq.pop ();

				if (pbest_err [buffer.pos ()] < gbest_err) {
					gbest_err = pbest_err [buffer.pos ()];
					gbest = pbests [buffer.pos ()];
				}
			}
		}
		/* Functions for internal use END */

	public:
		/* The Class has only one constructor. Supplying the object with dimension and objective function is necessary, rest initialized to default values. Every parameter except for dimension can be changed through setters. */
		Swarm (int dimension, double (*func_name) (std::vector< double >, void*)) : dim (dimension) {
			swarm_size = calc_swarm_size (dim);
			objective_func = func_name;

			x_hi = std::numeric_limits< double >::max ();
			x_lo = std::numeric_limits< double >::min ();

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

		/* Setters with appropriate Exceptions */

		/* set the objective function (either an in-built or a custom) */
		void set_objective_func (double (*func_name) (std::vector< double >, void*)) { objective_func = func_name; }

		/* set social strategy, i.e., should the psychological factor be global or another topology */
		void set_strategy_social (unsigned int s) {
			if (s != pso::STRATEGY_GLOBAL && s != pso::STRATEGY_KNN) {
				throw (std::invalid_argument (pso::ex_strategy_social));
			}

			strategy_social = s;
			if (s == pso::STRATEGY_KNN) {
				neighbours = static_cast< int > ( pso::NEIGHBOUR_FRACTION * swarm_size );
			}
		}

		/* If social strategy is Nearest Neighbour, how many neighbours should be considered? */
		void set_knn_neighbours (int n) {
			if (n < 1) {
				throw (std::invalid_argument (pso::ex_knn_small));
			}
			if (n > swarm_size) {
				throw (std::invalid_argument (pso::ex_knn_large));
			}
			neighbours = n;
		}

		/* Should the Inertia Weight remain constant or decrease linearly? */
		void set_strategy_weight (int s) {
			if (s != pso::STRATEGY_W_LIN_DEC && s != pso::STRATEGY_W_CONST) {
				throw (std::invalid_argument (pso::ex_weight));
			}

			strategy_weight = s;
			if (s == pso::STRATEGY_W_LIN_DEC) {
				inert_weight = w_hi = pso::DEFAULT_W_HI;
				w_lo = pso::DEFAULT_W_LO;
			}
		}

		/* If Inertia Weight is to decrease linearly, then what are the lower and upper bounds (both inclusive)? */
		void set_iw_bounds (double lo, double hi) {
			if (lo > hi) {
				throw (std::invalid_argument (pso::ex_iw_lo_bigger));
			}
			w_hi = hi;
			w_lo = lo;
		}

		/* If Halt Strategy is true for error threshold, what is the value of this threshold? */
		void set_err_thresh (double t) {
			if (t < 0.) {
				throw (std::invalid_argument (pso::ex_err_thresh));
			}
			err_threshold = t;
		}

		/* If Halt Strategy is true for iteration limit, what is the limit? */
		void set_iterations (int i) {
			if (i < 0) {
				throw (std::invalid_argument (pso::ex_iter_max));
			}
			iter_max = i;
		}

		/* If Halt Strategy is true for No Improvement over some iterations, what is the count? */
		void set_no_improve_count (int c) {
			if (c < 1) {
				throw (std::invalid_argument (pso::ex_no_improve_count));
			}
			no_improve = c;
		}

		/* Set the Halt strategy Parameters (error threshold, iteration limit, no improvement) */
		void set_strategy_halt (bool err_th, bool it, bool no_impr) {
			halt_iter_l = it;
			halt_err_thresh = err_th;
			halt_no_imp = no_impr;
		}

		/* Set Swarm Size */
		void set_swarm_size (int s) {
			if (s < 1) {
				throw (std::invalid_argument (pso::ex_swarm_size_small));
			}
			if (s > pso::SWARM_SIZE_MAX) {
				throw (std::invalid_argument (pso::ex_swarm_size_large));
			}
			swarm_size = s;
		}

		/* Verbose on Standard Output? */
		void set_verbose (bool v) { verbose = v; }

		/* Database Storage? */
		void set_storage (bool s) { db_store = s; }

		/* If Database storge is ON, then ask user for details */
		void set_db_details (const std::string username, const std::string password, const std::string dbname) {
			db_connection.uname (username);
			db_connection.passwd (password);
			db_connection.dbname (dbname);
		}

		/* Cognitive & Social Coefficients? */
		void set_c1c2 (double a, double b) {
			c1 = a;
			c2 = b;
		}

		/* What are the boundary values for each dimension? */
		void set_dim_bounds (double lo, double hi) {
			x_lo = lo;
			x_hi = hi;
		}
		/* Setters END */

		/* PSO Algorithm */
		std::vector< double > find_food (void) {
			std::vector< std::vector< double > > swarm (init_swarm ()), velocities (init_velocity ()), pbests (swarm);
			std::vector< double > pbest_errors (swarm_size, pso::MAX_ERR), gbest (dim, std::numeric_limits< double >::max ());
			double gbest_err (pso::MAX_ERR);
			unsigned int limit (halt_iter_l ? iter_max : std::numeric_limits< int >::max ());

			for (int iter = 0; iter < limit; iter++) {
				for (int i = 0; i < swarm_size; i++) {
					double err = objective_func (swarm [i], NULL);
					if (err < pbest_errors [i]) {
						pbests [i] = swarm [i];
						pbest_errors [i] = err;
					}
				}

				if (strategy_social == pso::STRATEGY_GLOBAL) { update_gbest_global (pbests, pbest_errors, gbest, gbest_err); }

				for (int i = 0; i < swarm_size; i++) {
					if (strategy_social == pso::STRATEGY_KNN) { update_gbest_knn (pbests, pbest_errors, gbest, gbest_err, swarm [i], neighbours); }
					for (int j = 0; j < dim; j++) {
						/*
							Behold! The backbone of PSO
						*/
						velocities [i] [j] = 
							(inert_weight * velocities [i] [j]) + 
							(c1 * drand (0, 1) * (pbests [i] [j] - swarm [i] [j])) + 
							(c2 * drand (0, 1) * (gbest [j] - swarm [i] [j]));
						swarm [i] [j] += velocities [i] [j];

						if (swarm [i] [j] > x_hi) { swarm [i] [j] = x_hi; }
						else if (swarm [i] [j] < x_lo) { swarm [i] [j] = x_lo; }
					}
				}

				if (halt_err_thresh && (gbest_err < err_threshold)) { break; }
				/* logic for no improve condition */
				if (strategy_weight == pso::STRATEGY_W_LIN_DEC) {
					inert_weight = update_inert_weight (iter, iter_max, w_lo, w_hi);
				}
			}

			return (gbest);
		}
		/* PSO Algorithm ENDS */
};
