/* rorschach.cpp 
 * Authors: Matthew D'Alonzo and Jeff Klouda
 * Main file for the rorschach program.
 * 
 */


//Necessary Includes
#include "rorschach.h"			//header file (contains prototypes)
#include <iostream>				//cin, cout
#include <stdlib.h>				//atoi
#include <sys/types.h>			//contains types
#include <fcntl.h>				//Arguments for use by open()
#include <unistd.h>				//standard symbolic constant
#include <sstream>				//stringstreams
#include <fstream>				//file input/output
#include <limits.h>				//Macros
#include <sys/stat.h>			//stat()
#include <map>					//STL Maps
#include <vector>				//STL Vectors

//Global Variables

uint TIME_TO_SCAN = 5;
string ROOT;
string RULES_LOCATION = "rules";
bool runningFlag = true;

//Usage Function
void usage(){
	cout << "Usage: rorschach [options] ROOT							\n"
            "                               							\n"
			"Options:													\n"
			"	-h			Print this help message						\n"
			"	-f RULES	Load rules from this file (default is rules)\n"
			"	-t SECONDS	Time between scans (default is 5 seconds)	\n";
}

//Signal Handler
void sig_handler (int sig) {
    cout << "\nCleaning up...\n";
    runningFlag = false;
}

//Main Function
int main(int argc, char *argv[]){

	signal(SIGINT, sig_handler);
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
  	
	map<string, file_scan> previous_scan;
	map<string, file_scan> current_scan;
    vector<file_scan> createVec;
    vector<file_scan> modifyVec;
    vector<file_scan> deleteVec;

	scan(full_root_path, current_scan);
	
	cout << "Monitoring " << full_root_path << endl;
	while(runningFlag){
		previous_scan = current_scan;
		current_scan.clear();
		scan(full_root_path, current_scan);
		
        createVec.clear();
        modifyVec.clear();
        deleteVec.clear();
        check_create(previous_scan, current_scan, createVec);
        check_modify(previous_scan, current_scan, modifyVec);
        check_delete(previous_scan, current_scan, deleteVec);

        for (uint i = 0; i < rules_list.size(); i++){
			//cout << "HERE0\n";
			if (rules_list[i][0] == "CREATE"){
				//cout << "HERE1\n";
				for (auto it = createVec.begin(); it != createVec.end(); ++it) {
					cout << "HERE\n";
                    check_match(rules_list[i], *it);
                }
			}else if(rules_list[i][0] == "MODIFY"){
				for (auto it = modifyVec.begin(); it != modifyVec.end(); ++it) {
                    check_match(rules_list[i], *it);
                }
			}else if(rules_list[i][0] == "DELETE"){
				for (auto it = deleteVec.begin(); it != deleteVec.end(); ++it) {
                    check_match(rules_list[i], *it);
                }
			}else{
				fprintf(stderr, "Unable to understand rule. Maybe you typed it in wrong?\n");
				return EXIT_FAILURE;
		}
		}
	sleep(TIME_TO_SCAN);
	}
	cout << "Bye!\n";	
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

