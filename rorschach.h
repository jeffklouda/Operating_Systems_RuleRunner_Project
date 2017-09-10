#ifndef RORSCHACH_H
#define RORSCHACH_H

#include <string.h>			//C string library
#include <errno.h>			//errno
#include <string>			//STL Strings
#include <sys/stat.h>		//stat()
#include <vector>			//STL Vectors
#include <stdio.h>			//stdio
#include <sys/types.h>		//some types
#include <fcntl.h>			//fcntl
#include <signal.h>			//signal management
#include <sys/wait.h>		//wait (for parent)
#include <unistd.h>			//unistd
#include <map>				//STL maps
#include <iostream>			//cin, cout

using namespace std;


//Structs

struct file_scan {		//file_scan struct
    std::string name;
    time_t lastMod;
    ino_t inode;
};


//Function prototypes

void rule_loader(vector<vector<string>>&); //(contained in rorschach.cpp)

void scan(string root, map<string, file_scan> &fileMap); //file scanner function
														   //(contained in scanner.cpp)


int run_commands(vector<string> rule, string fileName);	//fork() and exec() function
										//(contained in rule_runner.cpp)

void check_create(map<string,file_scan> &prev_scan,			//checks creations
                    map<string,file_scan> &curr_scan,		//(contained in check_functions.cpp)
                    vector<string> &rule);

void check_modify(map<string,file_scan> &prev_scan,			//checks modifications
                    map<string,file_scan> &curr_scan,		//(contained in check_functions.cpp)
                    vector<string> &rule);

void check_delete(map<string,file_scan> &prev_scan,			//checks deletions
                    map<string,file_scan> &curr_scan,		//(contained in check_functions.cpp)
                    vector<string> &rule);

#endif
