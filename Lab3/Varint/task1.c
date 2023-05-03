#include "varint.h"
#define QUANTITY 1000000

int main()
{
    FILE *file, *file2;
    uint32_t *array, value, value2;
    size_t temp, i;
    uint8_t *bufp, buf[4];

    array = malloc(QUANTITY * sizeof(uint32_t));
    if (array == NULL)
    {
        printf("Не удалось выделить память под массив\n");
        return 0;
    }
    for (i = 0; i < QUANTITY; i++)
        array[i] = generate_number();
    
    file = fopen("uncompressed.dat", "wb");
    if (file == NULL)
    {
        printf("Не удалось открыть (создать) файл\n");
        return 0;
    }
    for (i = 0; i < QUANTITY; i++)
    {
        fwrite(&array[i], sizeof(uint32_t), 1, file);
    }
    fclose(file);

    file2 = fopen("compressed.dat", "wb");
    if (file2 == NULL)
    {
        printf("Не удалось открыть (создать) файл\n");
        return 0;
    }
    for (i = 0; i < QUANTITY; i++)
    {
        temp = encode_varint(array[i], buf);
        fwrite(buf, 1, temp, file2);
    }
    fclose(file);

    file = fopen("uncompressed.dat", "rb");
    file2 = fopen("compressed.dat", "rb");
    if (file == NULL || file2 == NULL)
    {
        printf("Не удалось открыть файл\n");
        return 0;
    }
    fseek(file, 0, SEEK_SET);
    fseek(file2, 0, SEEK_SET);
    for (i = 0; i < QUANTITY; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            fread(&buf[j], sizeof(uint8_t), 1, file2);
            if ((buf[j] >> 7) == 0)
                break;
        }
        bufp = buf;
        value = decode_varint(&bufp);
        fread(&value2, sizeof(uint32_t), 1, file);
        if (value != value2)
        {
            printf("Числа не равны!\n");
            return 0;
        }
    }
    if (array != NULL)
        free(array);
    fclose(file);
    fclose(file2);
    printf("Числа совпадают :)\n");
    return 0;
}