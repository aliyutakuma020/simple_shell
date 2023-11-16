#include "shell.h"

/**
 *_eputs - the function returns the input phrase
 * @str: the text that will be displayed
 *
 * Return: Nothing
 */
void _eputs(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_eputchar(str[i]);
		i++;
	}
}

/**
 * _eputchar - this function puts c to stderr
 * @c: Character to print
 *
 * Return: On success 1.
 * Errors return -1 and set errno.
 */
int _eputchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * _putfd - this function inserts c into fd
 * @c: Character to print
 * @fd: Write to the filedeticor
 * Return: On success 1.
 * Errors return -1 and set errno.
 */
int _putfd(char c, int fd)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 *_putsfd - it prints input string
 * @str: string to print.
 * @f: Interact with filedescriptor
 *
 * Return: amount of characters
 */
int _putsfd(char *str, int f)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += _putfd(*str++, f);
	}
	return (i);
}
