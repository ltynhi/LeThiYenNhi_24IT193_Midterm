
#include <stdio.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include "display.h"


static void format_permissions(mode_t mode, char *str) {
    str[0] = S_ISDIR(mode)  ? 'd' :
             S_ISLNK(mode)  ? 'l' :
             S_ISCHR(mode)  ? 'c' :
             S_ISBLK(mode)  ? 'b' :
             S_ISFIFO(mode) ? 'p' :
             S_ISSOCK(mode) ? 's' : '-'; //[cite: 3]

    str[1] = (mode & S_IRUSR) ? 'r' : '-';
    str[2] = (mode & S_IWUSR) ? 'w' : '-';
    if (mode & S_ISUID) str[3] = (mode & S_IXUSR) ? 's' : 'S'; //[cite: 4]
    else str[3] = (mode & S_IXUSR) ? 'x' : '-';

    str[4] = (mode & S_IRGRP) ? 'r' : '-';
    str[5] = (mode & S_IWGRP) ? 'w' : '-';
    if (mode & S_ISGID) str[6] = (mode & S_IXGRP) ? 's' : 'S'; //[cite: 4]
    else str[6] = (mode & S_IXGRP) ? 'x' : '-';

    str[7] = (mode & S_IROTH) ? 'r' : '-';
    str[8] = (mode & S_IWOTH) ? 'w' : '-';
    if (mode & S_ISVTX) str[9] = (mode & S_IXOTH) ? 't' : 'T'; //[cite: 4]
    else str[9] = (mode & S_IXOTH) ? 'x' : '-';

    str[10] = '\0';
}


static char get_classify_char(mode_t mode) {
    if (S_ISDIR(mode)) return '/'; //[cite: 2]
    if (S_ISLNK(mode)) return '@'; //[cite: 2]
    if (S_ISSOCK(mode)) return '='; //[cite: 2]
    if (S_ISFIFO(mode)) return '|'; //[cite: 2]
    if (mode & (S_IXUSR | S_IXGRP | S_IXOTH)) return '*'; //[cite: 2]
    return '\0';
}

static void print_long_format(const FileInfo *file, const Options *opts) {
    char perm[11];
    format_permissions(file->statbuf.st_mode, perm);

    char user_str[32], group_str[32];
    

    if (opts->numeric_id) {
        snprintf(user_str, sizeof(user_str), "%u", file->statbuf.st_uid);
        snprintf(group_str, sizeof(group_str), "%u", file->statbuf.st_gid);
    } else {
        struct passwd *pw = getpwuid(file->statbuf.st_uid);
        struct group  *gr = getgrgid(file->statbuf.st_gid);
        if (pw) snprintf(user_str, sizeof(user_str), "%s", pw->pw_name);
        else snprintf(user_str, sizeof(user_str), "%u", file->statbuf.st_uid);

        if (gr) snprintf(group_str, sizeof(group_str), "%s", gr->gr_name);
        else snprintf(group_str, sizeof(group_str), "%u", file->statbuf.st_gid);
    }


    time_t file_time = file->statbuf.st_mtime;
    if (opts->time_type == 1) file_time = file->statbuf.st_atime; // -u[cite: 3]
    else if (opts->time_type == 2) file_time = file->statbuf.st_ctime; // -c[cite: 2]

    char time_buf[64];
    struct tm *tm_info = localtime(&file_time);
    strftime(time_buf, sizeof(time_buf), "%b %e %H:%M", tm_info);

    printf("%s %2lu %-8s %-8s %8lld %s %s",
           perm,
           (unsigned long)file->statbuf.st_nlink,
           user_str,
           group_str,
           (long long)file->statbuf.st_size,
           time_buf,
           file->name);

    if (opts->classify) {
        char c = get_classify_char(file->statbuf.st_mode);
        if (c != '\0') printf("%c", c);
    }

    if (S_ISLNK(file->statbuf.st_mode)) {
        char link_target[1024];
        ssize_t len = readlink(file->path, link_target, sizeof(link_target) - 1);
        if (len != -1) {
            link_target[len] = '\0';
            printf(" -> %s", link_target); //[cite: 3]
        }
    }
    printf("\n");
}

void display_files(FileInfo *files, int count, const Options *opts) {

    if (opts->long_format && count > 0) {
        long long total_blocks = 0;
        for (int i = 0; i < count; i++) {
            total_blocks += files[i].statbuf.st_blocks;
        }
        printf("total %lld\n", total_blocks); //[cite: 3]
    }

    for (int i = 0; i < count; i++) {
        if (opts->long_format) {
            print_long_format(&files[i], opts);
        } else {
            printf("%s", files[i].name);
            if (opts->classify) {
                char c = get_classify_char(files[i].statbuf.st_mode);
                if (c != '\0') printf("%c", c);
            }
            printf("\n");
        }
    }
}
