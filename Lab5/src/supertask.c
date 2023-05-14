#include <stdio.h>
#include <stdlib.h>

#include "strings.h"
#include "supertask.h"

char *input()
{
    char *name;
    printf("Введите путь: ");
    scanf("%s", name);
    printf("\nПолученная строка: \n%s\n", name);
    return name;
}

int ip_check(char *string)
{
    int dots = 0;
    int i = 0;
    if (mein_atoi(&string[i]) > 255)
    {
        return 1;
    }
    while (string[i] != '\0')
    {
        if (string[i] == '.')
        {
            dots++;
            if (mein_atoi(&string[i + 1]) > 255)
            {
                return 1;
            }
        }
        i++;
    }
    if (dots != 3)
    {
        return 1;
    }
    return 0;
}

int domen_check(char *string)
{
    int i = 0;
    int dots = 0;
    int symbols = 0;
    char domen[10];

    while (string[i] != '\\' && string[i] != '\0')
    {
        if (string[i] == '.')
        {
            dots++;
        }
        else if (mein_is_alpha(string[i]) == 0)
        {
            symbols++;
        }
        i++;
    }

    if (dots > 3 || symbols != 0)
    {
        return 1;
    }

    char *suffix = mein_suffix(string, '.');
    i = 0;

    while (suffix[i] != '\\' && suffix[i] != '\0')
    {
        domen[i] = suffix[i];
        i++;
    }

    domen[i] = '\0';

    if ((mein_strcmp(".ru", domen)) != 0 && (mein_strcmp(".com", domen) != 0) && (mein_strcmp(".org", domen) != 0))
    {
        return 1;
    }
   
    return 0;
}

int *check(char *string, int *errors)
{
    if (*string != '\\')
    {
        errors[0] = 1; // ошибка относительного пути
        errors[5] = 1;
    }

    if (mein_strlen(string) > 260) 
    {
        errors[1] = 1; // ошибка максимального количества символов
        errors[5] = 1;
    }

    char *temp = string;
    char banned[] = {'/' ,'*', '?', '<', '>', '|'};

    while (*temp != '\0')
    {
        if (mein_is_delim(*temp, banned) == 1)
        {
            errors[2] = 1; // ошибка запрещенных символов в Виндовс
            errors[5] = 1;
        }
        temp++;
    }

    temp = string;
    int i = 2;

    if (mein_is_digit(temp[i]) == 1)
    {
        errors[3] = ip_check(&temp[i]); // ошибка IP-адреса
        errors[5] = errors[3];
    }

    if (mein_is_alpha(temp[i]) == 1)
    {
        errors[4] = domen_check(&temp[i]); // ошибка домена
        errors[5] = errors[4];
    }
    return errors;
}

char *process(char *string, char *result)
{
    mein_strcat(result, "http:");
    mein_strcat(result, string);
    while(*result != '\0')
    {
        if (*result == '\\')
        {
            *result = '/'; 
        }
        result++;
    }
    return result;
}

void output_string(char *string)
{
    printf("%s\n", string);
}

void output_errors(int *errors)
{
    if (*errors == 1)
    {
        printf("Ошибка в относительном пути!\n");
    }
    if (*(errors + 1) == 1)
    {
        printf("Превышен лимит количества допустимых символов!\n");
    }
    if (*(errors + 2) == 1)
    {
        printf("Использованы запрещенные символы в пути!\n");
    }
    if (*(errors + 3) == 1)
    {
        printf("Ошибка в IP-адресе!\n");
    }
    if (*(errors + 4) == 1)
    {
        printf("Ошибка в доменном имени!\n");
    }
}