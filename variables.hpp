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

#ifndef INCLUDED
#define INCLUDED 1

#include <vector>
#include <cstdlib>
#include <ctime>
#include <cfloat>
#include <cmath>

#endif

/*
   Declaration & Description of Variables and structures used in the library
*/

namespace pso {
	/*
		Strategy constants for Social Factor Influence
	*/
	const unsigned int STRATEGY_GLOBAL (0);
	const unsigned int STRATEGY_KNN (1);

	/*
		Constants for Inertia Weight Configuration 
	*/
	const double DEFAULT_W (0.6359);
	const unsigned int STRATEGY_W_CONST (0);
	const unsigned int STRATEGY_W_LIN_DEC (1);

	/*
		Constants for determining Halting Conditions - Can be used in combination with each-other using bitwise OR '|' operator
		EXAMPLE: pso.halt_strategy = STRATEGY_FITNESS_THRESHOLD | STRATEGY_ITER_LIMIT;		
		//loop breaks if error is small enough or N iterations have passed
	*/
	const double MAX_ERR = DBL_MAX;
	const double DEFAULT_ERR_THRESHOLD (1e-03);
	const unsigned int DEFAULT_ITERATIONS (5000);
	const unsigned int DEFAULT_NO_IMPROVE_ITER (7);

	const unsigned int STRATEGY_FITNESS_THRESHOLD (1);
	const unsigned int STRATEGY_ITER_LIMIT (2);
	const unsigned int STRATEGY_NO_IMPROVE (3);

	/*
		Constants concerning the Swarm
	*/
	const unsigned int SWARM_SIZE_MAX (100);

	/*
		Cognitive & Social Constants
		C1 = C2 = C (defined below)
	*/
	const double C (1.496);

	/*
		Constants for Verbose Information
	*/
	const unsigned int VERBOSE_OFF (false);
	const unsigned int VERBOSE_ON (true);

	/*
		Constants for Database Storage
	*/
	const unsigned int DB_STORE_OFF (false);
	const unsigned int DB_STORE_ON (true);
};
