#include "shell.h"
/**
* pel_custom_interactive - Returns true if the custom shell is in
* interactive mode.
* @format: CustomInfo_t struct
*
* Return: 1 if in interactive mode, 0 otherwise
*/
int pel_custom_interactive(CustomInfo_t *format)
{
return (isatty(STDIN_FILENO) && format->r_fd <= 2);
}
/**
* pel_custom_is_delimiter  - it Checks if a character is a delimiter.
* @a: The character to check
* @format: The delimiter string.
*
* Return: 1 if 'a' is a delimiter, 0 if not
*/
int pel_custom_is_delimiter(char a, char *format)
{
while (*format)
if (*format++ == a)
return (1);
return (0);
}
/**
* pel_custom_is_alpha - it Checks weather a character is alphabetic.
* @b: The character to check
*
* Return: 1 if 'b' is alphabetic, 0 if not
*/
int pel_custom_is_alpha(int b)
{
if ((b >= 'a' && b <= 'z') || (b >= 'A' && b <= 'Z'))
return (1);
else
return (0);
}
/**
* pel_custom_atoi - It Converts a string to an integer.
* @s: The string to be converted.
*
* Return: The integer value from 's'.
*/
int pel_custom_atoi(char *s)
{
int j, sign = 1, flag = 0, out;
unsigned int result = 0;
for (j = 0; s[j] != '\0' && flag != 2; j++)
{
if (s[j] == '-')
sign *= -1;
if (s[j] >= '0' && s[j] <= '9')
{
flag = 1;
result *= 10;
result += (s[j] - '0');
}
else if (flag == 1)
flag = 2;
}
if (sign == -1)
out = -result;
else
out = result;
return (out);
}
