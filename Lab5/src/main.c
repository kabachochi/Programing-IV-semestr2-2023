#include <stdio.h>
#include <stdlib.h>

#include "supertask.h"
#include "strings.h"

int main()
{
    char *in, *superstr, *temp;
    char *out = malloc(260 * sizeof(char));
    int *errors = calloc(0, 6 * sizeof(int));
    char *delim = "+";
    int count = 1;
    in = input();
    superstr = mein_strtok(in, delim);

    while (superstr != NULL)
    {
        printf("\nСтрока %d\n", count); 
        check(superstr, errors);
        output_errors(errors);
        if (errors[5] == 0)
        {
            temp = superstr;
            process(temp, out);
            output_string(out);
        }
        superstr = mein_strtok(NULL, delim);
        count++;
        *out = 0;
        for (int i = 0; i < 6; i++)
        {
            errors[i] = 0;
        }
    }

    if (out != NULL)
    {
        free(out);
    }
    if (errors != NULL)
    {
        free(errors);
    }
    return 0;
}