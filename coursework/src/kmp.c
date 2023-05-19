#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "kmp.h"

int kmp_seeker(char *text, char *pattern)
{
    int i, j, len_patt, len_text;
    len_text = strlen(text);
    len_patt = strlen(pattern);

    int *pref_array = (int *)malloc(len_patt * sizeof(int)); // Массив для хранения информации отработки префикс-функции

    pref_array = prefix(pattern, len_patt, pref_array); // Префикс-функция

    for (i = 0, j = 0; i < len_text; i++) // Поиск шаблона в тексте
    {
        while (j > 0 && pattern[j] != text[i])
        {
            j = pref_array[j - 1];
        }
        if (pattern[j] == text[i])
        {
            j++;
        }
        if (j == len_patt)
        {
            free(pref_array);
            return i - j + 1;
        }
    }

    free(pref_array);
    return -1;
}

int *prefix(char *patt, int len, int *array)
{
    int i, j;
    array[0] = 0;
    for (i = 1, j = 0; i < len; i++) 
    {
        while (j > 0 && patt[j] != patt[i])
        {
            j = array[j - 1];
        }
        if (patt[j] == patt[i])
        {
            j++;
        }
        array[i] = j;
    }
    return array;
}