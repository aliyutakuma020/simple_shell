#include "shell.h"

/**
 * pel_custom_strcpy - it copies a string
 * @d: the destination
 * @s: the source
 *
 * Return: returns pointer to destination
 */
char *pel_custom_strcpy(char *d, char *s)
{
    int j = 0;

    if (d == s || s == 0)
        return (d);

    while (s[j])
    {
        d[j] = s[j];
        j++;
    }

    d[j] = '\0';
    return (d);
}

/**
 * pel_custom_strdup - it duplicates a string
 * @s: string to the duplicate
 *
 * Return: returns pointer to the duplicated string
 */
char *pel_custom_strdup(const char *s)
{
    int l = 0;
    char *r;

    if (s == NULL)
        return (NULL);

    while (*s++)
        l++;

    r = malloc(sizeof(char) * (l + 1));
    if (!r)
        return (NULL);

    for (l++; l--;)
        r[l] = *--s;

    return (r);
}

/**
 * pel_custom_puts - it prints an input string.
 * @s: string to be printed.
 *
 * Return: it returns Nothing
 */
void pel_custom_puts(char *s)
{
    int j = 0;

    if (!s)
        return;

    while (s[j] != '\0')
    {
        pel_custom_putchar(s[j]);
        j++;
    }
}

/**
 * pel_custom_putchar - writes the character to stdout with buffering
 * @ch: The character to print.
 *
 * Return: On success 1.
 */
int pel_custom_putchar(char ch)
{
    static int j;
    static char buffer[WRITE_BUFFER_SIZE];

    if (ch == BUFFER_FLUSH || j >= WRITE_BUFFER_SIZE)
    {
        write(1, buffer, j);
        j = 0;
    }
    if (ch != BUFFER_FLUSH)
        buffer[j++] = ch;
    return (1);
}
