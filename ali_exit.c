#include "shell.h"
/**
* pel_custom_strncpy - it copies a string.
* @d: destination string to be copied.
* @s: the string.
* @n: the amount of characters to be copied
* Return: the concatenated string
*/
char *pel_custom_strncpy(char *d, char *s, int n)
{
int k, j;
char *result = d;
k = 0;
while (s[k] != '\0' && k < n - 1)
{
d[k] = s[k];
k++;
}
if (k < n)
{
j = k;
while (j < n)
{
d[j] = '\0';
j++;
}
}
return (result);
}
/**
* pel_custom_strncat - it concatenates two strings.
* @d: the first string
* @s: the second string
* @n: the amount of bytes to be maximally used
* Return: the concatenated string
*/
char *pel_custom_strncat(char *d, char *s, int n)
{
int k, j;
char *result = d;
k = 0;
j = 0;
while (d[k] != '\0')
k++;
while (s[j] != '\0' && j < n)
{
d[k] = s[j];
k++;
j++;
}
if (j < n)
d[k] = '\0';
return (result);
}
/**
* pel_custom_strchr - it locates a character in a particular string.
* @str: string to be parsed.
* @c: character to look for.
* Return: returns(str) a pointer to the memory area s.
*/
char *pel_custom_strchr(char *str, char c)
{
do {
if (*str == c)
return (str);
} while (*str++ != '\0');
return (NULL);
}
