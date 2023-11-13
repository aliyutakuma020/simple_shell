#include "shell.h"

/**
 * pel_custom_strlen - it returns the length of a string.
 * @s: the string length to be checked
 *
 * Return: integer length of the string
 */
int pel_custom_strlen(char *str)
{
    int j = 0;

    if (!str)
        return (0);

    while (*str++)
        j++;
    return (j);
}

/**
 * pel_custom_strcmp - it performs the comparison of two strings.
 * @s11: first string
 * @s12: second string
 *
 * Return: it returns negative if s11 < s22, positive or zero if s11 == s22
 */
int pel_custom_strcmp(char *s11, char *s22)
{
    while (*s11 && *s22)
    {
        if (*s11 != *s22)
            return (*s11 - *s22);
        s11++;
        s22++;
    }
    if (*s11 == *s22)
        return 0;
    else
        return (*s11 < *s22 ? -1 : 1);
}

/**
 * pel_custom_starts_with - it checks if the needle starts with stack
 * @stack: string to be searched
 * @need: substring to find
 *
 * Return: returns the address of the next char of stack or NULL
 */
char *pel_custom_starts_with(const char *stack, const char *need)
{
    while (*need)
        if (*need++ != *stack++)
            return NULL;
    return ((char *)stack);
}

/**
 * pel_custom_strcat - it concatenates two strings
 * @d: destination buffer
 * @s: source buffer
 *
 * Return: pointer to destination buffer
 */
char *pel_custom_strcat(char *d, char *s)
{
    char *result = d;

    while (*d)
        d++;
    while (*s)
        *d++ = *s++;
    *d = *s;

    return (result);
}
