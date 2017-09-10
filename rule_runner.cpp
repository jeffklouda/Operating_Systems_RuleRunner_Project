/* rule_runner.cpp
 * This function will run the commands given to it
 * by the check_functions functions.
 * Authors: Matthew D'Alonzo and Jeff Klouda
 */

#include "rorschach.h"


int run_commands(vector<string> rule, string fileName){
	string command_string = "";
	char* char_baseName = basename(const_cast<char*>(fileName.c_str()));
	string string_baseName = char_baseName; 
	for (uint i=2; i < rule.size(); i++){
		command_string += rule[i];
	}
	cout << "Executing action \"" << command_string << "\" on \"" << string_baseName << "\"" << endl;
	vector<char *> command;
	for (uint i=2; i < rule.size(); i++){
		if (rule[i] == "${BASEPATH}"){
			command.push_back(const_cast<char*>(string_baseName.c_str()));
		}else if (rule[i] == "${FULLPATH}"){
			command.push_back(const_cast<char*>(fileName.c_str()));
		}else{
			command.push_back(const_cast<char*>(rule[i].c_str()));
		}
	}
	command.push_back(NULL);
	char **command_char = &command[0];

	pid_t pid = fork();
	

	switch (pid){
		case -1:		//Error
			fprintf(stderr, "Unable to fork: %s\n", strerror(errno));
			break;
		case 0:			//Child
			execvp(command_char[0], command_char);
			_exit(EXIT_FAILURE);
		default:
			wait(NULL);
			break;
	}

	return EXIT_SUCCESS;
}
