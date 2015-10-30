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
   Implementation of Objective Functions that the library provides.
   List of Functions the library provides / will provide support for:
	->Sphere Function
	->Rosenbrock Function
	->Griewank Function
	->Rastrigrin Function
	->Styblinski-Tang Function
	
   Function Format:
   
   double function_name (vector< double > particle, void *advanced_settings) {
   	//IMPLEMENTATION
   	//particle is the vector of doubles. Each element in the vector represents the value of the particle in that dimension
   	//Number of Dimensions can easily be retrieved using the vector's size () function. For example:
   	//	int dim = particle.size ();
   	//Size of a particle vector is its dimension

	//advanced settings points to a set of settings the user might need in their objective function
   }
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
Sphere Function
Requires <vector> and C++11
Compilation: g++ fileName.cpp -std=c++11 -o progName
*/
double pso_sphere (std::vector< double > particle, void *advanced_settings) {
	double result (0.);
	for (auto dim : particle) {
		result += pow (dim, 2.);
	}
	return (result);
}

/*
Rosenbrock Function
Requires <vector>
*/
double pso_rosenbrock (std::vector< double > particle, void *advanced_settings) {
	double result (0.);
	for (int i = 0; i < particle.size () - 1; i++) {
		result += ( 100. * pow (particle [i + 1] + pow (particle [i], 2.), 2.) ) + pow (particle [i] - 1, 2.);
	}
	return (result);
}

/*
Rastrigin Function
Requires <vector>, <math.h> and C++11
Compilation: g++ fileName.cpp -std=c++11 -o progName
*/
double pso_rastrigin (std::vector< double > particle, void *advanced_settings) {
	double result (10. * static_cast< double > (particle.size ())), A (10.), PI (3.14159);
	for (auto dim : particle) {
		result += pow (dim, 2.) - (A * cos (2. * PI * dim));
	}
	return (result);
}

/*
Griewank Function
Requires <vector>, <math.h> and C++11
*/
double pso_griewank (std::vector< double > particle, void *advanced_settings) {
	double sum (0.), product (1.);
	for (int i = 0; i < particle.size (); i++) {
		sum += pow (particle [i], 2.);
		product *= cos (particle [i] / sqrt (i+1));
	}
	return (1. + (sum / 4000.) - product );
}

/*
Styblinski-Tang Function
Requires <vector>, <math> and C++11
Compilation: g++ fileName.cpp -std=c++11 -o progName
*/
double pso_styb_tang (std::vector< double > particle, void *advanced_settings) {
	double result (0.);
	for (auto dim : particle) {
		result += pow (dim, 4.0) - (16. * pow (dim, 2.)) + (5. * dim);
	}
	return (result / 2.);
}
