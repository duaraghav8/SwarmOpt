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
	
   Function Format:
   
   double function_name (vector< vector< double > > swarm, void *advanced_settings) {
   	/*IMPLEMENTATION
   	swarm is the vector of vector of doubles. Each Vector inside the Swarm represents an N-Dimensional particle
   	Number of Dimensions can easily be retrieved. For example:
   		int dim = swarm [0].length ();
   	Length of a particle vector is its dimension
   }
*/


/*
Sphere Function
Requires <vector> and C++11
Compilation: g++ fileName.cpp -std=c++11 -o progName
*/
double pso_sphere (vector< vector< double > > swarm, void *advanced_settings) {
	double result (0.);
	for (auto particle : swarm) {
		for (auto dim : particle) {
			result += pow (dim, 2);
		}
	}
	return (result);
}
