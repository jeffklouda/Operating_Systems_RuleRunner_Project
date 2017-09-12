/* rule_runner.cpp
 * This function will run the commands given to it
 * by the check_functions functions.
 * Authors: Matthew D'Alonzo and Jeff Klouda
 */

#include "rorschach.h"

extern int ROOT_STRING_LENGTH;
extern string ROOT;

int run_commands(vector<string> rule, string fileName, time_t timeStamp){
	string command_string = "";
	char* char_baseName = basename(const_cast<char*>(fileName.c_str()));
	string string_baseName = char_baseName; 
	for (uint i=2; i < rule.size(); i++){
		command_string += rule[i];
		command_string += " ";
	}
	cout << "Executing action \"" << command_string << "\" on \"" << string_baseName << "\"" << endl;
	vector<char *> command;
	int output_fd = STDOUT_FILENO;
	for (uint i=2; i < rule.size(); i++){
		if (rule[i] == "${BASEPATH}" || rule[i] == "${{BASEPATH}}"){
			//size_t lastdot = string_baseName.find_last_of(".");
			//if (lastdot != string::npos){
			command.push_back(char_baseName);
			//}
		}else if (rule[i] == "${FULLPATH}" || rule[i] == "${{FULLPATH}}"){
			string extended_filename = ROOT + '/' + char_baseName;
			command.push_back(const_cast<char*>(extended_filename.c_str()));
		}else if (rule[i] == "${TIMESTAMP}" || rule[i] == "${{TIMESTAMP}}"){
			string string_timeStamp = to_string(timeStamp);
			command.push_back(const_cast<char*>(string_timeStamp.c_str()));
		}else if (rule[i] == "${EVENT}" || rule[i] == "${{EVENT}}"){
			command.push_back(const_cast<char*>(rule[0].c_str()));
		}else if (rule[i] == ">>"){
			output_fd = open(rule[i+1].c_str(), O_WRONLY | O_CREAT | O_APPEND, 0644);	
			break;
		}else if (rule[i] == ">"){
			fclose(fopen(rule[i+1].c_str(), "w"));			
			output_fd = open(rule[i+1].c_str(), O_WRONLY | O_CREAT, 0644);
			break;
		}else{
			command.push_back(const_cast<char*>(rule[i].c_str()));
		}
	}
	command.push_back(NULL);
	char **command_char = &command[0];

	//char ** ptr = command_char;
	//for (char *c = *ptr; c; c=*++ptr){
	//	cout << "command_char: " << c << endl;
	//}
	pid_t pid = fork();
	

	switch (pid){
		case -1:		//Error
			fprintf(stderr, "Unable to fork: %s\n", strerror(errno));
			break;
		case 0:			//Child
			dup2(output_fd, STDOUT_FILENO);
			execvp(command_char[0], command_char);
			_exit(EXIT_FAILURE);
		default:
			wait(NULL);
			break;
	}

	return EXIT_SUCCESS;
}
