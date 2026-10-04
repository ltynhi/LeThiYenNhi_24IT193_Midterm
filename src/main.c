
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include "ls.h"
#include "options.h"
#include "display.h"

static const Options *g_opts;

static int compare_files(const void *a, const void *b) {
    const FileInfo *f1 = (const FileInfo *)a;
    const FileInfo *f2 = (const FileInfo *)b;
    int res = 0;

    if (g_opts->sort_by_time) {
        if (f1->statbuf.st_mtime < f2->statbuf.st_mtime) res = 1;
        else if (f1->statbuf.st_mtime > f2->statbuf.st_mtime) res = -1;
        else res = strcmp(f1->name, f2->name);
    } else {
        res = strcmp(f1->name, f2->name);
    }

    return g_opts->reverse_sort ? -res : res;
}

void process_path(const char *path, const Options *opts) {
    g_opts = opts;
    struct stat path_stat;

    if (lstat(path, &path_stat) == -1) {
        perror(path);
        return;
    }

    if (!S_ISDIR(path_stat.st_mode)) {
        FileInfo file;
        strncpy(file.name, path, sizeof(file.name));
        strncpy(file.path, path, sizeof(file.path));
        file.statbuf = path_stat;
        display_files(&file, 1, opts);
        return;
    }

    DIR *dir = opendir(path);
    if (!dir) {
        perror(path);
        return;
    }

    struct dirent *entry;
    FileInfo *files = NULL;
    int count = 0;
    int capacity = 0;

    while ((entry = readdir(dir)) != NULL) {
        if (!opts->show_all && entry->d_name[0] == '.') {
            continue;
        }

        if (count >= capacity) {
            capacity = capacity == 0 ? 16 : capacity * 2;
            files = realloc(files, capacity * sizeof(FileInfo));
        }

        strncpy(files[count].name, entry->d_name, sizeof(files[count].name));
        snprintf(files[count].path, sizeof(files[count].path), "%s/%s", path, entry->d_name);

        if (lstat(files[count].path, &files[count].statbuf) == -1) {
            perror("lstat");
            continue;
        }
        count++;
    }
    closedir(dir);

    qsort(files, count, sizeof(FileInfo), compare_files);
    display_files(files, count, opts);

    if (opts->recursive) {
        for (int i = 0; i < count; i++) {
            if (S_ISDIR(files[i].statbuf.st_mode)) {
                if (strcmp(files[i].name, ".") == 0 || strcmp(files[i].name, "..") == 0) {
                    continue;
                }
                printf("\n%s:\n", files[i].path);
                process_path(files[i].path, opts);
            }
        }
    }

    free(files);
}

int main(int argc, char *argv[]) {
    Options opts;
    int opt_ind;

    parse_options(argc, argv, &opts, &opt_ind);

    if (opt_ind == argc) {
        process_path(".", &opts);
    } else {
        for (int i = opt_ind; i < argc; i++) {
            if (argc - opt_ind > 1) {
                printf("%s:\n", argv[i]);
            }
            process_path(argv[i], &opts);
            if (i < argc - 1) printf("\n");
        }
    }

    return 0;
}
