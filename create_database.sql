/*
    First, log into your MySql Client (Command Line):
        mysql -u username -p <ENTER>
        Enter Password: ***** <ENTER>
    
    Then at the main console, type:
        source path/to/create_database.sql
*/

Create Database PSO;
Use PSO;

Create table Logs(
	Social_Strategy varchar(50),
	Number_of_neighbours integer,
	Inertia_Weight_Strategy varchar(50),
	Inertia_Weight_Const_IW double(4,4),
	IW_Lin_Dec_upper double(4,4),
	IW_Lin_Dec_lower double(4,4),
	Fitness_Threshold_Exists boolean,
	Fitness_Threshold varchar (100),
	Limited_Iterations_Exists boolean,
	Limited_Iterations integer,
	No_Improve_Strategy_Exists boolean,
	No_Improve_Iterations integer,
	Swarm_Size integer,
	Cogni_Const double(4,4),
	Social_Const double(4,4),
	Final_Answer varchar(1000),
	Final_Ans_Error double(10,10)
);
