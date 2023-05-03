#include <string.h>

#include "coder.h"
#include "command.h"

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        printf("Usage:\n coder encode <in-file-name> <out-file-name>\n coder decode <in-file-name> <out-file-name>\n");
        return -1;
    }

    const char *command = argv[1];
    const char *in_file_name = argv[2];
    const char *out_file_name = argv[3];

    if (strcmp("encode", command) == 0)
    {
        encode_file(in_file_name, out_file_name);
        return 0;
    }
    else if (strcmp("decode", command) == 0)
    {
        decode_file(in_file_name, out_file_name);
        return 0;
    }
    else 
    {
        printf("Uncorrect input!\n");
        return -1;
    }
}