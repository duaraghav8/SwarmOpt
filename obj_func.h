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
   Implementation of built-in Objective Functions that the library provides.
   List of Functions the library provides / will provide support for:
	->Sphere Function
	->Rosenbrock Function
	->Griewank Function
	->Rastrigrin Function
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
