#include "command.h"
#include "coder.h"

int encode_file(const char *in_file_name, const char *out_file_name)
{
    FILE *in, *out;

    in = fopen(in_file_name, "r");

    if (in == NULL)
    {
        printf("Ошибка открытия файла!\n");
        return -1;
    }

    out = fopen(out_file_name, "wb");

    if (out == NULL)
    {
        printf("Ошибка открытия файла!\n");
        return -1;
    }

    uint32_t code_point;
    CodeUnits code_unit;

    while(fscanf(in, "%" SCNx32, &code_point) >= 0)
    {
        printf("%" PRIx32 "\n", code_point);
 
        if (encode(code_point, &code_unit) < 0)
        {
            printf("Ошибка кодировки!\n");
            return -1;
        }

        write_code_unit(out, &code_unit);
    }

    fclose(in);
    fclose(out);

    printf("Кодирование завершено успешно!\n");
    return 0;
}

int decode_file(const char *in_file_name, const char *out_file_name)
{
    FILE *in, *out;

    in = fopen(in_file_name, "r");
    if (in == NULL)
    {
        printf("Ошибка открытия файла!\n");
        return -1;
    }

    out = fopen(out_file_name, "wb");
    if (out == NULL)
    {
        printf("Ошибка открытия файла!\n");
        return -1;
    }

    CodeUnits code_unit;
    uint32_t code_point;

    while(read_next_code_unit(in, &code_unit) != -1)
    {
        code_point = decode(&code_unit);
        fprintf(out, "%" PRIx32 "\n", code_point);
    }

    fclose(in);
    fclose(out);
    return 0;
}