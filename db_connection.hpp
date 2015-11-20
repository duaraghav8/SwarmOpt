#include "variables.hpp"
typedef unsigned int UINT;

class DBObject {
	private:
		std::string username, password, db_name;
		std::string strat_social, strat_inert_weight;
		std::string result;
		MYSQL *connection;
	public:
		DBObject () : connection (mysql_init (nullptr)) {
			if (!connection) {
				throw (std::runtime_error (pso::ex_db_init_fail));
			}
		}

		void uname (const std::string name) {
			if (name.length () < 1) {
				throw (std::length_error (pso::ex_insufficient_data));
			}
			username = name;
		}
		void passwd (const std::string& pass) {
			if (pass.length () < 1) {
				throw (std::length_error (pso::ex_insufficient_data));
			}
			password = pass;
		}
		void dbname (const std::string& db) {
			if (db.length () < 1) {
				throw (std::length_error (pso::ex_insufficient_data));
			}
			db_name = db;
		}

		void push_parameters (UINT strategy_social, UINT strategy_weight, UINT iter_max, UINT no_improve, UINT swarm_size, UINT neighbours, UINT dim, double inert_weight, double err_threshold, double c1, double c2, double x_hi, double x_lo, double w_hi, double w_lo, bool verbose, bool db_store, bool halt_iter_l, bool halt_no_imp, bool halt_err_thresh) {

		}

		void push_result (std::vector< double >& particle_gbest) {
			std::stringstream converter;
			std::string temp;
			for (auto dimension : particle_gbest) {
				converter << dimension;
				converter >> temp;
				converter.clear ();
				result += temp + " ";
			}
		}

		void flush (void) {
		}
};
