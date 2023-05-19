#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <stdbool.h>

#include "kmp.h"
#include "dir.h"

int main(int argc, char *argv[])
{
    char *dirpath, *pattern;
    char colors[][5] = {"0;36", "0;31"};
    
    if (strcmp(argv[1], "-r") == 0)
    {
        if (argc != 4)
        {
            printf("%s%smERROR: Wrong number of arguments!%s0m\n", CSI, colors[1], CSI);
            return 0;
        }
        pattern = argv[2];
        dirpath = argv[3];

        rec_check_dir(dirpath, pattern);
    }
    else
    {
        if (argc != 3)
        {
            printf("%s%smERROR: Wrong number of arguments!%s0m\n", CSI, colors[1], CSI);
            return 0;
        }
        pattern = argv[1];
        dirpath = argv[2];

        check_dir(dirpath, pattern);
    }
    return 0;
}