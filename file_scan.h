#ifndef FILE_SCAN
#define FILE_SCAN

#include <sys/stat.h>

struct file_scan {
    string name;
    time_t lastMod;
}

#endif
