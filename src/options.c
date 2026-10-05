
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "options.h"






void parse_options(int argc, char *argv[], Options *opts, int *opt_ind) {
    int opt;
    opts->show_all = 0;
    opts->show_almost_all = 0;
    opts->long_format = 0;
    opts->numeric_id = 0;
    opts->classify = 0;
    opts->recursive = 0;
    opts->sort_by_time = 0;
    opts->sort_by_size = 0;
    opts->reverse_sort = 0;
    opts->time_type = 0; // 0 = mtime


    while ((opt = getopt(argc, argv, "AaFnlRtrScu")) != -1) {
        switch (opt) {
            case 'a': opts->show_all = 1; break;
            case 'A': opts->show_almost_all = 1; break; 
            case 'l': opts->long_format = 1; break; 
            case 'n': opts->long_format = 1; opts->numeric_id = 1; break;
            case 'F': opts->classify = 1; break; 
            case 'R': opts->recursive = 1; break;
            case 't': opts->sort_by_time = 1; break;
            case 'S': opts->sort_by_size = 1; break; 
            case 'r': opts->reverse_sort = 1; break;
            case 'c': opts->time_type = 2; break; 
            case 'u': opts->time_type = 1; break;
            default:
                fprintf(stderr, "Usage: %s [-AaFnlRtrScu] [file...]\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }
    *opt_ind = optind;
}
