#include "shell.c"

/**
 * print_ap - prints to the standard output
 * @info: string
 * Return: No return value
 *
 */

void print_ap(const char *info)
{
	write(STDOUT_FILENO, info, strlen(info));
}
