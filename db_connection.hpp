#include "includes.hpp"

class DBObject {
	private:
		std::string username, password, db_name;
		std::string strat_social, strat_inert_weight;
	public:
		void uname (const std::string& name) { username = name; }
		void passwd (const std::string& pass) { username = pass; }
		void dbname (const std::string& db) { username = db; }
};
