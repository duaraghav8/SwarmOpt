**Team:**

	Raghav Dua

	Mridhul Bhambri


**Mentors:**

	Dr. Rashmi Sharma

	Mr. Gunjan Chhabra


SwarmOpt is a C++ Based Particle Swarm Optimization Library for optimizing continuous single-objective functions. The library currently features 3 in-built objective functions (Sphere, Rosenbrock, Griewank). Though PSO can also be used for Discrete Optimization Problems, the current version of the library doesn't support it.


**Features:**


1. Scope of Social Influence:

	->Global Best - The best social factor depends upon the entire swarm.

	->Local Best - The best social factor depends upon K Nearest Neighbours of the particle (K (int) supplied by the user). The nearest Neighbours are selected using the Euclidean Distance Heuristic.


2. Inertia Weight:

	->Constant - Remains constant W throughout the process (W (double) supplied by the user) (default 0.6359)

	->Linearly Decreasing - Starts with an Inertia Weight of W1 and decreases toward W2 (W1 (double) & W2 (double) supplied by the user, W1 > W2)


3. Halting Conditions:

	(Can be used individually as well as in combination with each-other)

	->DEFAULT: Fitness Error < Specified Error (The user specifies an error (double) and when the fittest particle demonstrates an error smaller than that, process stops).

	->Limit on Iterations: The Process stops after I iterations (I (int) supplied by the user)

	->No Significant Change: Process stops if no significant change is observed over S number of Iterations (S (int) supplied by the user)


4. Swarm Size:

	A Maximum of 100 particles can be used (however, a size of 20 to 30 is recommend for most problems). The default swarm size is (12 * sqrt (dim), sqrt means Square Root, dim is the number of dimensions in each particle) particles.

	Custom Swarm Size: Swarm Size is set to S (S (int) supplied by the user. S <= 100)


5. Cognitive & Social Coefficients:

	The coefficients C1 & C2: default value C1 = C2 = 1.496

	Custom: C1 & C2 can be set to A & B (A (double), B (double) supplied by user)


6. Verbose Information:

	Return the state of the swarm after each iteration (for each iteration, a vector of vectors of double is produced). This is the 'snapshot' of the swarm after that iteration

	default value: 0 (means verbose information output is OFF)

	supply the function with any int other than 0 - Verbose ON

	Prints Verbose Information to Standard Output.


7. Output format:

	->Optimal Solution - A Value for each Dimension

	->Error for the acquired value

	->Number of Iterations used to achieve the solution

	->Time taken

	->The choice of Parameters


8. Output Storage:

	The Library provides Database connectivity with MySql to store the problem configuration, parameters, progress under each iteration, solution retrieved and time taken.


9. Objective Functions:

	The Library Currently Supports 3 Objective Functions (more will be added):

		->Sphere Function

		->Rosenbrock

		->Griewank

	Apart from these, the user may supply an objective function of their own, which will be minimized.
