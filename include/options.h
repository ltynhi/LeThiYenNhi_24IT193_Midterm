
#ifndef OPTIONS_H
#define OPTIONS_H




typedef struct {
    int show_all;       // -a
    int show_almost_all;// -A
    int long_format;    // -l
    int numeric_id;     // -n
    int classify;       // -F
    int recursive;      // -R 
    int sort_by_time;   // -t
    int sort_by_size;   // -S
    int reverse_sort;   // -r
    int time_type;      // 0
} Options;

void parse_options(int argc, char *argv[], Options *opts, int *opt_ind);

#endif

