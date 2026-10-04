
#Midterm Project: Implementation of UNIX ls(1)

- **Student Name:** Le Thi Yen Nhi
- **Student ID:** 24IT193
- **Repository:** https://github.com/USERNAME/LeThiYenNhi_24IT193_midterm

## Description
This project implements a simplified version of the UNIX `ls(1)` command in C, targeting NetBSD/POSIX environments.

## Options Implemented
- `-a`: List all entries including hidden ones (starting with `.`).
- `-l`: Use a long listing format (permissions, links, owner, group, size, time, name).
- `-R`: List subdirectories recursively.
- `-t`: Sort by modification time (newest first).
- `-r`: Reverse sort order.

## Build and Run Instructions
To build the binary:
```bash
make
