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

	
**Creating & Initializing a Swarm Object**

**Using Built-in Objective Functions**

**Using Custom Objective Functions**

**Functions**


**Compilation:**

If you are not using the DataBase Connectivity Feature, then:

	g++ file_name.cpp -std=c++11 -o program_name

If, however, you are using it, then:

	g++ file_name.cpp -std=c++11 -L/usr/lib/mysql -lmysqlclient -lz -o program_name
