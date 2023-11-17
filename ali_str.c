#include "shell.h"

/**
 * _strlen - string length
 * @s: s must be admistered
 *
 * Return: s in numbers
 */
int _strlen(char *s)
{
	int i = 0;

	if (!s)
		return (0);

	while (*s++)
		i++;
	return (i);
}

/**
 * _strcmp - compares two strun
 * @s1: strung one
 * @s2: strung two
 *
 * Return: no good  if s1 < s2, good if > s2, zero if = s2.
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * starts_with - function when it goes
 * @haystack: str to search
 * @needle: substr to be looked for
 *
 * Return: address of haystack, NULL if failed
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * _strcat - puts two str together
 * @dest: buffer stop
 * @src: buffer start
 *
 * Return: buffer stop ptr
 */
char *_strcat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}
