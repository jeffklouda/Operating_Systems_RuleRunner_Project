/* rorschach.cpp 
 * Authors: Matthew D'Alonzo and Jeff Klouda
 * Main file for the rorschach program.
 * 
 */


//Necessary Includes
#include "rorschach.h"
#include <iostream>				//cin, cout
#include <stdlib.h>				//atoi
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <sstream>
#include <fstream>
#include <limits.h>
#include <sys/stat.h>
#include <map>
#include <vector>

//Function prototypes
void rule_loader(vector<vector<string>>&);

//Global Variables
uint TIME_TO_SCAN = 5;
string ROOT;
string RULES_LOCATION = "rules";

//Usage Function
void usage(){
	cout << "Usage: rorschach [options] ROOT							\n"
            "                               							\n"
			"Options:													\n"
			"	-h			Print this help message						\n"
			"	-f RULES	Load rules from this file (default is rules)\n"
			"	-t SECONDS	Time between scans (default is 5 seconds)	\n";
}

//Main Function
int main(int argc, char *argv[]){

	//Command-Line Parsing
	string PROGRAM_NAME = argv[0];
	int arg_index = 1;	
	string flag;
	while (arg_index < (argc)){
		flag = argv[arg_index++];
		if (flag == "-h"){
			usage();
			return 0;
		}else if (flag == "-f"){
			RULES_LOCATION = argv[++arg_index];
		}else if (flag == "-t"){
			TIME_TO_SCAN = atoi(argv[++arg_index]);
		}
	}
	ROOT = flag;
    if (ROOT.empty()) {
        usage();
        return 1;
    }
	string full_root_path = realpath(ROOT.c_str(), NULL);
	vector<vector<string>> rules_list;
	rule_loader(rules_list);
  	
	map<ino_t, file_scan> previous_scan;
	map<ino_t, file_scan> current_scan;

	scan(full_root_path, current_scan);
	
	while(true){
		sleep(TIME_TO_SCAN);
		previous_scan = current_scan;
		scan(full_root_path, current_scan);
		for (uint i = 0; i < rules_list.size(); i++){
			if (rules_list[i][0] == "CREATE"){
				check_create(previous_scan, current_scan, rules_list[i]);
			}else if(rules_list[i][0] == "MODIFY"){
				check_modify(previous_scan, current_scan, rules_list[i]);
			}else if(rules_list[i][0] == "DELETE"){
				check_delete(previous_scan, current_scan, rules_list[i]);
			}
		}
	}
		
	return 0;		//Successful end
}

void rule_loader(vector<vector<string>> &rules_list){
	ifstream opened_file(RULES_LOCATION);
	vector<string> raw_rules;
	string rules_line;
	while (getline(opened_file, rules_line)){
		raw_rules.push_back(rules_line);
	}
	
	string word;
	vector<string> empty_vector;
	for (uint i = 0; i < raw_rules.size(); i++){
		istringstream string_stream(raw_rules[i]);
		rules_list.push_back(empty_vector);
		while (string_stream >> word){
			rules_list[i].push_back(word);
		}
	}
}


