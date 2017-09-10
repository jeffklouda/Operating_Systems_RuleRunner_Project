#include <string>
#include <sys/stat.h>
#include "rorschach.h"

struct file_scan {
    std::string name;
    time_t lastMod;
    ino_t inode;
};

