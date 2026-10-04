
#ifndef OPTIONS_H
#define OPTIONS_H

typedef struct {
    int show_all;       // -a: File ẩn
    int long_format;    // -l: Định dạng danh sách dài
    int recursive;      // -R: Đệ quy thư mục
    int sort_by_time;   // -t: Sắp xếp theo thời gian mtime
    int reverse_sort;   // -r: Sắp xếp ngược
} Options;

void parse_options(int argc, char *argv[], Options *opts, int *opt_ind);

#endif
