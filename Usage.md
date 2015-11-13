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

*coming soon*

**Compilation:**

If you are not using the DataBase Connectivity Feature, then:

	g++ file_name.cpp -std=c++11 -o program_name

If, however, you are using it, then:

	g++ file_name.cpp -std=c++11 -L/usr/lib/mysql -lmysqlclient -lz -o program_name
