#include "variables.hpp"
typedef unsigned int UINT;

class DBObject {
	private:
		std::vector< std::string > parameters;
		std::string username, password, db_name, buffer;
		std::string result, result_err;
		std::stringstream converter;
		MYSQL *connection;

	public:
		DBObject () = default;
		void construct (void) {
			connection = mysql_init (nullptr);
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

		void push_parameters (UINT strategy_social, UINT neighbours, UINT strategy_weight, UINT iter_max, UINT no_improve, UINT swarm_size, UINT dim, double inert_weight, double err_threshold, double c1, double c2, double x_hi, double x_lo, double w_hi, double w_lo, bool verbose, bool db_store, bool halt_iter_l, bool halt_no_imp, bool halt_err_thresh) {
			if (strategy_social == pso::STRATEGY_GLOBAL) { parameters.push_back ("\"GLOBAL\""); } else { parameters.push_back ("\"KNN\""); }

			converter << neighbours;
			converter >> buffer;
			converter.clear ();
			parameters.push_back (buffer);

			if (strategy_weight == pso::STRATEGY_W_CONST) { parameters.push_back ("\"CONSTANT\""); } else { parameters.push_back ("\"LINEAR DECREASE\""); }

			converter << inert_weight;
			converter >> buffer;
			converter.clear ();
			parameters.push_back (buffer);

			converter << w_hi;
			converter >> buffer;
			converter.clear ();
			parameters.push_back (buffer);

			converter << w_lo;
			converter >> buffer;
			converter.clear ();
			parameters.push_back (buffer);

			if (halt_err_thresh) { parameters.push_back ("\"THRESHOLD ERROR SET\""); } else { parameters.push_back ("\"THRESHOLD ERROR NOT SET\""); }

			converter << err_threshold;
			converter >> buffer;
			converter.clear ();
			parameters.push_back (buffer);

			if (halt_iter_l) { parameters.push_back ("\"ITERATION LIMIT SET\""); } else { parameters.push_back ("\"ITERATION LIMIT NOT SET\""); }

			converter << iter_max;
			converter >> buffer;
			converter.clear ();
			parameters.push_back (buffer);

			if (halt_no_imp) { parameters.push_back ("\"NO IMPROVE SET\""); } else { parameters.push_back ("\"NO IMPROVE NOT SET\""); }

			converter << no_improve;
			converter >> buffer;
			converter.clear ();
			parameters.push_back (buffer);

			converter << swarm_size;
			converter >> buffer;
			converter.clear ();
			parameters.push_back (buffer);

			converter << c1;
			converter >> buffer;
			converter.clear ();
			parameters.push_back (buffer);

			converter << c2;
			converter >> buffer;
			converter.clear ();
			parameters.push_back (buffer);

		}

		void push_result (const std::vector< double >& particle_gbest, const double error) {
			for (auto dimension : particle_gbest) {
				converter << dimension;
				converter >> buffer;
				converter.clear ();
				result += buffer + " | ";
			}

			converter << error;
			converter >> result_err;
			converter.clear ();
		}

		void flush (void) {
			std::string query = "INSERT INTO Logs (Social_Strategy, Number_of_neighbours, Inertia_Weight_Strategy, Inertia_Weight_Const_IW, IW_Lin_Dec_upper, IW_Lin_Dec_lower, Fitness_Threshold_Exists, Fitness_Threshold, Limited_Iterations_Exists, Limited_Iterations, No_Improve_Strategy_Exists, No_Improve_Iterations, Swarm_Size, Cogni_Const, Social_Const, Final_Answer, Final_Ans_Error) values (";
			connection = mysql_real_connect (connection, "localhost", username.c_str (), password.c_str (), db_name.c_str (), 0, nullptr, 0);
			if (connection) {
				//EXCEPTION TO BE ADDED
			}
			for (auto p : parameters) {
				query += p + ", ";
			}
			query += ("\"" + result + "\", " + result_err + ")");
			mysql_query (connection, query.c_str ());
		}
};
