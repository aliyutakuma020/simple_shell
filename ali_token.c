#include "shell.h"

/**
 * pel_custom_strtow - it splits a string into words.
 * @str: input string.
 * @delimiters: delimeter of a string
 * Return: returns a pointer to an array of strings, or NULL on failure
 */
char **pel_custom_strtow(char *str, char *delimiters)
{
    int i, j, k, m, num = 0;
    char **result;

    if (str == NULL || str[0] == 0)
        return (NULL);

    if (!delimiters)
        delimiters = " ";

    for (i = 0; str[i] != '\0'; i++)
    {
        if (!pel_custom_is_delimiter(str[i], delimiters) && (pel_custom_is_delimiter(str[i + 1], delimiters) || !str[i + 1]))
        {
            num++;
        }
    }

    if (num == 0)
        return (NULL);

    result = malloc((1 + num) * sizeof(char *));
    if (!result)
        return (NULL);

    for (i = 0, j = 0; j < num; j++)
    {
        while (pel_custom_is_delimiter(str[i], delimiters))
            i++;

        k = 0;
        while (!pel_custom_is_delimiter(str[i + k], delimiters) && str[i + k])
            k++;

        result[j] = malloc((k + 1) * sizeof(char));
        if (!result[j])
        {
            for (k = 0; k < j; k++)
                free(result[k]);
            free(result);
            return (NULL);
        }

        for (m = 0; m < k; m++)
            result[j][m] = str[i++];

        result[j][m] = 0;
    }

    result[j] = NULL;
    return (result);
}
/**
 * pel_custom_strtow2 - it splits a string into words.
 * @str: input string.
 * @delimiter: delimiter character.
 * Return: returns a pointer to an array of strings, or NULL on failure
 */
char **pel_custom_strtow2(char *str, char delimiter)
{
    int i, j, k, m, num = 0;
    char **result;

    if (str == NULL || str[0] == 0)
        return (NULL);

    for (i = 0; str[i] != '\0'; i++)
    {
        if ((str[i] != delimiter && str[i + 1] == delimiter) ||
            (str[i] != delimiter && !str[i + 1]) || str[i + 1] == delimiter)
        {
            num++;
        }
    }

    if (num == 0)
        return (NULL);

    result = malloc((1 + num) * sizeof(char *));
    if (!result)
        return (NULL);

    for (i = 0, j = 0; j < num; j++)
    {
        while (str[i] == delimiter && str[i] != delimiter)
            i++;

        k = 0;
        while (str[i + k] != delimiter && str[i + k] && str[i + k] != delimiter)
            k++;

        result[j] = malloc((k + 1) * sizeof(char));
        if (!result[j])
        {
            for (k = 0; k < j; k++)
                free(result[k]);
            free(result);
            return (NULL);
        }

        for (m = 0; m < k; m++)
            result[j][m] = str[i++];

        result[j][m] = '\0';
    }

    result[j] = NULL;
    return (result);
}
