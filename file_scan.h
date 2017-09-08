#ifndef FILE_SCAN
#define FILE_SCAN

#include <string>
#include <sys/stat.h>

struct file_scan {
    std::string name;
    time_t lastMod;
};

#endif
