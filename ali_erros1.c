#include "shell.h"
/**
* pel_custom_error_atoi - Converts a string to an integer.
* @t: String to be converted.
*
* Return: 0 if no numbers in string, converted number otherwise,
*         -1 on error.
*/
int pel_custom_error_atoi(char *t)
{
int j = 0;
unsigned long int result = 0;
if (*t == '+')
t++;
for (j = 0; t[j] != '\0'; j++)
{
if (t[j] >= '0' && t[j] <= '9')
{
result *= 10;
result += (t[j] - '0');
if (result > INT_MAX)
return (-1);
}
else
return (-1);
}
return (result);
}
/**
* pel_custom_print_error - Prints an error message.
* @format: Parameter & return info struct.
* @e: String containing specified error type.
*/
void pel_custom_print_error(CustomInfo_t *format, char *e)
{
pel_custom_error_puts(format->prg_fname);
pel_custom_error_puts(": ");
pel_custom_print_d(format->count_err, STDERR_FILENO);
pel_custom_error_puts(": ");
pel_custom_error_puts(format->argv[0]);
pel_custom_error_puts(": ");
pel_custom_error_puts(e);
}
/**
* pel_custom_print_d - Prints a decimal (int) number (base 10).
* @insert: Input.
* @fd: The file descriptor to be written.
*
* Return: Returns the number of characters printed.
*/
int pel_custom_print_d(int insert, int fd)
{
int (*_pel_custom_putchar)(char) = pel_custom_putchar;
int j, count = 0;
unsigned int _abs_, current;
if (fd == STDERR_FILENO)
_pel_custom_putchar = pel_custom_error_putchar;
if (insert < 0)
{
_abs_ = -insert;
_pel_custom_putchar('-');
count++;
}
else
_abs_ = insert;
current = _abs_;
for (j = 1000000000; j > 1; j /= 10)
{
if (_abs_ / j)
{
_pel_custom_putchar('0' + current / j);
count++;
}
current %= j;
}
_pel_custom_putchar('0' + current);
count++;
return (count);
}
/**
* pel_custom_convert_number - Converter function, a clone of itoa.
* @m: The number.
* @base: The base.
* @flags: The argument flags.
*
* Return: Returns the string.
*/
char *pel_custom_convert_number(long int m, int base, int flags)
{
static char *a;
static char buffer[50];
char s = 0;
char *ptr;
unsigned long n = m;
if (!(flags & UNSIGNED_CONVERSION) && m < 0)
{
n = -m;
s = '-';
}
a = flags & LOWERCASE_CONVERSION ? "0123456789abcdef" : "0123456789ABCDEF";
ptr = &buffer[49];
*ptr = '\0';
do {
*--ptr = a[n % base];
n /= base;
} while (n != 0);
if (s)
*--ptr = s;
return (ptr);
}
/**
* pel_custom_remove_comments - Replaces the first instance of '#' with '\0'.
* @b: Address of the string to modify.
*/
void pel_custom_remove_comments(char *b)
{
int j;
for (j = 0; b[j] != '\0'; j++)
{
if (b[j] == '#' && (j == 0 || b[j - 1] == ' '))
{
b[j] = '\0';
break;
}
}
}
