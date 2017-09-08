#ifndef SCANNER
#define SCANNER

#include <string.h>
#include <errno.h>
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>

#include <sys/types.h>
#include <sys/stat.h>

#include "file_scan.h"
#include <string>
#include <vector>

using namespace std;

void scan(string root, vector<file_scan> fileVector) {
    DIR *dir;
    struct dirent *dp;
    struct stat buf;
    if (lstat(root.c_str(), &buf) < 0) {
        printf("Couldn't scan %s: %s\n", root.c_str(), strerror(errno));
        return;
    }
    
    if (S_ISDIR(buf.st_mode)) {

        if ((dir = opendir(root.c_str())) == NULL) {
            printf("Couldn't open directory %s: %s\n", root.c_str(), strerror(errno));
            return;
        }
        while ((dp = readdir(dir)) != NULL) {
            if (strcmp(dp->d_name, ".")!=0 && strcmp(dp->d_name, "..")!=0){ 
                string d_name = dp->d_name;
                string full_path = root + "/" + d_name;
                scan(full_path, fileVector);
            }
        }
    }
    else {

        file_scan foundFile;
        foundFile.name = root; 
        foundFile.lastMod = buf.st_mtime;
        foundFile.inode = buf.st_ino;
        fileVector.push_back(foundFile);
    
    }    
}
#endif
