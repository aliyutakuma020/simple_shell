#include "shell.h"
/**
* pel_custom_error_puts - prints an input string to standard error (2)
* @s: the string to be printed
*
* Return: Nothing
*/
void pel_custom_error_puts(char *s)
{
int j = 0;
if (!s)
return;
while (s[j] != '\0')
{
pel_custom_error_putchar(s[j]);
j++;
}
}
/**
* pel_custom_error_putchar - It writes the character c to stderr
* @c: The character to be printed.
*
* Return: On success 1.
* On error, -1 is returned, and errno is set appropriately.
*/
int pel_custom_error_putchar(char c)
{
static int j;
static char buf[WRITE_BUFFER_SIZE];
if (c == BUFFER_FLUSH || j >= WRITE_BUFFER_SIZE)
{
write(2, buf, j);
j = 0;
}
if (c != BUFFER_FLUSH)
buf[j++] = c;
return (1);
}
/**
* pel_custom_fd_putchar - writes the character c to the given file descriptor
* @c: The character to print
* @fd: The file descriptor to be written.
*
* Return: On success 1.
* On error, -1 .
*/
int pel_custom_fd_putchar(char c, int fd)
{
static int j;
static char buf[WRITE_BUFFER_SIZE];
if (c == BUFFER_FLUSH || j >= WRITE_BUFFER_SIZE)
{
write(fd, buf, j);
j = 0;
}
if (c != BUFFER_FLUSH)
buf[j++] = c;
return (1);
}
/**
* pel_custom_error_puts_fd - it prints an input string
* to the given file descriptor.
* @s: String to be printed
* @fd: file descriptor to written.
*
* Return: returns number of characters written
*/
int pel_custom_error_puts_fd(char *s, int fd)
{
int j = 0;
if (!s)
return (0);
while (*s)
{
j += pel_custom_fd_putchar(*s++, fd);
}
return (j);
}
