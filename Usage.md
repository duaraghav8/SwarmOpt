**Prerequisites**

In order to use the library, save all the files of this repository inside a directory. Let's call this directory 'pso'.

Now write the following code in a file and save the file in the directory which also contains your pso directory.

```c++
	#include <iostream>
	#include "pso/pso.hpp"
	using namespace std;

	int main () {
		cout << "It works!" << endl;
		return (0);
	}
```

Compile the file (see compilation (without database connectivity) below). If it runs, we're good to go!

	
**Creating & Initializing a Swarm Object**
To create a Swarm object:

```c++
	#include <iostream>
	#include "pso/pso.hpp"

	using namespace std;
	int main () {
		Swarm mySwarm (6, measure_fitness);
		/* measure_fitness () is your custom objective function */
		return (0);
	}
```

The only Constructor available for Swarm Object Construction takes 2 arguments: Number of Dimensions in each particle and the Objective Function. the objective function can be changed later as well, but the dimension count can never be changed once the object has been initialized with it.

**Using Built-in Objective Functions**

```c++
	#include <iostream>
	#include "pso/pso.hpp"
	#include "pso/obj_func.hpp"

	using namespace std;
	int main () {
		Swarm mySwarm (6, pso_sphere);
		/* pso_sphere () is a built-in objective function (The Sphere Function) */

		Swarm mySwarm2 (6, pso_rosenbrock);
		/* pso_rosenbrock () is a built-in objective function (The Rosenbrock Function) */

		return (0);
	}
```

**Creating & Using Custom Objective Functions**

Your custom Objective Function, which is to be *minimized* must follow the following format:

```c++
	double custom_objective_func (vector< double > particle, void *params) {
		/* logic of the function */
	return (result);
}
```

**Functions**

1. Name- Swarm(int dimension, double (*func_name) (std::vector< double >, void*)) : dim (dimension)

   Return type- None( A Constructor)

   Purpose- The only constructor of the Class Swarm, used to set up the scenario, where we use the PSO, or in  simple words to set up a swarm of particles.

   Parameters- Two parameters, dimension of type integer, tells us the number of dimensions in our dimensional space and helps us in finding the maximum population of a swarm, and func_name, that tells us the name of the objective function we are going to use PSO on, to optimize.

List of Functions the library provides provide support for:

	-Sphere Function

	-Rosenbrock Function

	-Griewank Function

	-Rastrigrin Function

	-Styblinski-Tang Function


2. Name- set_objective_func(double (*func_name) (std::vector< double >, void*))

   Return type- void

   Purpose- A function, which can be used to set up the objective function, either an in-built or a custom. You have done it in the constructor as well, but what if you need to change the function.

   Parameters- Just the name of the function, you want to optimize.


3*. Name- set_strategy_social(unsigned int s)

   Return type- void

   Purpose- To set the social horizon of the PSO, i.e. whether the particles of the swarm are being affected by the whole population or just some neighbouring ones'.

   Parameters- An unsigned Integer.


4. Name- set_knn_neighbours(int n)

   Return type- void

   Purpose- If the Social strategy is chosen to be some neighbours only, then to set the number of those neighbours.

   Parameters- The number of particles, you want to consider as neighbours.( Has to be a positive number, less than the Swarm size)


5*. Name- set_strategy_weight(int s)

   Return type- void

   Purpose-  To decide if the Inertia weight constraint used in the PSO, is a constant or a varying factor.

   Parameters- An integer to decide 


6. Name- set_iw_bounds(double lo, double hi)

   Return type- void

   Purpose- If the Inertia weight is a varying quantity, then what are its bounds, or from what it has to decrease to what.

   Parameters- Two double variables, one for the lower bound and other for the upper one.


7. Name- set_err_thresh(double t)

   Return type- void

   Purpose- The process may halt inbetween, if an undesired error comes as the result. So to set that threshold beyond which if the error appears, the process is to be halt, we use this function.

   Parameters- A double type variable representing the threshold of error that the strategy can consider, beyond which the process will halt automatically.


8. Name- set_iterations(int i)

   Return type- void

   Purpose- The optimization will take place, untill zero error is achieved, but that might not happen for sure. So that is why, we have this function, to define the number of iterations, after which the process will halt automatically.

   Parameters- An integer number, which will be equal to the number of iterations you need your function to perform.


9. Name- set_no_improve_count(int c)

   Return type- void

   Purpose- If the output the iterations appears to be same for more than a few iterations, the process may be put to a halt. And the count of those few iterations, that can be set by this function.

   Parameters- Just the number of iterations, for the no improvement condition.


10. Name- set_strategy_halt(bool err_th, bool it, bool no_impr)

    Return type- void

    Purpose- The process may halt inbetween, even if we dont have the exact error of 0. And this function helps us to set those conditions, that which of the three halting conditions known to us, should be valid or not.

    Parameters- The three boolean variables, each one for error threshold, number of iterations to be performed and the no improvement count.


11. Name- set_swarm_size(int s)

   Return type- void

   Purpose- To set the population of the swarm, you are going to use.

   Parameters- An integer, whic must be less than the maximum limit of the dimensional space.


12. Name- set_verbose(bool v)

   Return type- void

   Purpose- To set, if there is a requirement of the verbose functionality or not.

   Parameters- Just a boolean variable, deciding if the verbose functionality will be ON or OFF.


13. Name- set_storage(bool s)

   Return type- void

   Purpose- To avail the functionality of databse storage.

   Parameters- A boolean parameter for database support.


14. Name- set_db_details(const std::string username, const std::string password, const std::string dbname)

   Return type- void

   Purpose- To collect the information needed to access the database.

   Parameters- Three parameters, asking the username and password of the database you want your data to be put in. And third, the name of the database, you want this database to go in.


15. Name- set_c1c2(double a, double b)

   Return type- void

   Purpose- To set the Cognitive and Social coefficients.

   Parameters- Two double variables for the above said coefficients.


16. Name- set_dim_bounds(double lo, double hi)

   Return type- void

   Purpose- To set the bounds of each dimension. 

   Parameters- Two parametes, the least and the highest value of the dimenson.


**Compilation:**

If you are not using the DataBase Connectivity Feature, then:

	g++ file_name.cpp -std=c++11 -o program_name

If, however, you are using it, then:

	g++ file_name.cpp -std=c++11 -L/usr/lib/mysql -lmysqlclient -lz -o program_name
