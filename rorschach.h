#ifndef RORSCHACH_H
#define RORSCHACH_H

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


using namespace std;

struct file_scan {
    std::string name;
    time_t lastMod;
    ino_t inode;
};

void scan(string root, vector<file_scan> &fileVector);


#endif
