#ifndef RORSCHACH_H
#define RORSCHACH_H

#include <string>
#include <sys/stat.h>
#include <vector>

using namespace std;

struct file_scan {
    std::string name;
    time_t lastMod;
    ino_t inode;
};

void scan(string root, vector<file_scan> &fileVector);


#endif
