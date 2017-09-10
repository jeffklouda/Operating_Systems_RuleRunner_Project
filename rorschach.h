#ifndef RORSCHACH_H
#define RORSCHACH_H

#include <string.h>
#include <errno.h>
#include <string>
#include <sys/stat.h>
#include <vector>
#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>
#include <map>

using namespace std;

struct file_scan {		//file_scan struct
    std::string name;
    time_t lastMod;
    ino_t inode;
};

void scan(string root, map<ino_t, file_scan> &fileVector); //file scanner function
														   //(contained in scanner.cpp)


int run_commands(vector<string> rule);	//fork() and exec() function
										//(contained in rule_runner.cpp)

#endif
