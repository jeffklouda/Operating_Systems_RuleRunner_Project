/* rorschach.cpp 
 * Authors: Matthew D'Alonzo and Jeff Klouda
 * Main file for the rorschach program.
 * 
 */


//Necessary Includes
#include <iostream>				//cin, cout
#include <string>				//string
#include <stdlib.h>				//atoi
#include <sys/stat.h>			//stat()
#include <sys/types.h>
#include <fcntl.h>
#include <vector>				//vectors
#include <unistd.h>
#include <sstream>
#include <fstream>

using namespace std;			//STL namespace

//Function prototypes
void rule_loader(vector<string>&);

//Global Variables
int TIME_TO_SCAN = 5;
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

	vector<string> rules_list;
	rule_loader(rules_list);



	return 0;		//Successful end
}

void rule_loader(vector<string> &rules_list){
	ifstream opened_file(RULES_LOCATION);
	string rules_line;
	while (getline(opened_file, rules_line)){
		rules_list.push_back(rules_line);
	}
}


