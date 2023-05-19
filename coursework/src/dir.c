#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <stdbool.h>
#include <string.h>
#include <sys/types.h>

#include "dir.h"
#include "kmp.h"

char colors[][5] = {"0;36", "0;31"};

int check_file(char *path, char *pattern)
{
    FILE *in;
    char *text;
    int superpos, position;
    in = fopen(path, "r");
    if (in != NULL)
    {
        superpos = 0;
        position = 0;
        text = malloc(100 * sizeof(char));
        while (fgets(text, 100, in) != NULL)
        {
            position = kmp_seeker(text, pattern);
            if (position != -1)
            {
                superpos = superpos + position;
                printf("Pattern \"%s\" in position %d\n", pattern, superpos);
            }
        }
        if (superpos == 0)
        {
            printf("Pattern \"%s\" not found!\n", pattern);
        }
        free(text);
    }
    else
    {
        printf("%s%smERROR: Could not open file!%s0m\n", CSI, colors[1], CSI);
        return 1;
    }
    fclose(in);
    return 0;
}

int check_dir(char *path, char *pattern)
{
    DIR *dir;
    struct dirent *ent;
    int len;

    dir = opendir(path);
    if (dir == NULL)
    {
        printf("%s%smERROR: Could not open directory!%s0m\n", CSI, colors[1], CSI);
        return 1;
    }
    len = strlen(path);

    char temp[len + 1];
    strcpy(temp, path);

    printf("\t\t%s%smIn directory \"%s\"%s0m\n", CSI, colors[0], path, CSI);

    while ((ent = readdir(dir)) != false)
    {
        if (ent->d_type == DT_REG)
        {
            path = malloc(255 * sizeof(char));
            strcpy(path, temp);
            strcat(path, "/");
            strcat(path, ent->d_name);
            printf("%s%smIn file \"%s\"%s0m\n", CSI, colors[0], ent->d_name, CSI); 
            check_file(path, pattern);
            free(path);
        }
    }
    closedir(dir);
    return 0;
}

int rec_check_dir(char *path, char *pattern)
{
    DIR *dir;
    struct dirent *ent;
    char rec_path[255];
    int flag;

    flag = check_dir(path, pattern);
    if (flag == 1)
    {
        return 1;
    }
    dir = opendir(path);
    if (dir == NULL)
    {
        printf("%s%smERROR: Could not open directory!%s0m\n", CSI, colors[1], CSI);
        return 1;
    }
    while ((ent = readdir(dir)) != false)
    {
        if (ent->d_type == DT_DIR && strcmp(ent->d_name, "..") != 0 && strcmp(ent->d_name, ".") != 0)
        {
            int length = strlen(ent->d_name);
            char cur_dir[length];
            
            strcpy(cur_dir, ent->d_name);
            strcpy(rec_path, path);
            strcat(rec_path, "/");
            strcat(rec_path, cur_dir);
            rec_check_dir(rec_path, pattern);
            memset(rec_path, 0, strlen(rec_path));
        }
    }
    closedir(dir);
    return 0;
}