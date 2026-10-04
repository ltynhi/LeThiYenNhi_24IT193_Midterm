
#ifndef LS_H
#define LS_H

#include <sys/stat.h>
#include "options.h"

typedef struct {
    char name[256];
    char path[1024];
    struct stat statbuf;
} FileInfo;

void process_path(const char *path, const Options *opts);

#endif
