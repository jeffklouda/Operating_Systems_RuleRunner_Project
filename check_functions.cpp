/* check_functions.cpp
 * This contains the functions that check if a file has
 * been CREATED, MODIFIED, or DELETED
 * Authors: Matthew D'Alonzo and Jeff Klouda
 */

#include "rorschach.h"
#include <sys/stat.h>
#include <map>
#include <vector>
#include <string>

void check_create(map<ino_t,file_scan> &prev_scan,
                    map<ino_t,file_scan> &curr_scan,
                    vector<string> &rule) {
    
    for (auto it = curr_scan.begin(); it != curr_scan.end(); ++it) {
        std::map<ino_t,file_scan>::iterator findIt;
        findIt = prev_scan.find(it->first);
        if (findIt == prev_scan.end()) {
            // file created
        }
    }   
}

void check_modify(map<ino_t,file_scan> &prev_scan,
                    map<ino_t,file_scan> &curr_scan,
                    vector<string> &rule) {

    for (auto it = curr_scan.begin(); it != curr_scan.end(); ++it) {
        std::map<ino_t,file_scan>::iterator findIt;
        findIt = prev_scan.find(it->first);
        if (findIt->second.lastMod != it->second.lastMod) {
            // file modified
        }
    }
}

void check_delete(map<ino_t,file_scan> &prev_scan,
                    map<ino_t,file_scan> &curr_scan,
                    vector<string> &rule) {

    for (auto it = prev_scan.begin(); it != prev_scan.end(); ++it) {
        std::map<ino_t,file_scan>::iterator findIt;
        findIt = curr_scan.find(it->first);
        if (findIt == curr_scan.end()) {
            // file deleted
        }
    }
}
