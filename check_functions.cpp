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

extern int ROOT_STRING_LENGTH;
extern string ROOT;
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
			string extended_filename = ROOT + it->second.name.erase(0, ROOT_STRING_LENGTH);
            cout << extended_filename;
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
        if (findIt != prev_scan.end() && 
            findIt->second.lastMod != it->second.lastMod) {
            // file modified
            modifyVec.push_back(it->second);
            cout << "Detected \"MODIFY\" event on \"";
            string extended_filename = ROOT + it->second.name.erase(0, ROOT_STRING_LENGTH);
            cout << extended_filename;
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
            string extended_filename = ROOT + it->second.name.erase(0, ROOT_STRING_LENGTH);
            cout << extended_filename;
            cout << "\"\n";
        }
    }
}

void check_match (vector<string> &rule, file_scan fileN) {
    char* fullPathName = const_cast<char*>(fileN.name.c_str());
    char* fileName = basename(const_cast<char*>(fileN.name.c_str()));
    if (!fnmatch(rule[1].c_str(), (const char*)fileName, FNM_EXTMATCH)
        || !fnmatch(rule[1].c_str(), fileN.name.c_str(), FNM_EXTMATCH)) {
        // run rule
        cout << "Matched \"" << rule[1] << "\" pattern on \"";
        cout << fileName << "\"\n";
        run_commands(rule, fullPathName, fileN.lastMod);
    }    
}
