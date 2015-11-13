#include "includes.hpp"
#include "variables.h"
typedef const unsigned int UINT;

class DBObject {
	private:
		std::string username, password, db_name;
		std::string strat_social, strat_inert_weight;
		MYSQL *connection;
	public:
		DBObject () : connection (mysql_init (nullptr)) {
			if (!connection) {
				throw (std::runtime_error (pso::ex_db_connect_fail);
			}
		}

		void uname (const std::string& name) { username = name; }
		void passwd (const std::string& pass) { username = pass; }
		void dbname (const std::string& db) { username = db; }

		void push_data (UINT social_strategy, UINT knn_neighbours, UINT iw_strategy, double iw_const_iw, double iw_ld_hi, double iw_ld_lo) {
			if (uname.length () + passwd.length () + dbname.length () < 3) {
				throw (std::length_error (pso::ex_insufficient_data));
			}
		}
};
