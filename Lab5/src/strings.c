#include <stdio.h>

#include "strings.h"

int mein_strlen(char *string) // correct
{
    int length = 0;
    while (*string != '\0')
    {
        string++;
        length++;
    }
    return length;
}

char *mein_strcpy(char *string1, char *string2) // correct
{
    if (string2 == NULL)
    {
        return NULL;
    }

    char *ptr = string2;

    while (*string1 != '\0')
    {
        *string2 = *string1;
        string1++;
        string2++;
    }   

    *string2 = '\0';

    return ptr;
}

int mein_strcmp(char *string1, char *string2) // correct
{
    while (*string1 == *string2)
    {
        if (*string2 == '\0')
        {
            break;
        }
        string1++;
        string2++;
    }
    return *string1 - *string2;
}

char *mein_strchr(char *string, char symbol) // correct
{
    while (*string != '\0')
    {
        if (*string == symbol)
        {
            return string;
        }
        string++;
    }
    return NULL;
}

unsigned short mein_strspn(char *string, char *find) // correct
{
    unsigned short count = 0;

    while (*string)
    {
        int c = *string;
        if (mein_strchr(find, c) != NULL)
        {
            count++;
        }
        else
        {
            break;
        }
        string++;
    }

    return count;
}

int mein_is_delim(char symbol, char *delim) // correct
{
    while (*delim != '\0')
    {
        if (symbol == *delim)
        {
            return 1;
        }
        delim++;
    }
    return 0;
}

char *mein_strtok(char *string, char *delim) // correct
{
    static char *current;

    if (!string)
    {
        string = current;
    }
    if (!string)
    {
        return NULL;
    }
    while (1)
    {
        if (mein_is_delim(*string, delim))
        {
            string++;
            continue;
        }
        if (*string == '\0')
        {
            return NULL;
        }
        break;
    }

    char *returned = string;

    while(1)
    {
        if (*string == '\0')
        {
            current = string;
            return returned;
        }
        if (mein_is_delim(*string, delim))
        {
            *string = '\0';
            current = string + 1;
            return returned;
        }
        string++;
    }
}

int mein_is_digit(char symbol) // correct
{
    if (symbol >= 48 && symbol <= 57)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int mein_is_alpha(char symbol) // correct
{
    if ((symbol >= 65 && symbol <= 90) || (symbol >= 97 && symbol <= 122))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int mein_atoi(char *string) // correct
{
    int result = 0;
    int i = 0;

    while (string[i] && (string[i] >= '0' && string[i] <= '9'))
    {
        result = result * 10 + (string[i] - '0');
        i++;
    }

    return result;
}

char *mein_suffix(char *string, char symbol) // correct
{
    while (*string != '\\')
    {
        string++;
    }
    while (*string != symbol)
    {
        string--;
    }
    return string;
}

char *mein_strcat(char *dest, const char *src) // correct
{
    char *ptr = dest + mein_strlen(dest);

    while (*src != '\0')
    {
        *ptr++ = *src++;
    }

    *ptr = '\0';

    return dest;
}