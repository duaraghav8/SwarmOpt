#include "includes.hpp"

namespace pso {
	void print_particle (const std::vector< double >& p) {
		for (auto value : p) { std::cout << value << "\t\t"; }
		std::cout << std::endl;
	}
	void print_border (void) { for (int i = 0; i < 100; i++) { std::cout << '-'; } }
}
