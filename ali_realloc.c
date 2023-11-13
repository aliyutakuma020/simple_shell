#include "shell.h"

/**
 * pel_custom_memset - it fills memory with a constant byte
 * @str: pointer to the memory area
 * @byte: byte to be filled
 * @num: amount of bytes to be filled
 * Return: (s) a pointer to the memory area.
 */
char *pel_custom_memset(char *str, char byte, unsigned int num)
{
    unsigned int j;

    for (j = 0; j < num; j++)
        str[j] = byte;

    return (str);
}
/**
 * pel_custom_ffree - it frees a string of some strings.
 * @ss: the string of strings
 */
void pel_custom_free(char **ss)
{
    char **t = ss;

    if (!ss)
        return;
    while (*ss)
        free(*ss++);
    free(t);
}
/**
 * pel_custom_realloc - it reallocates a block of a memory.
 * @p: A pointer to previous malloc'ated block.
 * @o_size: The byte size of the previous block.
 * @n_size: The byte size of the new block.
 *
 * Return: Returns a pointer to the reallocated block.
 */
void *pel_custom_realloc(void *p, unsigned int o_size, unsigned int n_size)
{
    char *t;

    if (!p)
        return (malloc(n_size));
    if (!n_size)
        return (free(p), NULL);
    if (n_size == o_size)
        return (p);

    t = malloc(n_size);
    if (!t)
        return (NULL);
    o_size = o_size < n_size ? o_size : n_size;
    while (o_size--)
        t[o_size] = ((char *)p)[o_size];
    free(p);
    return (t);
}
