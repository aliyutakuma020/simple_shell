#include "shell.h"

/**
 **_strncpy - it copies string
 *@dest: the string to which the copy will be made
 *@src: the source text.
 *@n: the number of characters that will be duplicated
 *Return: it returns the concatenated phrase
 */
char *_strncpy(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	while (src[i] != '\0' && i < n - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (s);
}

/**
 **_strncat - this function combines two strings
 *@dest: the initial string.
 *@src: the second line of the string.
 *@n: the maximum number of bytes to be used
 *Return: the phrase concatenated
 */
char *_strncat(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0' && j < n)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	if (j < n)
		dest[i] = '\0';
	return (s);
}

/**
 **_strchr - this function character locates within a string.
 *@s: The phrase requiring to be parsed.
 *@c: the individual to seek out
 *Return: (s) a pointer to the area of memory
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
