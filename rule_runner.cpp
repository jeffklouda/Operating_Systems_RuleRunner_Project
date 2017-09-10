/* rule_runner.cpp
 * This function will run the commands given to it
 * by the check_functions functions.
 * Authors: Matthew D'Alonzo and Jeff Klouda
 */

#include "rorschach.h"



void run_commands(vector<string> rule){
	string command = "";
	for (int i=3; i < rule.size(); i++){
		command += rule[i];
	}

	int status;
	pid_t pid = fork();
	

	switch (pid){
		case -1:		//Error
			fprintf(stderr, "Unable to fork: %s\n", strerror(errno));
			break;
		case 0:			//Child
			execvp(rule[2].c_str(), command.c_str());
			_exit(EXIT_FAILURE);
		default:
			wait(NULL);
			break;
	}

	return EXIT_SUCCESS;
}
