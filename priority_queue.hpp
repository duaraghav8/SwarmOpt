#include "includes.hpp"

namespace pso {
	class simple_tuple {
		private:
			unsigned int distance, position;
		public:
			simple_tuple ( unsigned int x, unsigned int y ) : distance (x), position (y) { }

			unsigned int dist (void) const { return (distance); }
			unsigned int pos (void) const { return (position); }
	};

	class simple_tuple_compare {
		public:
			bool operator () (simple_tuple& x, simple_tuple& y) {
				return (x.dist () > y.dist ());
			}
	};

	typedef std::priority_queue< simple_tuple, std::vector< simple_tuple >, simple_tuple_compare > priority_queue;
}
