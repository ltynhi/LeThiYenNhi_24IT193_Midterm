
#include <stdio.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <unistd.h>
#include "display.h"

static void format_permissions(mode_t mode, char *str) {
    str[0] = S_ISDIR(mode)  ? 'd' :
             S_ISLNK(mode)  ? 'l' :
             S_ISCHR(mode)  ? 'c' :
             S_ISBLK(mode)  ? 'b' :
             S_ISFIFO(mode) ? 'p' :
             S_ISSOCK(mode) ? 's' : '-';

    str[1] = (mode & S_IRUSR) ? 'r' : '-';
    str[2] = (mode & S_IWUSR) ? 'w' : '-';
    str[3] = (mode & S_IXUSR) ? 'x' : '-';

    str[4] = (mode & S_IRGRP) ? 'r' : '-';
    str[5] = (mode & S_IWGRP) ? 'w' : '-';
    str[6] = (mode & S_IXGRP) ? 'x' : '-';

    str[7] = (mode & S_IROTH) ? 'r' : '-';
    str[8] = (mode & S_IWOTH) ? 'w' : '-';
    str[9] = (mode & S_IXOTH) ? 'x' : '-';

    str[10] = '\0';
}

static void print_long_format(const FileInfo *file) {
    char perm[11];
    format_permissions(file->statbuf.st_mode, perm);

    struct passwd *pw = getpwuid(file->statbuf.st_uid);
    struct group  *gr = getgrgid(file->statbuf.st_gid);

    char time_buf[64];
    struct tm *tm_info = localtime(&file->statbuf.st_mtime);
    strftime(time_buf, sizeof(time_buf), "%b %e %H:%M", tm_info);

    printf("%s %2lu %-8s %-8s %8lld %s %s",
           perm,
           (unsigned long)file->statbuf.st_nlink,
           pw ? pw->pw_name : "UNKNOWN",
           gr ? gr->gr_name : "UNKNOWN",
           (long long)file->statbuf.st_size,
           time_buf,
           file->name);

    if (S_ISLNK(file->statbuf.st_mode)) {
        char link_target[1024];
        ssize_t len = readlink(file->path, link_target, sizeof(link_target) - 1);
        if (len != -1) {
            link_target[len] = '\0';
            printf(" -> %s", link_target);
        }
    }
    printf("\n");
}

void display_files(FileInfo *files, int count, const Options *opts) {
    for (int i = 0; i < count; i++) {
        if (opts->long_format) {
            print_long_format(&files[i]);
        } else {
            printf("%s  ", files[i].name);
        }
    }
    if (!opts->long_format && count > 0) {
        printf("\n");
    }
}
