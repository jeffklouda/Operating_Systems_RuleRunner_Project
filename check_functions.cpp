/* check_functions.cpp
 * This contains the functions that check if a file has
 * been CREATED, MODIFIED, or DELETED
 * Authors: Matthew D'Alonzo and Jeff Klouda
 */

#include "rorschach.h"
#include <sys/stat.h>
#include <libgen.h>
#include <map>
#include <vector>
#include <string>
#include <regex>
#include <iostream>
#include <glob.h>
#include <fnmatch.h>

using namespace std;

void check_create(  map<string,file_scan> &prev_scan,
                    map<string,file_scan> &curr_scan,
                    vector<file_scan> &createVec) {

    for (auto it = curr_scan.begin(); it != curr_scan.end(); ++it) {
        map<string,file_scan>::iterator findIt;
        findIt = prev_scan.find(it->first);
        if (findIt == prev_scan.end()) {
            // file created
            createVec.push_back(it->second);
            cout << "Detected \"CREATE\" event on \"";
            cout << basename(const_cast<char*>(it->first.c_str()));
            cout << "\"\n";
        }
    }   
}

void check_modify(  map<string,file_scan> &prev_scan,
                    map<string,file_scan> &curr_scan,
                    vector<file_scan> &modifyVec) {

    for (auto it = curr_scan.begin(); it != curr_scan.end(); ++it) {
        map<string,file_scan>::iterator findIt;
        findIt = prev_scan.find(it->first);
        if (findIt->second.lastMod != it->second.lastMod) {
            // file modified
            modifyVec.push_back(it->second);
            cout << "Detected \"MODIFY\" event on \"";
            cout << basename(const_cast<char*>(it->first.c_str()));
            cout << "\"\n";
        }
    }
}

void check_delete(  map<string,file_scan> &prev_scan,
                    map<string,file_scan> &curr_scan,
                    vector<file_scan> &deleteVec) {

    for (auto it = prev_scan.begin(); it != prev_scan.end(); ++it) {
        map<string,file_scan>::iterator findIt;
        findIt = curr_scan.find(it->first);
        if (findIt == curr_scan.end()) {
            // file deleted
            deleteVec.push_back(it->second);
            cout << "Detected \"DELETE\" event on \"";
            cout << basename(const_cast<char*>(it->first.c_str()));
            cout << "\"\n";
        }
    }
}

void check_match (vector<string> &rule, string fileN) {
    char* fileName = basename(const_cast<char*>(fileN.c_str()));
    if (!fnmatch(rule[1].c_str(), (const char*)fileName, FNM_EXTMATCH)) {
        // run rule
        cout << "Matched \"" << rule[1] << "\" pattern on \"";
        cout << fileName << "\"\n";
        run_commands(rule, fileName);
    }    
}
