#define CSI "\x1B\x5B"

int check_file(char *path, char *pattern);

int check_dir(char *path, char *pattern);

int rec_check_dir(char *path, char *pattern);